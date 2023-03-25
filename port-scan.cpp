#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <vector>

void portScan(std::string host, std::vector<int> ports) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
}
