#include <Shader.hh>

std::expected<std::unique_ptr<Shader>, std::string> Shader::create(const std::string& file_path, GLenum shader_type) {
    // Load shader file
    auto content = load_file(file_path);
    if (!content)
        return std::unexpected(content.error());

    size_t content_length = content.value().length();
    const char *chr = content.value().c_str();

    // Create and compile shader
    GLuint shader = glCreateShader(shader_type);  // 쉐이더 핸들을 정수 형태로 반환
    glShaderSource(shader, 1, &chr, reinterpret_cast<const GLint*>(&content_length));  // 하나의 쉐이더에 여러 개의 소스 코드를 전달할 수 있음
    glCompileShader(shader);

    // Check compile error
    int32_t success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success == 0) {
        char info_log[1024];
        int32_t length = 0;
        glGetShaderInfoLog(shader, 1024, &length, info_log);
        info_log[length] = '\0';
        return std::unexpected(std::format("Failed to compile shader file \"{}\"\n{}", file_path, info_log));
    }

    return std::unique_ptr<Shader>(new Shader(shader));
}

GLuint Shader::get() const {
    return shader;
}

Shader::Shader(GLuint shader) {
    this->shader = shader;
}

Shader::~Shader() {
    if (shader) {
        glDeleteShader(shader);
        SPDLOG_INFO("Destroyed shader({})", shader);
    }
}