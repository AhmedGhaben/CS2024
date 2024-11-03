#include <iostream>



int main(){
    
    int i;
    std::cout << "*************Pascal's Triangle*************\n" << '\n';
    std::cout << "Input rowIndex: ";
    std::cin >> i;

    int row[i+1];
    row[0] = 1;
    for (int j = 1; j <= i; j++){
        row[j] = row[j-1] * ( i - j + 1) / j;
    }

    for ( int p = 0; p < i+1; p++){ 
        std::cout << row[p] << ' ';
    }

    std::cout << "\n\n" << "******************************************\n" << '\n';

    return 0;
}