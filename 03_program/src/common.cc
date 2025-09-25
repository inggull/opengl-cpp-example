#include <common.hh>

std::expected<std::string, std::string> load_file(const std::string &file_path) {
    std::ifstream file(file_path, std::ios::binary);
    if (!file.is_open()) {
        return std::unexpected(std::format("Failed to open file \"{}\"", file_path));
    }

    file.seekg(0, std::ios::end);
    size_t size = file.tellg();
    std::string content;
    content.resize(size);
    file.seekg(0, std::ios::beg);
    file.read(&content[0], size);

    return content;
}