//
// Created by Anirudh Agrawal on 7/19/25.
//

#include <iostream>

int main(const int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <lifo|fifo>" << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
