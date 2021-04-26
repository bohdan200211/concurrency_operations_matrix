#include <thread>
#include <chrono>

#include <Operations.hpp>

int main() {
    Number n1("11234");
    Number n2("567");
//    Number n3("7123");


//    Number MultRes = Operations::NaiveMultiplication(n1, n2);
//    Number SquareRes = Operations::FastSquare(n1);
    Number PowResult = Operations::FastPow(n2, n1);


    std::cout << PowResult/*MultRes*//*SquareRes*/ << std::endl;

    return 0;
}
