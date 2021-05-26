#include <iostream>
#include "engine.h"

int main() {
    if(createWindow("sdl window") == 0) {
        std::cout << "programm finished sucesfully" << std::endl;
    } else {
        std::cout << "sumething fucked up!" << std::endl;
    }
    return 0;
}