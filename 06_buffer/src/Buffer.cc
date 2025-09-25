#include <Buffer.hh>

std::unique_ptr<Buffer> Buffer::create(GLenum type, GLsizeiptr data_size, const void* data, GLenum usage) {
    GLuint buffer = 0;

    glGenBuffers(1, &buffer);
    SPDLOG_INFO("Created buffer({})", buffer);
    glBindBuffer(type, buffer);
    glBufferData(type, data_size, data, usage);

    return std::unique_ptr<Buffer>(new Buffer(buffer, type, usage));
}

GLuint Buffer::get() const {
    return buffer;
}

void Buffer::bind() const {
    glBindBuffer(type, buffer);
}

Buffer::Buffer(GLuint buffer, GLenum type, GLenum usage) : buffer(buffer), type(type), usage(usage) {}

Buffer::~Buffer() {
    glDeleteBuffers(1, &buffer);
    SPDLOG_INFO("Destroyed buffer({})", buffer);
}