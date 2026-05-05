#include <iostream>
#include <string>
#include <set>
using namespace std;

int main() {
    string s;
    cout << "Enter the username: ";
    cin >> s;
    set<char> st(s.begin(), s.end());
    
    if (st.size() % 2 == 0)
        cout << "CHAT WITH HER!" << endl;
    else
        cout << "IGNORE HIM!" << endl;
    return 0;
} 