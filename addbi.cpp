#include <iostream>


bool is_binary(int num){

    while (num != 0){
        int rem = num % 10;
        if (rem !=0 && rem != 1){
            return false;
        }
        else{
            num /= 10;
        }
    }
    return true;

}


int addbi(int first, int second){

    int remainder = 0; 
    int sum = 0;
    int counter = 1;



    while (first > 0 || second > 0){

        int num1 = first%10;
        int num2 = second%10;

        int total = num1 + num2 + remainder;


        sum += (total%2) * counter;
        remainder = total / 2;


        counter *=10;
        first /= 10;
        second /= 10;

}
    if (remainder == 1){
        sum += 1 * counter;
    } 
    return sum;
}

int main(){


    int first;
    int second;

    std::cout << "***************The Sum Of Two Binary Numbers***************\n\n";
    std::cout << "The first number: ";
    std::cin >> first;


    std::cout << "The second number: ";
    std::cin >> second;

    if (is_binary(first) == 0 || is_binary(second) == 0){
        std::cout << "Please enter only binary numbers! \n";
    std::cout << "***********************************************************\n";
    }

    else{
    std::cout << "Result: " << addbi(first, second) << '\n' << '\n';

    std::cout << "***********************************************************\n";
    }
    return 0;

}