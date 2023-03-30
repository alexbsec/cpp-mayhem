#include <filesystem>
#include <iostream>
#include <fstream>
#include <vector>
#include "dir-hist.h"

DirectoryHistory dirhist;
std::string first_origin = std::filesystem::current_path();
std::string file_path = first_origin + "/worm";


