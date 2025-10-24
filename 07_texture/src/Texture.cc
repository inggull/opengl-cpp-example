#include <Texture.hh>

std::unique_ptr<Texture> Texture::create(std::shared_ptr<Image> image) {
    GLuint texture{0};

    glGenTextures(1, &texture);
    SPDLOG_INFO("Created texture({})", texture);
    // bind and set default filter and wrap option
    glBindTexture(GL_TEXTURE_2D, texture);
    set_wrap(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
    set_filter(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    set_texture(image);

    return std::unique_ptr<Texture>(new Texture(texture));
}

GLuint Texture::get() {
    return texture;
}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, texture);
}

Texture::~Texture() {
    glDeleteTextures(1, &texture);
    SPDLOG_INFO("Dropped texture({})", texture);
}

Texture::Texture(GLuint texture) : texture(texture) {}

void set_filter(GLenum min_filter, GLenum mag_filter) {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);
}

void set_wrap(GLenum wrap_s, GLenum wrap_t) {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t);
}

void set_texture(std::shared_ptr<Image> image) {
    GLenum format;

    switch (image->get_channel_count()) {
    case 1:
        format = GL_RED;
        break;

    case 2:
        format = GL_RG;
        break;

    case 3:
        format = GL_RGB;
        break;

    default:
        format = GL_RGBA;
        break;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->get_width(), image->get_height(), 0, format, GL_UNSIGNED_BYTE, image->get_data());
    glGenerateMipmap(GL_TEXTURE_2D);
}