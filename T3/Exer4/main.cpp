#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// реализуйте эту функцию:
size_t GetFileSize(string file);

int main() {
    ofstream("test.txt") << "123456789"s;
    assert(GetFileSize("test.txt"s) == 9);

    ofstream test2("test2.txt"s);
    test2.seekp(1000);
    test2 << "abc"s;
    test2.flush();

    assert(GetFileSize("test2.txt"s) == 1003);
    assert(GetFileSize("missing file name"s) == string::npos);
}

size_t GetFileSize(string file){
    fstream fsize (file, ios::in);
    if(!fsize.good()){
        return static_cast<size_t>(string::npos);
    }

    fsize.seekg(0, ios::end);
    
    size_t result = static_cast<size_t>(fsize.tellg());
    return result;

}
