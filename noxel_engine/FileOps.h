#pragma once
#include <fstream>
#include <streambuf>
#include <string>

class FileOps {
public:
	static void load_shader(const std::string& file_path, std::string& source);

private:
	FileOps() {};
};

