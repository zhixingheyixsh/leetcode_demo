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
    int i, j;
    std::vector<std::vector<int>> dp(str.size(), std::vector<int>(str.size(), 0));
    //init boundary
    for (i = 0; i < str.size() - 1; i++) {
        dp[i][i] = 1;
        dp[i][i+1] = (str[i]==str[i+1]);
    }
    int max_len = 0;
    int begin = 0, end = 0;
    for (i = str.size() - 2; i >= 0; i--) {
        for (j = i + 2; j <  str.size(); j++) {
            if (dp[i+1][j-1] == 1) {
                if (str[i] == str[j]) {
                    dp[i][j] = 1;
                    int temp = j - i + 1;
                    if (max_len < temp) {
                        max_len = temp;
                        begin = i;
                        end = j;
                    }
                }
            } else {
                dp[i][j] = 0;
            }
        }
    }
    return str.substr(begin, end - begin + 1);
}

std::string longPalindrome_center_extend(const std::string str) {
    std::string data = preprocess(str);
    int len = data.length();
    int i, j;
    int center_pos = 0;
    int round = 0;
    std::string res;
    for (i = 0; i < len; ++i) {
        //center pivilot char
        j = 1;
        while (i + j < len && i - j >= 0) {
            if (data[i+j]!=data[i-j]) {
                break;
            }
            j++;
        }
        if (round < j) {
            round = j;
            center_pos = i;
        }
    }
    // !!! round is one more than the real longth
    return str.substr((center_pos - round  + 1)/2, round - 1);
}


int main(int argc, char* argv[]){
    std::vector<std::string> vec_str;
    unsigned int ind = 0;
    vec_str.emplace_back("ab");
    vec_str.emplace_back("fabcddcbae");
    vec_str.emplace_back("mmsgbg");
    vec_str.emplace_back("gabaf");
    vec_str.emplace_back("f");
    for (auto &k : vec_str){        
        std::cout << "input: " << k << std::endl;
        std::cout << "[dp] out: " << longPalindrome_dp(k) << std::endl;
        //std::cout << preprocess(k) << std::endl;
        std::cout << "[center_extend] out: " << longPalindrome_center_extend(k) << std::endl;
    }
    std::cout << "----------------" << std::endl;
    return 0;
}

