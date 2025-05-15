#include <iostream>
#include <utility>
// to print a new line when we have no more arguments 
void myPrint() {
    std::cout << std::endl;
}

template<typename First, typename... Rest>
void myPrint(First&& first, Rest&&... rest) {
    std::cout << std::forward<First>(first);
    
    if (sizeof...(rest) > 0) {
        std::cout << " ";
    }
    
    myPrint(std::forward<Rest>(rest)...);
}

int main() {
    int x = 50;
    const std::string Hi = "Hi";
    double d = 99.99;
    
    myPrint("Start:");
    myPrint(Hi, "Katia!", x, d);
    myPrint("Values:", x, "and", d, "end");
    
    myPrint("Anastasia:", x);
    myPrint("Sara:", 13);
    myPrint("Mixed:", Hi, std::string("test"), 4.548621);
    
    return 0;
}