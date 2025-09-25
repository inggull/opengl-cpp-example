#ifndef __CONTEXT_HH__
#define __CONTEXT_HH__

#include <common.hh>
#include <Shader.hh>
#include <Program.hh>

class Context {
public:
    static std::expected<std::unique_ptr<Context>, std::string> create();
    void render() const;
    ~Context();

private:
    Context(std::unique_ptr<Program> program, uint32_t vao);
    std::unique_ptr<Program> program;
    uint32_t vao;
};

#endif