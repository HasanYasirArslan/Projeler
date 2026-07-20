#include "fs.h"
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <ctime>
#include <algorithm>
#include <sys/stat.h>
using namespace std;

SimpleFS::SimpleFS(const string &diskfile)
    : diskfile_(diskfile), file_count_(0), fd_(-1)
{
    // open or create disk file
    fd_ = open(diskfile_.c_str(), O_RDWR | O_CREAT, 0666);
    if (fd_ < 0)
    {
        perror("open");
        return;
    }
    // ensure size
    struct stat st;
    if (fstat(fd_, &st) == 0)
    {
        if ((size_t)st.st_size < DISK_SIZE)
        {
            if (ftruncate(fd_, DISK_SIZE) < 0)
                perror("ftruncate");
        }
    }
    load_metadata();
}

SimpleFS::~SimpleFS()
{
    if (fd_ >= 0)
        save_metadata();
    if (fd_ >= 0)
        close(fd_);
}

bool SimpleFS::load_metadata()
{
    lseek(fd_, 0, SEEK_SET);
    // read file_count
    if (read(fd_, &file_count_, sizeof(file_count_)) != sizeof(file_count_))
        return false;
    files_.clear();
    for (size_t i = 0; i < MAX_FILES; ++i)
    {
        FileMeta m;
        if (read(fd_, &m, sizeof(m)) != sizeof(m))
            return false;
        if (m.name[0])
            files_.push_back(m);
    }
    return true;
}

bool SimpleFS::save_metadata()
{
    lseek(fd_, 0, SEEK_SET);
    write(fd_, &file_count_, sizeof(file_count_));
    // write slots
    size_t idx = 0;
    for (; idx < files_.size(); ++idx)
    {
        write(fd_, &files_[idx], sizeof(FileMeta));
    }
    // empty rest
    FileMeta empty = {};
    for (; idx < MAX_FILES; ++idx)
        write(fd_, &empty, sizeof(empty));
    return true;
}

bool SimpleFS::fs_format()
{
    // reset metadata
    file_count_ = 0;
    files_.clear();
    save_metadata();
    // truncate data area
    // effectively zeroed by ftruncate if desired
    return true;
}
bool SimpleFS::fs_exists(const string &filename)
{
    return any_of(files_.begin(), files_.end(), [&](const FileMeta &m)
                  { return filename == m.name; });
}
uint32_t SimpleFS::fs_size(const string &filename)
{
    for (auto &m : files_)
        if (filename == m.name)
            return m.size;
    return 0;
}

bool SimpleFS::fs_create(const string &filename)
{
    if (filename.size() >= MAX_FILENAME || fs_exists(filename) || files_.size() >= MAX_FILES)
        return false;
    // new file, start size 0 => no blocks allocated until write/append
    FileMeta m = {};
    strncpy(m.name, filename.c_str(), MAX_FILENAME - 1);
    m.size = 0;
    m.start_block = 0; // allocate later
    m.created = time(NULL);
    files_.push_back(m);
    file_count_ = files_.size();
    save_metadata();
    return true;
}

bool SimpleFS::fs_delete(const string &filename)
{
    auto it = find_if(files_.begin(), files_.end(), [&](const FileMeta &m)
                      { return filename == m.name; });
    if (it == files_.end())
        return false;
    // for simplicity, no defragment; just remove metadata
    files_.erase(it);
    file_count_ = files_.size();
    save_metadata();
    return true;
}

bool SimpleFS::fs_rename(const string &oldname, const string &newname)
{
    if (fs_exists(newname))
        return false;
    for (auto &m : files_)
    {
        if (oldname == m.name)
        {
            strncpy(m.name, newname.c_str(), MAX_FILENAME - 1);
            save_metadata();
            return true;
        }
    }
    return false;
}

vector<FileMeta> SimpleFS::fs_ls()
{
    return files_;
}

int SimpleFS::alloc_blocks(uint32_t blocks)
{
    // simple: append at end of data area
    size_t max_block = 0;
    for (auto &m : files_)
    {
        size_t blk_count = m.start_block + (m.size + BLOCK_SIZE - 1) / BLOCK_SIZE;
        max_block = std::max(max_block, blk_count);
    }
    if ((max_block + blocks) * BLOCK_SIZE > DISK_SIZE - METADATA_SIZE)
        return -1;
    return static_cast<int>(max_block);
}

