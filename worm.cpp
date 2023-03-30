#include <filesystem>
#include <iostream>
#include <fstream>
#include <vector>
#include "dir-hist.h"

DirectoryHistory dirhist;
std::string first_origin = std::filesystem::current_path();
std::string file_path = first_origin + "/worm";

std::vector<std::string> checkSubDir(const std::string &path) {
    return;
}

std::filesystem::path run(std::filesystem::path origin, std::vector<std::string> sub_dirs) {
    return;
}

void deleteAll(std::filesystem::path path) {
    return;
}

void propagate(std::string destination) {
    return;
}

int main() {
    return 0;
}


