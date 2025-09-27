#ifndef __BUFFER_HH__
#define __BUFFER_HH__

#include <common.hh>

class Buffer {
public:
    static std::unique_ptr<Buffer> create(GLenum type, GLsizeiptr data_size, const void *data, GLenum usage);
    GLuint get() const;
    void bind() const;
    ~Buffer();

private:
    Buffer(GLuint buffer, GLenum type, GLenum usage);
    GLuint buffer;
    GLenum type;
    GLenum usage;
};

#endif // __BUFFER_HH__