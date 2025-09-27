#define STB_IMAGE_IMPLEMENTATION
#include <Image.hh>

std::expected<std::unique_ptr<Image>, std::string> Image::load(const std::string &file_path) {
    // 이미지 파일과 OpenGL은 이미지의 시작점이 상하 대칭 관계에 있기 때문에 불러온 이미지 파일을 상하 반전시켜야 한다
    stbi_set_flip_vertically_on_load(true);

    int32_t width;
    int32_t height;
    int32_t channel_count;
    uint8_t *data = stbi_load(file_path.c_str(), &width, &height, &channel_count, 0);

    if (data == nullptr) {
        return std::unexpected(std::format("Failed to load image \"{}\"", file_path));
    }

    return std::unique_ptr<Image>(new Image(width, height, channel_count, data));
}

int32_t Image::get_width() const {
    return width;
}

int32_t Image::get_height() const {
    return height;
}

int32_t Image::get_channel_count() const {
    return channel_count;
}

const uint8_t *Image::get_data() const {
    return data;
}

Image::~Image() {
    stbi_image_free(data);
    SPDLOG_INFO("Destroyed image");
}

Image::Image(int32_t width, int32_t height, int32_t channel_count, uint8_t *data) : width(width), height(height), channel_count(channel_count), data(data) {}