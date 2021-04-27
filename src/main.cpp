#include <thread>
#include <chrono>

#include <Operations.hpp>

int main() {
    Number n1("21");
    Number n2("53");
//    Number n3("7123");


    Number MultRes = Operations::ConcurrencyMultiplication<2>(n1, n2);
//    Number SquareRes = Operations::FastSquare(n1);
//    Number PowResult = Operations::FastPow(n2, n1);


    std::cout << /*PowResult*/MultRes/*SquareRes*/ << std::endl;

    return 0;
}
