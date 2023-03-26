#pragma once
#include <string_view>
#include <vector>
#include <stdexcept>
#include <filesystem>

namespace argparse {

    void parse(int argc, char *argv[]);

    const std::vector<std::string_view>& input_files();
    bool show_service();
    bool show_ports();
    std::vector<int> &ports();

    // Implementation details
    namespace detail {
        extern std::vector<std::string_view> _input_files;
        extern bool _show_service;
        extern bool _show_ports;
        extern std::vector<int> _ports;
    }
};
