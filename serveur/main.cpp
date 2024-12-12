
#include <iostream>
#include "UDPServer.hpp"

int main() {
    try {
        UDPServer(4242);
        while(true) {
            sleep(1);
            std::cout << "loop" << std::endl;
        };
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}