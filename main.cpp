#include <iostream>
#include <vector>
#include <algorithm>  // 包含 std::copy 算法
#include <iterator>   // 包含 std::back_inserter

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    // 复制向量中的元素到另一个位置
    std::copy(vec.begin()+1, vec.end()-1, vec.begin());

    // 输出复制后的 vector
    std::cout << "After copy: ";
    for (int num : vec) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
