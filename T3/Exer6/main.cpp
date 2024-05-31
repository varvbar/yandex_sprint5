#include <algorithm>
#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>


using namespace std;

using filesystem::path;

path operator""_p(const char* data, std::size_t sz) {
    return path(data, data + sz);
}
void PrintTree(ostream& dst, const path& p, const filesystem::file_status& status, int offset){
    
    vector<pair<filesystem::path, filesystem::file_status>> items;
    
    if (status.type() == filesystem::file_type::directory){
        dst << string(static_cast<size_t>(offset), ' ') << p.filename().string() << endl;
        for (const auto& dir_entry : filesystem::directory_iterator(p)) {
            items.push_back({dir_entry.path(), dir_entry.status()});
        }
        // компаратор неокончательный
        sort(items.begin(), items.end(), [](const auto& LItem, const auto& RItem){
            return (LItem.second.type() == filesystem::file_type::directory && RItem.second.type() == filesystem::file_type::regular)  
                    || (LItem.first > RItem.first);
        });
        for (const auto& item : items){
            PrintTree(dst, item.first, item.second, offset+2);
        }
    }
    else {
        dst << string(static_cast<size_t>(offset), ' ') << p.filename().string() << endl;
        return;
    }

    
}
// напишите эту функцию
void PrintTree(ostream& dst, const path& p){
    int offset = 0;
    error_code err;
    // Вывели название папки
    //dst << p.filename().string() << endl;
    const auto& status = (filesystem::status(p));
    PrintTree(dst, p, status, offset);
}
int main() {
    error_code err;
    filesystem::remove_all("test_dir", err);
    filesystem::create_directories("test_dir"_p / "a"_p, err);
    filesystem::create_directories("test_dir"_p / "b"_p, err);
    ofstream("test_dir"_p / "b"_p / "f1.txt"_p);
    ofstream("test_dir"_p / "b"_p / "f2.txt"_p);
    ofstream("test_dir"_p / "a"_p / "f3.txt"_p);
    ostringstream out;
    PrintTree(out, "test_dir"_p);
    assert(out.str() ==
        "test_dir\n"
        "  b\n"
        "    f2.txt\n"
        "    f1.txt\n"
        "  a\n"
        "    f3.txt\n"s
    );
}