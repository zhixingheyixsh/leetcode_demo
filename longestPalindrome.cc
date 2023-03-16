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
    res.push_back('$');
    for (auto &k : str) {
        res.push_back('#');
        res.push_back(k);
    }
    res.push_back('#');
    return res;
}

static int min(int x, int y) {
    return x > y ? y : x;
}

std::string longPalindrome_dp3(const std::string str) {
    auto s1 = preprocess(str);
    int len = s1.size();
    std::vector<int> P(len, 0);
    int mx = 0, id = 0;
    for (int i = 1; i < len; ++i) {
        P[i] = mx > i ? min(P[2 * id - i], mx - i): 1;
        while (s1[i + P[i]] == s1[i - P[i]]) P[i]++;
        if (mx < i + P[i]) {
            mx = i + P[i];
            id = i;
        }
    }
    id = 0;
    for (int i = 1; i < len; ++i) {
        if (id < P[i])  id = i;
    }
    return str.substr((id - P[id])/2, P[id] - 1);
    //return str.substr((id - 1/2), P[id]/2);
}

std::string longPalindrome_dp2(const std::string str) {
    int M = str.size();
    std::vector<std::vector<int> > dp(M, std::vector<int>(M, 0));
    int left,  max_len = 0;
    for (int i = M-1; i >= 0; --i) {
        for (int j = i; j < M ; ++j) {
            // || , when first is true, return 1
            dp[i][j] = str[i] == str[j] && (j - i < 2 || dp[i + 1][j - 1]);
            if (dp[i][j]) {
                if (max_len < j - i + 1) {
                    max_len = j - i + 1;
                    left = i;
                }
            }
        }
    }
    return str.substr(left, max_len);
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
    //vec_str.emplace_back("ab");
    vec_str.emplace_back("12212321");
    vec_str.emplace_back("fabcddcbae");
    vec_str.emplace_back("mmsgbg");
    vec_str.emplace_back("gabaf");
    vec_str.emplace_back("f");
    for (auto &k : vec_str){        
        std::cout << "input: " << k << std::endl;
        std::cout << "[dp] out: " << longPalindrome_dp(k) << std::endl;
        std::cout << "[dp2] out: " << longPalindrome_dp2(k) << std::endl;
        std::cout << "[dp3] out: " << longPalindrome_dp3(k) << std::endl;
        //std::cout << preprocess(k) << std::endl;
        std::cout << "[center_extend] out: " << longPalindrome_center_extend(k) << std::endl;
    }
    std::cout << "----------------" << std::endl;
    return 0;
}

