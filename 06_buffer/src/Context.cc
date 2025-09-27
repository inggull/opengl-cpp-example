#include <Context.hh>

std::expected<std::unique_ptr<Context>, std::string> Context::create() {
    std::expected<std::shared_ptr<Shader>, std::string> vertex_shader = Shader::create("shader/triangle.vert", GL_VERTEX_SHADER);
    if (vertex_shader.has_value() == false)
        return std::unexpected(vertex_shader.error());
    std::expected<std::shared_ptr<Shader>, std::string> fragment_shader = Shader::create("shader/triangle.frag", GL_FRAGMENT_SHADER);
    if (fragment_shader.has_value() == false)
        return std::unexpected(fragment_shader.error());
    SPDLOG_INFO("Created vertex shader({})", vertex_shader.value()->get());
    SPDLOG_INFO("Created fragment shader({})", fragment_shader.value()->get());

    auto program = Program::create({vertex_shader.value(), fragment_shader.value()});
    if (program.has_value() == false)
        return std::unexpected(program.error());
    SPDLOG_INFO("Created program({})", program.value()->get());

    float vertices[18] = {
        0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
    };
    GLuint indices[3] = {
        0, 1, 2,
    };

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f); // State-setting function

    // 사용할 vao를 먼저 바인딩 해줘야 나머지 오르젝트들이 vao에 저장된다
    auto vao = VertexArray::create(); // 새로운 vao를 생성
    vao->bind(); // 사용할 vao를 지정
    auto vbo = Buffer::create(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // 새로운 vbo를 생성
    auto ebo = Buffer::create(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); // 새로운 ebo를 생성

    // 초기에 `VertexAttribPointer`의 포인터는 각 버택스 버퍼에 바인딩된 배열의 시작 주소를 가리켰지만, vao가 등장하면서 vao가 가리키는 배열의 오프셋을 의미하게 되었다
    // 속성 0번: position
    vao->set(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, reinterpret_cast<const void *>(sizeof(float) * 0)); // vao의 0번 속성을 활성화하고, 해당하는 vbo 데이터를 전달
    // 속성 1번: color
    vao->set(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, reinterpret_cast<const void *>(sizeof(float) * 3)); // vao의 1번 속성을 활성화하고, 해당하는 vbo 데이터를 전달

    return std::unique_ptr<Context>(new Context(move(program.value()), move(vao), move(vbo), move(ebo)));
}

void Context::render() const {
    glClear(GL_COLOR_BUFFER_BIT); // State-using function
    program->use(); // 사용할 프로그램을 지정
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
}

Context::Context(std::unique_ptr<Program> program, std::unique_ptr<VertexArray> vao, std::unique_ptr<Buffer> vbo, std::unique_ptr<Buffer> ebo) : program(move(program)), vao(move(vao)), vbo(move(vbo)), ebo(move(ebo)) {}