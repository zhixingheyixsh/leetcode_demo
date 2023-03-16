
#include <vector>
#include <iostream>
using namespace std;
class Solution {
public:
    Solution() {
        cout << "base construct" << endl;
        a = 0;
        b = 1;
        c = 2;
    }
    ~Solution() {
        cout << "base deconstruct" << endl;
    }

    int unique_paths(int M, int N) {
        if (M < 1 || N < 1) return 0;
        if (M == 1 || N == 1) return 1;
        f = vector<vector<int> >(M, vector<int>(N, 0));
        f[0][0] = 1;
        return dfs2(M - 1, N - 1);
    }
    //record 
    int dfs2(int m, int n) {
        if (m < 0 || n < 0) return 0;
        if (m == 0 || n == 0) return f[0][0];
        if (f[m][n] > 0 ) {
            return f[m][n];
        } else {
            return dfs2(m - 1, n) + dfs2(m, n- 1);
        }
    }


    int dfs(int m, int n) {
        if (m < 1 || n < 1) return 0;
        if (m==1 && n==1) 
            return 1;
        return dfs(m-1, n) + dfs(m, n-1);
    }

    int dp1(int M, int N) {
        if (M < 1 || N < 1)  return 0;
        if (M == 1 || N == 1)  return 1;
        vector<vector<int> >p(M, vector<int>(N, 0));
        int m, n;
        for (m = 0; m < M; m++) p[m][0] = 1;
        for (n = 0; n < N; n++) p[0][n] = 1;
        for (m = 1; m < M; m++) {
            for (n = 1; n < N; n++) {
                // state translate p[i][j] = p[i-1][j] + p[i][j-1]
                p[m][n] = p[m-1][n] + p[m][n-1];
            }
        }
        return p[m-1][n-1];
    }

    int dp2(int M, int N) {
        if (M < 1 || N < 1)  return 0;
        if (M == 1 || N == 1)  return 1;
        if ( M < N) return dp2(N, M);
        int m, n;
        vector<int> f(N, 0);
        f[0] = 1;
        for (m = 0; m < M; ++m) {
            for (n = 1; n < N; ++n) {
                f[n] += f[n-1];
            }
        }
        return f[N-1];
    }

    /*
    Solution(int x, int y):rows(x), cols(y) {
        cout << "base with para construct" << endl;
    }
    */

    int a;
protected:
    int b;
private:
    vector<vector<int>> f; //cache
    int c;
};

class child : public Solution {
    public:
    child (int x, int y) {
        cout << "child with para construct" << endl;
    }

    child() {
        cout << "child construct" << endl;
        cout << "child : a is " << a << endl;
        cout << "child : b is " << b << endl;
    }
    ~child() {
        cout << "child deconstruc" << endl;
    }
    protected:
    private:
    int c;

};

int main(int argc, char * argv[]) {
    /* input: M * N , DP algorithm

       */
    if (argc != 3) {
        std::cout << "usage: " << argv[0] << " row[]" << "cols[]" << endl;
        return -1;
    }
    Solution A;
    cout << "input: [m]: " << argv[1] << "   [n]: " << argv[2] << endl;;
    cout << "dp1: " << A.dp1(stoi(argv[1]), stoi(argv[2])) << endl;
    cout << "dp2: " << A.dp2(stoi(argv[1]), stoi(argv[2])) << endl;
    cout << "dfs: " << A.dfs(stoi(argv[1]), stoi(argv[2])) << endl;
    cout << "dfs2: " << A.unique_paths(stoi(argv[1]), stoi(argv[2])) << endl;
    //A.dfs
    return 0;
}

