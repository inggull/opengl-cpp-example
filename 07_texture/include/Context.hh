#ifndef __CONTEXT_HH__
#define __CONTEXT_HH__

#include <common.hh>
#include <Shader.hh>
#include <Program.hh>
#include <VertexArray.hh>
#include <Buffer.hh>
#include <Image.hh>
#include <Texture.hh>

class Context {
public:
    static std::expected<std::unique_ptr<Context>, std::string> create();
    void render() const;

private:
    Context(std::unique_ptr<Program> program, std::unique_ptr<VertexArray> vao, std::unique_ptr<Buffer> vbo, std::unique_ptr<Buffer> ebo, std::unique_ptr<Texture> tbo1, std::unique_ptr<Texture> tbo2);
    std::unique_ptr<Program> program;
    std::unique_ptr<VertexArray> vao;
    std::unique_ptr<Buffer> vbo;
    std::unique_ptr<Buffer> ebo;
    std::unique_ptr<Texture> tbo1;
    std::unique_ptr<Texture> tbo2;
};

#endif // __CONTEXT_HH__