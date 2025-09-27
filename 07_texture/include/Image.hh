#ifndef __IMAGE_HH__
#define __IMAGE_HH__

#include <common.hh>
#include <stb_image.h>

class Image {
public:
    static std::expected<std::unique_ptr<Image>, std::string> load(const std::string &file_path);
    int32_t get_width() const;
    int32_t get_height() const;
    int32_t get_channel_count() const;
    const uint8_t *get_data() const;
    ~Image();

private:
    Image(int32_t width, int32_t height, int32_t channel_count, uint8_t *data);
    int32_t width;
    int32_t height;
    int32_t channel_count;
    uint8_t *data;
};

#endif // __IMAGE_HH__