#include <iostream>

#include <kos/random/random_api.h>

int main() {
    std::cerr << "Started!" << std::endl;
    size_t random;
    /*
     * return something like this >>> [17965291858125854928] <<<
     */
    if (KosRandomGenerate(sizeof random, &random))
    {
        std::cerr << "KosRandomGenerate() failed" << std::endl;
        return EXIT_FAILURE;
    }
    std::cerr << ">>> [" << random << "] <<<" << std::endl;
    return 0;
}
