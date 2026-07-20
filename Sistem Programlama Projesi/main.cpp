#include "fs.h"

#include <iostream>
#include <sstream>
#include <cstdint>
using namespace std;
void print_menu()
{
    cout << "\nSimpleFS Menu:\n"
         << "1. Format\n"
         << "2. Create file\n"
         << "3. Delete file\n"
         << "4. Write file\n"
         << "5. Read file\n"
         << "6. List files\n"
         << "7. Rename file\n"
         << "8. Append file\n"
         << "9. Truncate file\n"
         << "10. Copy file\n"
         << "11. Move file\n"
         << "12. Backup\n"
         << "13. Restore\n"
         << "14. Cat file\n"
         << "15. Diff files\n"
         << "0. Exit\n"
         << "Choice: ";
}

int main()
{
    SimpleFS fs;
    int choice;
    while (true)
    {
        print_menu();
        cin >> choice;
        if (choice == 0)
            break;
        string a, b, data;
        uint32_t size, offset;
        switch (choice)
        {
        case 1:
            fs.fs_format();
            break;
        case 2:
            cout << "Filename: ";
            cin >> a;
            fs.fs_create(a);
            break;
        case 3:
            cout << "Filename: ";
            cin >> a;
            fs.fs_delete(a);
            break;
        case 4:
            cout << "Filename: ";
            cin >> a;
            cout << "Data: ";
            cin.ignore();
            getline(cin, data);
            fs.fs_write(a, data.c_str(), data.size());
            break;
        case 5:
            cout << "Filename: ";
            cin >> a;
            cout << "Offset: ";
            cin >> offset;
            cout << "Size: ";
            cin >> size;
            {
                vector<char> buf(size + 1);
                if (fs.fs_read(a, offset, size, buf.data()))
                {
                    buf[size] = '\0';
                    cout << buf.data() << "\n";
                }
            }
            break;
        case 6:
        {
            auto list = fs.fs_ls();
            for (auto &m : list)
                cout << m.name << "\t" << m.size << " bytes\n";
        }
        break;
        case 7:
            cout << "Old name: ";
            cin >> a;
            cout << "New name: ";
            cin >> b;
            fs.fs_rename(a, b);
            break;
        case 8:
            cout << "Filename: ";
            cin >> a;
            cout << "Data: ";
            cin.ignore();
            getline(cin, data);
            fs.fs_append(a, data.c_str(), data.size());
            break;
        case 9:
            cout << "Filename: ";
            cin >> a;
            cout << "New size: ";
            cin >> size;
            fs.fs_truncate(a, size);
            break;
        case 10:
            cout << "Source: ";
            cin >> a;
            cout << "Dest: ";
            cin >> b;
            fs.fs_copy(a, b);
            break;
        case 11:
            cout << "Source: ";
            cin >> a;
            cout << "Dest: ";
            cin >> b;
            fs.fs_mv(a, b);
            break;
        case 12:
            cout << "Backup file: ";
            cin >> a;
            fs.fs_backup(a);
            break;
        case 13:
            cout << "Backup file: ";
            cin >> a;
            fs.fs_restore(a);
            break;
        case 14:
            cout << "Filename: ";
            cin >> a;
            fs.fs_cat(a);
            break;
        case 15:
            cout << "File1: ";
            cin >> a;
            cout << "File2: ";
            cin >> b;
            fs.fs_diff(a, b);
            break;
        default:
            cout << "Invalid\n";
        }
    }
    return 0;
}
