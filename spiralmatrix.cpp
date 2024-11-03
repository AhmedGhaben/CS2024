#include <iostream>
#include <vector>

std::vector<std::vector<int>> matrix(int m, int n, const std::vector<int>& list) {
    std::vector<std::vector<int>> matrix(m, std::vector<int>(n, -1));
    int top = 0, bottom = m - 1;
    int left = 0, right = n - 1;
    int integer = 0;

    while (top <= bottom && left <= right && integer < list.size()) {
        for (int i = left; i <= right && integer < list.size(); i++) {
            matrix[top][i] = list[integer++];
        }
        top++;

        for (int i = top; i <= bottom && integer < list.size(); i++) {
            matrix[i][right] = list[integer++];
        }
        right--;

        for (int i = right; i >= left && top <= bottom && integer < list.size(); i--) {
            matrix[bottom][i] = list[integer++];
        }
        bottom--;

        for (int i = bottom; i >= top && left <= right && integer < list.size(); i--) {
            matrix[i][left] = list[integer++];
        }
        left++;
    }

    return matrix;
}

int main() {

    std::cout << "******************Spiral Matrix******************\n";
    int m, n, num;

    std::cout << "Enter m: ";
    std::cin >> m;

    std::cout << "Enter n: ";
    std::cin >> n;

    std::vector<int> list;
    std::cout << "Enter elements (enter a letter to end input): \n";
    while (std::cin >> num) {
        list.push_back(num);
    }


    std::vector<std::vector<int>> result = matrix(m, n, list);
    for (const auto& row : result) {
        for (int number : row) {
            std::cout << number << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << '\n' << "***********************************************\n";


    return 0;
}