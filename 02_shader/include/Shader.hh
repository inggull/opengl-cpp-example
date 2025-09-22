#ifndef __SHADER_HH__
#define __SHADER_HH__

#include <common.hh>

class Shader {
  public:
    static std::expected<std::unique_ptr<Shader>, std::string> create(const std::string &file_path, GLenum shader_type);
    GLuint get() const;
    ~Shader();

  private:
    Shader(GLuint shader);
    GLuint shader;
};

#endif