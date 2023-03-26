#include <string_view>
#include <vector>
#include <stdexcept>

namespace ProgramOptions {

    void parse(int argc, char *argv[]);

    const std::vector<std::string_view> &input_files();
    bool show_ends();
    bool show_line_numbers();
};

void ProgramOptions::parse(int argc, char *argv[]) {
    if (argc > 64) {
        throw std::runtime_error("Too many input parameters");
    }
    const std::vector<std::string_view> args(argv + 1, argv + argc);
}