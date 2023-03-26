#pragma once
#include <string_view>
#include <vector>
#include <stdexcept>
#include <filesystem>

namespace portparser {

    namespace detail {
        std::vector<std::string_view> _input_files;
        bool _show_service = false;
        bool _show_ports = false;
        std::vector<int> _ports;
        std::string_view _hostname;
    }

    const std::vector<std::string_view>& input_files() {
        return detail::_input_files;
    }

    bool show_service() {
        return detail::_show_service;
    }


    std::string_view hostname() {
        return detail::_hostname;
    }

    std::vector<int> &ports() {
        return detail::_ports;
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
        bool positional_arg_found = false;

        for (auto it = args.begin(); it != args.end(); it++) {
            if (*it != "-p" && *it != "--port" && *it != "-p-" && *it != "-sv" && *it != "--service") {
                if (positional_arg_found) {
                    throw std::runtime_error("only one positional argument is allowed");
                }
                detail::_hostname = *it;
                positional_arg_found = true;
                continue;
            }
            if (detail::_input_files.empty()) {
                if (*it == "-p" || *it == "--port") {
                    if (detail::_show_ports) {
                        throw std::runtime_error("cannot use -p/--port twice");
                    }
                    it++;
                    if (it == args.end()) {
                        throw std::runtime_error("-p/--port flag requires an argument");
                    }
                    std::string port_str(*it);
                    std::stringstream port_stream(port_str);
                    std::string port;
                    while (std::getline(port_stream, port, ',')) {
                        if (port.find('-') != std::string::npos) {
                            // Range of ports
                            size_t pos = port.find('-');
                            int start_port, end_port;
                            try {
                                start_port = std::stoi(port.substr(0, pos));
                                end_port = std::stoi(port.substr(pos + 1));
                            } catch (const std::exception &e) {
                                throw std::runtime_error("invalid port range or port number in range: " + port);
                            }
                            if (start_port > end_port) {
                                throw std::runtime_error("start port cannot be greater than end port");
                            }
                            if (end_port > 65535 || start_port < 1) {
                                throw std::runtime_error("cannot scan ports below 1 or above 65535");
                            }
                            for (int p = start_port; p <= end_port; p++) {
                                detail::_ports.push_back(p);
                            }
                        } else {
                            int port_to_add;
                            try {
                                port_to_add = std::stoi(port);
                                detail::_ports.push_back(port_to_add);
                            } catch (const std::exception &e) {
                                throw std::runtime_error(port + " is not a valid port number");
                            }
                            if (port_to_add > 65535 || port_to_add < 1) {
                                throw std::runtime_error("cannot scan ports below 1 or above 65535");
                            }
                        }
                    }

                    detail::_show_ports = true;
                    continue;
                }
                if (*it == "-p-") {
                    for (int p = 1; p <= 65535; p++) {
                        detail::_ports.push_back(p);
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
                throw std::runtime_error(std::string(*it) + ": No such flag");
            }

            detail::_input_files.push_back(*it);
        }

        if (!positional_arg_found) {
            throw std::runtime_error("no hostname/IP address was passed");
        }
    }
};

