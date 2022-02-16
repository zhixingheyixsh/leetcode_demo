// 2022/2/26
#include <iostream>
#include <vector>
#include <algorithm>

int longestSubstrUnrepeat_v1(const std::string x) {
    int res = 1;
    std::vector<int> hist(128);
    int len = x.size();
    int i, j;
    int max_len = 1;
    for (i = 0; i < len - 1; i++) {
        std::fill(hist.begin(), hist.end(), 0);
        hist[x[i] - '0']++;
        for (j = i + 1; j < len; j++) {
            if (hist[ x[j] - '0'] == 0) {
                hist[x[j] - '0']++;
            } else {
                max_len = (j - i > max_len ? j - i : max_len);
                break;
            }
        }
    }
    return max_len;
}
int longestSubstrUnrepeat_v2(const std::string x) {
    //sliding window
    if (x.size() < 1)   return 0;
    int res = 1;
    std::vector<int> hist(128);
    int len = x.size();
    int left, right = -1;
    int max_len = 1;
    for (left = 0; left < len;) {
        if (right + 1 < len && hist[x[right + 1] - '0'] == 0) {
            hist[x[right + 1] - '0']++;
            right ++;
        } else {
            hist[x[left] - '0']--;
            left++;           
        }
        max_len = (max_len < right - left + 1 ? right - left + 1 : max_len);
    }
    return max_len;
}

int main() {
    std::string test1("abcabcbb");
    std::string test2("bbb");
    std::string test3("pwwkew");
    std::cout << "input:\n" << test1 << std::endl;
    std::cout << longestSubstrUnrepeat_v1(test1) << std::endl;
    std::cout << "input:\n" << test2 << std::endl;
    std::cout << longestSubstrUnrepeat_v1(test2) << std::endl;
    std::cout << "input:\n" << test3 << std::endl;
    std::cout << longestSubstrUnrepeat_v1(test3) << std::endl;
    std::cout << "v2 result is " << std::endl;

    std::cout << "input:\n" << test1 << std::endl;
    std::cout << longestSubstrUnrepeat_v2(test1) << std::endl;
    std::cout << "input:\n" << test2 << std::endl;
    std::cout << longestSubstrUnrepeat_v2(test2) << std::endl;
    std::cout << "input:\n" << test3 << std::endl;
    std::cout << longestSubstrUnrepeat_v2(test3) << std::endl;

    return 0;
}

