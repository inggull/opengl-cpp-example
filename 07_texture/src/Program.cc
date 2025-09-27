#include <Program.hh>

std::expected<std::unique_ptr<Program>, std::string> Program::create(const std::vector<std::shared_ptr<Shader>> &shaders) {
    GLuint program = glCreateProgram();
    for (auto shader: shaders)
        glAttachShader(program, shader->get());
    glLinkProgram(program);

    // Check link error
    GLint success{0};
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (success == 0) {
        char info_log[1024];
        GLint length{0};
        glGetProgramInfoLog(program, 1024, &length, info_log);
        info_log[length] = '\0';
        return std::unexpected(std::format("Failed to link program\n{}", info_log));
    }

    return std::unique_ptr<Program>(new Program(program));
}

GLuint Program::get() const {
    return program;
}

void Program::use() const {
    glUseProgram(program);
}

Program::Program(GLuint program) : program(program) {}

Program::~Program() {
    glDeleteProgram(program);
    SPDLOG_INFO("Destroyed program({})", program);
}