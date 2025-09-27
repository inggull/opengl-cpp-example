#ifndef __VERTEX_ARRAY_HH__
#define __VERTEX_ARRAY_HH__

#include <common.hh>

class VertexArray {
public:
    static std::unique_ptr<VertexArray> create();
    void set(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* offset);
    GLuint get() const;
    void bind() const;
    ~VertexArray();

private:
    VertexArray(GLuint vertex_array);
    GLuint vertex_array;
};

#endif // __VERTEX_ARRAY_HH__