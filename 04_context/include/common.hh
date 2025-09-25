#ifndef __COMMON_HH__
#define __COMMON_HH__

#include <iostream>
#include <fstream>
#include <format>
#include <expected>

#include <spdlog/spdlog.h>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

std::expected<std::string, std::string> load_file(const std::string &file_path);

#endif