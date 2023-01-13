#include "FileOps.h"
#include <iostream>

/// reads shader source file into a string which we can later use for compilation
/// and other shader related operations.
void FileOps::load_shader(const std::string& file_path, std::string& source) {
    std::cout << " writing source to string..." << std::endl;
    std::ifstream in(file_path);
    std::string shader_source((std::istreambuf_iterator<char>(in)),
        std::istreambuf_iterator<char>());
    source = shader_source;
}
