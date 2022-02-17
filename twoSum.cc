// 2022-2-14
// by xish
// vector<int> input: [2, 7, 9, 11]
// out:[0, 1]

#include <vector>
#include <iostream>
#include <unordered_map>
#include <ctime>
#include <sstream>
#include <algorithm>
// resolution1: hash_map

std::vector<int> two_sum(std::vector<int> &nums, int target){
    std::unordered_map<int, int> nums_map;
    std::vector<int> res;
    for (int i = 0; i < nums.size(); ++i) {
        if ( nums_map.find(target - nums[i]) != nums_map.end() ){
            if ( i > nums_map[ target - nums[i] ]) {
                res.push_back(nums_map[ target - nums[i] ]);
                res.push_back(i);
                return res;
            } else {
                res.push_back(i);
                res.push_back(nums_map[ target - nums[i] ]);
                return res;
            }
        }
        nums_map[ nums[i] ] = i;
    }
    return res;
}
//resolution2 : when without std::map
// divide into two steps: quick_sort, binary_search

void quick_sort_v1(std::vector<int> &data, int left, int right) {
	if (left > right)	return;
	int i = left;
	int j = right;
	int base = data[left];
	int tmp = 0;
	while (i < j)
	{
		while (data[j] >= base && i < j)	j--;
		while (data[i] <= base && i < j)	i++;
		if (i < j) {
			tmp = data[i];
			data[i] = data[j];
			data[j] = tmp;
		}
	}
	data[left] = data[i];
	data[i] = base;
	quick_sort_v1(data, left, i - 1);
	quick_sort_v1(data, i + 1, right);
}

void quick_sort_v2(std::vector<int> &x, int left, int right){
    //select the right pivotal
    if (left > right) return;
    int i = left - 1;
    int temp = 0;
    for (int k = left; k < right; ++k){
        if (x[k] < x[right]) {
            //swap
            temp = x[++i];
            x[i] = x[k];
            x[k] = temp;
        }
    }
    // swap pivotal
    temp = x[++i];
    x[i] = x[right];
    x[right] = temp;
    quick_sort_v2(x, left, i - 1);
    quick_sort_v2(x, i + 1, right);

}

void quick_sort_v2_pair(std::vector<std::pair<int, int>> &x, int left, int right){
    //select the right pivotal
    if (left > right) return;
    int i = left - 1;
    std::pair<int,int> temp;
    for (int k = left; k < right; ++k){
        if (x[k].first < x[right].first) {
            //swap
            temp = x[++i];
            x[i] = x[k];
            x[k] = temp;
        }
    }
    // swap pivotal
    temp = x[++i];
    x[i] = x[right];
    x[right] = temp;
    quick_sort_v2_pair(x, left, i - 1);
    quick_sort_v2_pair(x, i + 1, right);
}

int bound_low(std::vector<int> x, int first, int last, int target) {
    int count = last - first;
    int step = 0;
    int it = 0;
    while (count > 0) {
        step = count >> 1;
        it += step;
        if (x[it] < target) {
            first = ++it;
            count -= step + 1;
        }
        count = step;
    }
    return first;
}
int bound_low(std::vector<std::pair<int, int>> x, int first, int last, int target) {
    int count = last - first;
    int step = 0;
    int it = 0;
    while (count > 0) {
        it = first;
        step = count >> 1;
        it += step;
        if (x[it].first < target) {
            first = ++it;
            count -= step + 1;
        }
        count = step;
    }
    return first;
}

int binary_search(std::vector<int> x, int first, int last, int target) {
    int res = bound_low(x, first, last, target);
    if (res < 0 || res >= last || x[res] != target) return -1;
    return res;
}

int binary_search_v2(std::vector<std::pair<int, int>> x, int first, int last, int target) {
    int res = bound_low(x, first, last, target);
    if (res < 0 || res >= last || x[res].first != target) return -1;
    return x[res].second;
}
// binary_search !!! target must be in x[]
int binary_search(std::vector<int> & x, int left, int right, int target ){
    while(left <= right) {
        int mid = left + (right - left) / 2;
        if (x[mid] == target) {
            return mid;
        } else if (x[mid] < target) {
            left = mid + 1;
            // if target may be not in x[], open this commment
            if (left == right) {
                if (x[left] == target) {
                    return left;
                } else {
                    return -1;
                }
            }
        } else {
            right = mid - 1;
        }
    }
    return -1;        
}
int binary_search(std::vector<std::pair<int, int>> x, int left, int right, int target) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (x[mid].first == target) {
            return x[mid].second;
        } else if (x[mid].first < target) {
            left = mid + 1;
            // if target may be not in x[], open this commment
            if (left == right) {
                if (x[left].first == target) {
                    return x[mid].second;
                } else {
                    return -1;
                }
            }
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

std::vector<int> two_sum_v2(std::vector<int> nums, int target){
    int i;
    std::vector<int> res;
    std::vector<std::pair<int, int>> nums_index;
    for(i = 0; i < nums.size(); i++) {
        nums_index.push_back(std::make_pair(nums[i], i));    
    }
    //sort
    quick_sort_v2_pair(nums_index, 0, nums_index.size()-1);
    for (i = 0; i < nums.size(); ++i) {
        //int target_index = binary_search(nums_index, 0, nums_index.size()-1, target-nums[i]);
        int target_index = binary_search_v2(nums_index, 0, nums_index.size(), target-nums[i]);
        if (target_index != -1) {
            if (i < target_index) {
                res.push_back(i);
                res.push_back(target_index);
                break;
            } else {
                res.push_back(i);
                res.push_back(target_index);
                break;
            }
        }
    }
    return res;

}


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
bool cmp(int a, int b){
    return a < b;
}

int main(int argc, char* argv[]){
    if (argc < 3) {
        std::cout << "usage: " << argv[0] << " [len of input vector]  [range of everyone]" << std::endl;
        return -1;
    }
    int len = convert<int>(argv[1]);
    unsigned int range = convert<unsigned int >(argv[2]);
    //std::string s1("8");
    //std::string s2("20");
    std::cout << "len is " << len << std::endl;
    std::cout << "range is " << range << std::endl;
    std::vector<int> num2(len, 0);
    srand((unsigned)time(0));
    std::cout << "\ninput data :" << std::endl;
    unsigned int ind = 0;
    // test quick_sort
    /*
    for (auto &k: num2){
        ind++;
        k = rand() % range;
        std::cout << k << "\t";
        if ( (ind & 7) == 0) {
            std::cout << std::endl;
        }
    }
    auto res0(num2);
    std::sort(res0.begin(), res0.end(), cmp);
    auto res1(num2);
    quick_sort_v1(res1, 0, res1.size() - 1);
    auto res2(num2);
    quick_sort_v2(res2, 0, res1.size() - 1);

    bool v1_is_right = diff_two_vector(res0, res1);
    bool v2_is_right = diff_two_vector(res0, res2);
    std::cout << "\n\n\nv1 is :" << v1_is_right << std::endl;
    std::cout << "v2 is :" << v2_is_right << std::endl;
    */
    
    //for (auto k : res){
    //    std::cout << k << std::endl;
    //}

    // test two_sum
    std::vector<int> num1({0, 2, 11, 7, 8, 4, 15});
    auto res1 = two_sum(num1, 9);
    std::cout << "res1 is: " << std::endl;
    for (auto & t: res1){
        std::cout << t << std::endl;
    }
    auto res2 = two_sum_v2(num1, 9);
    std::cout << "res2 is: " << std::endl;
    for (auto & t: res2){
        std::cout << t << std::endl;
    }
    return 0;
}

