#ifndef __PROGRAM_HH__
#define __PROGRAM_HH__

#include <common.hh>
#include <Shader.hh>

class Program {
public:
    static std::expected<std::unique_ptr<Program>, std::string> create(const std::vector<std::shared_ptr<Shader>> &shaders);
    GLuint get() const;
    void use() const;
    ~Program();

private:
    Program(GLuint program);
    GLuint program;
};

#endif // __PROGRAM_HH__