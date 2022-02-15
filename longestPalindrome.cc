// 2022-2-15
// by xish

#include <vector>
#include <iostream>
#include <unordered_map>
#include <ctime>
#include <sstream>
#include <algorithm>


template <class out_type, class input_type>
out_type convert(const input_type &t) {
    std::stringstream ss;
    ss << t;
    out_type result;
    ss >> result;
    return result;
}

bool diff_two_vector(std::vector<int> x,std::vector<int> y) {
    if (x.size() != y.size()) {
        return false;
    }
    for (int i = 0; i < x.size(); ++i) {
        if (x[i] != y[i])   return false;
    }
    return true;
}

std::string preprocess(const std::string str) {
    std::string res;
    for (auto &k : str) {
        res.push_back('#');
        res.push_back(k);
    }
    res.push_back('#');
    return res;
}

//resolution1: dynamic programing
std::string  longPalindrome_dp(const std::string str) {
    std::string data = preprocess(str);
    int i, j;
    std::vector<std::vector<int>> dp(str.size(), 0);
    for ( auto &t: dp) {
        t.push_back(std::vector<int>(str.size()));
    }
    //init
    for (i = 0; i < str.size(); i++) {
        dp[i][i] = 1;
    }
    for (i = 1; i < str.size(); i++) {
        if (dp[0][i-1] == 1) {
        } else {

        }
    }

    for (i = str.size() -1 ; i > 0; i--) {

    }
    // i < j
    for (i = 0; i < str.size(); ++i) {
        for (j = i + 1; j < str.size(); ++j) {
            if (dp[][])
        }
    }
    return str.substring();
}
int main(int argc, char* argv[]){
    std::vector<std::string> vec_str;
    unsigned int ind = 0;
    vec_str.emplace_back("aaaaaab");
    vec_str.emplace_back("fabcddcbae");
    vec_str.emplace_back("mmsgbg");
    vec_str.emplace_back("gabaf");
    std::cout << "input vector<string> is " << std::endl;
    for (auto &k : vec_str){        
        std::cout << preprocess(k) << std::endl;
    }
    return 0;
}

