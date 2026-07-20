#ifndef FS_H
#define FS_H

#include <string>
#include <vector>
#include <cstdint>
using namespace std;

const size_t DISK_SIZE = 1024 * 1024;  // 1 MB
const size_t METADATA_SIZE = 4 * 1024; // 4 KB
const size_t BLOCK_SIZE = 512;
const size_t MAX_FILENAME = 32;
const size_t MAX_FILES = (METADATA_SIZE - sizeof(uint32_t)) / (MAX_FILENAME + sizeof(uint32_t) * 2 + sizeof(uint64_t));

struct FileMeta
{
    char name[MAX_FILENAME];
    uint32_t size;
    uint32_t start_block;
    uint64_t created;
};

class SimpleFS
{
public:
    SimpleFS(const string &diskfile = "disk.sim");
    ~SimpleFS();

    bool fs_format();
    bool fs_create(const string &filename);
    bool fs_delete(const string &filename);
    bool fs_exists(const string &filename);
    uint32_t fs_size(const string &filename);
    bool fs_rename(const string &oldname, const string &newname);
    vector<FileMeta> fs_ls();
    bool fs_write(const string &filename, const char *data, uint32_t len);
    bool fs_append(const string &filename, const char *data, uint32_t len);
    bool fs_read(const string &filename, uint32_t offset, uint32_t len, char *buffer);
    bool fs_truncate(const string &filename, uint32_t newsize);
    bool fs_copy(const string &src, const string &dest);
    bool fs_mv(const string &src, const string &dest);
    bool fs_defragment();
    bool fs_backup(const string &backup);
    bool fs_restore(const string &backup);
    bool fs_cat(const string &filename);
    bool fs_diff(const string &f1, const string &f2);
    bool fs_log();
    // integrity, delete logs, advanced features omitted for brevity

private:
    string diskfile_;
    uint32_t file_count_;
    vector<FileMeta> files_;
    int fd_;
    bool load_metadata();
    bool save_metadata();
    int alloc_blocks(uint32_t blocks);
};

#endif
