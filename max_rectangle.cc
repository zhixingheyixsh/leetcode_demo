// 2022-2-22
// by xish

#include <vector>
#include <iostream>
#include <unordered_map>
#include <ctime>
#include <sstream>
#include <algorithm>


void print_vec(const std::vector<int> in) {
    int len = in.size();
    int i, j;
    int max_v = 0;
    for (auto k : in){        
        if (k > max_v) {
            max_v = k;
        }
    }
    for (i = 0; i < max_v; i++) {
        for(j = 0; j < len; j++) {
            if (max_v - in[j] <= i) {
                std::cout << "*";
            } else {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}
int maxRectangleArea(const std::vector<int> x) {
    int len = x.size();
    std::vector<int> dp1(len, 0);
    std::vector<int> dp2(len, 0);
    for (int i = 1; i < len; i++) {
        dp1[i] = std::max(dp1[i-1], x[i-1]);
    }
    for (int i = len - 2; i >= 0; i--) {
        dp2[i] = std::max(dp2[i+1], x[i+1]);
    }
    int sum = 0;
    for (int i = 1; i < len - 1; i++) {
        for (left = i - 1; left >= 0; left--) {
            if (x[left]<x[i])   break;
        }
        int temp = std::min(dp1[i], dp2[i]) - x[i];
        sum += (temp > 0 ? temp : 0);
    }
    return sum;
}

int maxRectangleArea_v2(const std::vector<int> x) {
    int len = x.size();
    std::vector<int> dp1(len, 0);
    std::vector<int> dp2(len, 0);
    for (int i = 1; i < len; i++) {
        dp1[i] = std::max(dp1[i-1], x[i-1]);
    }
    for (int i = len - 2; i >= 0; i--) {
        dp2[i] = std::max(dp2[i+1], x[i+1]);
    }
    int sum = 0;
    for (int i = 1; i < len - 1; i++) {
        int temp = std::min(dp1[i], dp2[i]) - x[i];
        sum += (temp > 0 ? temp : 0);
    }
    return sum;
}

int main(int argc, char* argv[]){
    std::vector<int> in({4, 2, 0, 3, 2, 5});
    std::vector<int> in_2({0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1});
    std::cout << "------input vector is --------" << std::endl;
    print_vec(in);    
    std::cout << "------input vector is --------" << std::endl;
    print_vec(in_2);    
    std::cout << "------out max rain value is  --------" << std::endl;
    std::cout << rain(in) << std::endl;
    std::cout << rain(in_2) << std::endl;
    std::cout << "------out max rain v2 value is  --------" << std::endl;
    std::cout << rain_v2(in) << std::endl;
    std::cout << rain_v2(in_2) << std::endl;
    return 0;
}