bool SimpleFS::fs_write(const string &filename, const char *data, uint32_t len)
{
    for (auto &m : files_)
    {
        if (filename == m.name)
        {
            // allocate blocks
            uint32_t blocks = (len + BLOCK_SIZE - 1) / BLOCK_SIZE;
            int blk = alloc_blocks(blocks);
            if (blk < 0)
                return false;
            m.start_block = blk;
            m.size = len;
            lseek(fd_, METADATA_SIZE + blk * BLOCK_SIZE, SEEK_SET);
            if (write(fd_, data, len) != (ssize_t)len)
                return false;
            save_metadata();
            return true;
        }
    }
    return false;
}

bool SimpleFS::fs_append(const string &filename, const char *data, uint32_t len)
{
    for (auto &m : files_)
    {
        if (filename == m.name)
        {
            // read existing data
            vector<char> buf(m.size);
            lseek(fd_, METADATA_SIZE + m.start_block * BLOCK_SIZE, SEEK_SET);
            read(fd_, buf.data(), m.size);
            // write new combined
            fs_write(filename, buf.data(), m.size); // re-alloc
            // write append
            lseek(fd_, METADATA_SIZE + m.start_block * BLOCK_SIZE + m.size, SEEK_SET);
            write(fd_, data, len);
            m.size += len;
            save_metadata();
            return true;
        }
    }
    return false;
}

bool SimpleFS::fs_read(const string &filename, uint32_t offset, uint32_t len, char *buffer)
{
    for (auto &m : files_)
    {
        if (filename == m.name)
        {
            if (offset + len > m.size)
                return false;
            lseek(fd_, METADATA_SIZE + m.start_block * BLOCK_SIZE + offset, SEEK_SET);
            return read(fd_, buffer, len) == (ssize_t)len;
        }
    }
    return false;
}

bool SimpleFS::fs_truncate(const string &filename, uint32_t newsize)
{
    for (auto &m : files_)
    {
        if (filename == m.name)
        {
            if (newsize > m.size)
                return false;
            m.size = newsize;
            save_metadata();
            return true;
        }
    }
    return false;
}

bool SimpleFS::fs_copy(const string &src, const string &dest)
{
    if (!fs_exists(src) || fs_exists(dest))
        return false;
    uint32_t sz = fs_size(src);
    vector<char> buf(sz);
    fs_read(src, 0, sz, buf.data());
    fs_create(dest);
    return fs_write(dest, buf.data(), sz);
}

bool SimpleFS::fs_mv(const string &src, const string &dest)
{
    if (!fs_exists(src) || fs_exists(dest))
        return false;
    return fs_rename(src, dest);
}

bool SimpleFS::fs_backup(const string &backup)
{
    int ofd = open(backup.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (ofd < 0)
        return false;
    lseek(fd_, 0, SEEK_SET);
    char buf[BLOCK_SIZE];
    size_t remaining = DISK_SIZE;
    while (remaining)
    {
        ssize_t r = read(fd_, buf, min<size_t>(BLOCK_SIZE, remaining));
        write(ofd, buf, r);
        remaining -= r;
    }
    close(ofd);
    return true;
}

bool SimpleFS::fs_restore(const string &backup)
{
    int ifd = open(backup.c_str(), O_RDONLY);
    if (ifd < 0)
        return false;
    lseek(fd_, 0, SEEK_SET);
    char buf[BLOCK_SIZE];
    size_t remaining = DISK_SIZE;
    while (remaining)
    {
        ssize_t r = read(ifd, buf, min<size_t>(BLOCK_SIZE, remaining));
        write(fd_, buf, r);
        remaining -= r;
    }
    close(ifd);
    load_metadata();
    return true;
}

bool SimpleFS::fs_cat(const string &filename)
{
    uint32_t sz = fs_size(filename);
    vector<char> buf(sz + 1);
    if (!fs_read(filename, 0, sz, buf.data()))
        return false;
    buf[sz] = '\0';
    printf("%s\n", buf.data());
    return true;
}

bool SimpleFS::fs_diff(const string &f1, const string &f2)
{
    uint32_t sz1 = fs_size(f1), sz2 = fs_size(f2);
    if (sz1 != sz2)
    {
        printf("Size differs: %u vs %u\n", sz1, sz2);
        return false;
    }
    vector<char> b1(sz1), b2(sz2);
    fs_read(f1, 0, sz1, b1.data());
    fs_read(f2, 0, sz2, b2.data());
    for (uint32_t i = 0; i < sz1; ++i)
        if (b1[i] != b2[i])
        {
            printf("Byte %u differs: %02x vs %02x\n", i, b1[i], b2[i]);
            return false;
        }
    printf("Files are identical\n");
    return true;
}
