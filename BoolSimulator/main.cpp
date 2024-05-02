#include <iostream>
#include <string>
#include <stack>

#include "BoolSimulator.h"

int main() {

    std::stack<char> data; // initialize stack
    std::string inp; // input string

    std::cout << "\n~[ BOOLEAN LOGIC SIMULATOR ]~\n";
    std::cout << "\nPress q or Q anytime to quit.\n";

    while (1) {

        std::cout << "\nInput Expression: ";
        std::getline(std::cin, inp); // prompt for user input
        
        if (inp == "q" || inp == "Q") {
            std::cout << "Goodbye...\n\n";
            break;
        }

        BoolSimulator bool_sim;
        std::string a = (bool_sim.calculate(inp) ? "True" : "False"); // calculate expression
        std::cout << inp << " = " << a << std::endl;
    }

    return 0;

}