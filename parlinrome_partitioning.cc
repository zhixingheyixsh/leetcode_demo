#include <iostream>
#include <vector>

using namespace std;
class Solution {
public:
    vector<vector<string> > partition(string s) {
        const int n = s.size();
        bool p[n][n]; // whether s[i,j] is palindrome
        fill_n(&p[0][0], n * n, false);
        for (int i = n - 1; i >= 0; --i)
            for (int j = i; j < n; ++j)
                p[i][j] = s[i] == s[j] && ((j - i < 2) || p[i + 1][j - 1]);
        
        for (int i = 0; i < n; ++i)
            for (int j = i; j < n; ++j)
                cout << "p[" << i << "]" << "[" << j << "]" << p[i][j] << endl;
        vector<vector<string> > sub_palins[n]; // sub palindromes of s[0,i]
        for (int i = n - 1; i >= 0; --i) {
            for (int j = i; j < n; ++j) {
                if (p[i][j]) {
                    const string palindrome = s.substr(i, j - i + 1);
                    if (j + 1 < n) {
                        for (auto v : sub_palins[j + 1]) {
                            v.insert(v.begin(), palindrome);
                            sub_palins[i].push_back(v);
                        }
                    } else {
                        sub_palins[i].push_back(vector<string> { palindrome });
                    }
                }
            }
        }
        return sub_palins[0];
    }
};


int main(int argc, char *argv[]) {
    if (argc <  2) {
        cout << "usage: " << argv[0] << " string" << endl;
        return 0;
    }
    Solution A;
    //string s1("tsaabbsd");
    string s1(argv[1]);
    cout << "input: is " << s1 << endl;
    cout << "all sub palindromes is " << endl;
    auto res = A.partition(s1);
    cout << "res is " << endl;
    int index = 0;
    for (auto v : res) {
        cout << "[" << index++ <<": ";
        for (auto s:v) {
            cout << s << " ";
        }
        cout << "] " << endl;
    }
    return 0;
}
