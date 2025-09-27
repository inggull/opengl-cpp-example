#ifndef __TEXTURE_HH__
#define __TEXTURE_HH__

#include <common.hh>
#include <Image.hh>

class Texture {
public:
    static std::unique_ptr<Texture> create(std::shared_ptr<Image> image);
    GLuint get();
    void bind();
    ~Texture();

private:
    Texture(GLuint texture);
    GLuint texture;
};

void set_filter(GLenum min_filter, GLenum mag_filter);
void set_wrap(GLenum wrap_s, GLenum wrap_t);
void set_texture(std::shared_ptr<Image> image);

#endif // __TEXTURE_HH__