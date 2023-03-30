#ifndef dirhist_H
#define dirhist_H
#include <filesystem>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>


class DirectoryHistory {
public:
    DirectoryHistory() {
        std::string current_dir = getCurrentDirectory();
        history_.push_back(current_dir);
    }

    // Public member function to add a directory to the history
    void addDirectory(const std::string& dir) {
        history_.push_back(dir);
    }

    bool directoryExists(const std::string& dir) const {
        return std::find(history_.begin(), history_.end(), dir) != history_.end();
    }

    // Public member function to print the directory history
    void printHistory() const {
        std::cout << "Directory history:" << std::endl;
        for (const auto& dir : history_) {
            std::cout << "  " << dir << std::endl;
        }
    }

private:
    // Private member function to get the current directory
    std::string getCurrentDirectory() const {
        return std::filesystem::current_path().string();
    }

    std::vector<std::string> history_;
};
#endif
