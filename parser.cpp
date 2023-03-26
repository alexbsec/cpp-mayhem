#include "command-parser.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <filesystem>

namespace argparse {

    namespace detail {
        std::vector<std::string_view> _input_files;
        bool _show_service = false;
        bool _show_ports = false;
        int _port;
    }

    const std::vector<std::string_view>& input_files() {
        return detail::_input_files;
    }

    bool show_service() {
        return detail::_show_service;
    }

    int port() {
        return detail::_port;
    }

    bool show_ports() {
        return detail::_show_ports;
    }

    void parse(int argc, char *argv[]) {
        // Make sure user does not exploit input
        if (argc > 64) {
            throw std::runtime_error("Too many input parameters");
        }

        const std::vector<std::string_view> args(argv + 1, argv + argc);

        for (auto it = args.begin(); it != args.end(); it++) {
            if (detail::_input_files.empty()) {
                if (*it == "-p" || *it == "--port") {
                    if (detail::_show_ports) {
                        throw std::runtime_error("cannot use -p/--port twice");
                    }
                    it++;
                    if (it == args.end()) {
                        throw std::runtime_error("-p/--port flag requires an argument");
                    }
                    try {
                        detail::_port = std::stoi(std::string(*it));
                    } catch (const std::exception &e) {
                        throw std::runtime_error(std::string(*it) + " is not a valid port number");
                    }
                    detail::_show_ports = true;
                    continue;
                }
                if (*it == "-sv" || *it == "--service") {
                    if (detail::_show_service) {
                        throw std::runtime_error("cannot use -sv/--service twice");
                    }
                    detail::_show_service = true;
                    continue;
                }
            }
            if (!std::filesystem::exists(*it)) {
                throw std::runtime_error(std::string(*it) + ": No such file");
            }

            detail::_input_files.push_back(*it);
        }
    }
}

int main(int argc, char* argv[]) {

    argparse::parse(argc, argv);

    std::cout << argparse::port() << std::endl;

    return 0;
}