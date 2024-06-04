#include <iostream>
#include <string>

using namespace std;

bool IncreaseStr (string& str1, int i){
    if (str1.empty()) {
        return false;
    }

    if (str1[i] == 'Z') {
        //str1 += 'A';
        return false;
    }

    if (str1[i] < 'Z') {
        ++str1[i];
        return true;
    }
}

template <typename F>
string BruteForce(F check) {
    // верните строку str, для которой check(str) будет true
    const string initial_str = "AAAAA"s;
    string str = BruteForceInternal(check, initial_str, initial_str.length());
    return str;
}

template <typename F>
string BruteForceInternal(F check, const string& begin, int n){
    string str (begin);
    int cur = 0;

    if (check(str)) {
        return str;
    }
    else {
        while (IncreaseStr(str, cur))
        {   
            if (check(str)) {
                return str;
            }
           
        }
        ++cur;
    }
    
}



int main() {
    string pass = "ARTUR"s;
    auto check = [pass](const string& s) {
        return s == pass;
    };
    cout << BruteForce(check) << endl;
}