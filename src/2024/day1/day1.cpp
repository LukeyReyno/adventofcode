#include "common/logging/logging.h"

int main() {
    AOC::Log(AOC::LogLevel::INFO, "Suh dude: ", 1);
    AOC::Log(AOC::LogLevel::ERROR, "Suh dude: ", 2);
    return 0;
}
