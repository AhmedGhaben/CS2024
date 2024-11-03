#include <iostream>
#include <unordered_map>

std::string kth_Distinct(const std::string array[], int size, int k) {
    std::unordered_map<std::string, int> repetition;


    int distinct_Numbers = 0;


    for (int i = 0; i < size; i++) {
        repetition[array[i]]++;
    }

    for (int i = 0; i < size; i++) {
        if (repetition[array[i]] == 1) { 
            distinct_Numbers++;
            if (distinct_Numbers == k) {
                return array[i]; 
            }
        }
    }

    return ""; 
}

int main() {
    

    int k;
    int size;

    std::cout << "********************Distinct String********************\n\n";
    std::cout << "How many elements would you like to input? ";
    std::cin >> size;
    std::string array[size];

    for (int i = 0; i < size; i++){
        std::cout << "Enter the elements: ";
        std::cin >> array[i]; 
    }
    
    std::cout << "What is k? ";
    std::cin >> k;
    std::cout << "Result: " << kth_Distinct(array, size, k) << "\n\n";
    std::cout << "*******************************************************";


    return 0;
}
