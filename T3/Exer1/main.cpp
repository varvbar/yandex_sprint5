#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>

using namespace std;

// реализуйте эту функцию:
void CreateFiles(const string& config_file);

string GetLine(istream& in) {
    string s;
    getline(in, s);
    return s;
}

int main() {
    ofstream("test_config.txt"s) << "a.txt\n"
                                    ">10\n"
                                    ">abc\n"
                                    "b.txt\n"
                                    ">123"s;

    CreateFiles("test_config.txt"s);
    ifstream in_a("a.txt"s);
    assert(GetLine(in_a) == "10"s && GetLine(in_a) == "abc"s);

    ifstream in_b("b.txt"s);
    assert(GetLine(in_b) == "123"s);
}

void CreateFiles(const string& config_file){
    ofstream out_file;
    ifstream in_files(config_file);

    string last_data = GetLine(in_files);
    string last_file;
    
    while(!last_data.empty()){

        if(last_data[0] != '>'){
            out_file.open(last_data);
            last_file = last_data;
            last_data = GetLine(in_files);
            out_file.close();
        }

        out_file.open(last_file);
        while (last_data[0] == '>'){
            last_data = last_data.substr(1);
            out_file << last_data << endl;
            last_data = GetLine(in_files);
        }
    }
}

/* void CreateFiles(const string& config_file) {
    ifstream input_file(config_file);
    ofstream output_file;
    string line;

    while (getline(input_file, line)) {
        if (line[0] != '>') {
            output_file.close();
            output_file.open(line);
            continue;
        }

        output_file << line.substr(1) << endl;
    }
} */