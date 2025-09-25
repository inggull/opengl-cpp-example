#include <Context.hh>

std::expected<std::unique_ptr<Context>, std::string> Context::create() {
    uint32_t vao{0};

    std::expected<std::shared_ptr<Shader>, std::string> vertex_shader = Shader::create("shader/simple.vert", GL_VERTEX_SHADER);
    if (vertex_shader.has_value() == false)
        return std::unexpected(vertex_shader.error());
    std::expected<std::shared_ptr<Shader>, std::string> fragment_shader = Shader::create("shader/simple.frag", GL_FRAGMENT_SHADER);
    if (fragment_shader.has_value() == false)
        return std::unexpected(fragment_shader.error());
    SPDLOG_INFO("Created vertex shader({})", vertex_shader.value()->get());
    SPDLOG_INFO("Created fragment shader({})", fragment_shader.value()->get());

    auto program = Program::create({vertex_shader.value(), fragment_shader.value()});
    if (program.has_value() == false)
        return std::unexpected(program.error());
    SPDLOG_INFO("Created program({})", program.value()->get());

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f); // State-setting function

    glGenVertexArrays(1, &vao); // 새로운 vao를 생성
    SPDLOG_INFO("Created vertex array({})", vao);
    // 셰이더의 전역 변수에 값을 전달
    program.value()->use(); // 사용할 프로그램을 지정
    glUniform3f(glGetUniformLocation(program.value()->get(), "global_position"), 0.0f, 0.0f, 0.0f);
    glUniform4f(glGetUniformLocation(program.value()->get(), "global_color"), 1.0f, 1.0f, 1.0f, 1.0f);

    return std::unique_ptr<Context>(new Context(move(program.value()), vao));
}

void Context::render() const {
    glClear(GL_COLOR_BUFFER_BIT); // State-using function
    glBindVertexArray(vao); // 사용할 vao를 지정
    program->use();
    glDrawArrays(GL_POINTS, 0, 1);
}

Context::Context(std::unique_ptr<Program> program, uint32_t vao) : program(move(program)), vao(vao) {}

Context::~Context() {
    glDeleteVertexArrays(1, &vao);
    SPDLOG_INFO("Destroyed vertex array({})", vao);
}