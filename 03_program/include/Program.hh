#ifndef __PROGRAM_HH__
#define __PROGRAM_HH__

#include <03_program/include/common.hh>
#include <03_program/include/Shader.hh>

class Program {
public:
    static std::expected<std::unique_ptr<Program>, std::string> create(const std::vector<std::shared_ptr<Shader>>& shaders);
    GLuint get() const;
    ~Program();

private:
    Program(GLuint program);
    GLuint program;
};

#endif