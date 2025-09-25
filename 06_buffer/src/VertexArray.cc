#include <VertexArray.hh>

std::unique_ptr<VertexArray> VertexArray::create() {
    GLuint vertex_array = 0;

    glGenVertexArrays(1, &vertex_array);
    SPDLOG_INFO("Created vertex array({})", vertex_array);

    return std::unique_ptr<VertexArray>(new VertexArray(vertex_array));
}

void VertexArray::set(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* offset) {
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, size, type, normalized, stride, offset);
}

GLuint VertexArray::get() const {
    return vertex_array;
}

void VertexArray::bind() const {
    glBindVertexArray(vertex_array);
}

VertexArray::VertexArray(GLuint vertex_array) : vertex_array(vertex_array) {}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &vertex_array);
    SPDLOG_INFO("Destroyed vertex array({})", vertex_array);
}