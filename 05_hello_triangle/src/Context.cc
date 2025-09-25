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
        0.0, 0.5, 0.0, 1.0, 0.0, 0.0,
        -0.5, -0.5, 0.0, 0.0, 1.0, 0.0,
        0.5, -0.5, 0.0, 0.0, 0.0, 1.0,
    };
    uint32_t indices[3] = {
        0, 1, 2,
    };

    uint32_t vao{0};
    uint32_t vbo{0};
    uint32_t ebo{0};

    // 사용할 vao를 먼저 바인딩 해줘야 나머지 오르젝트들이 vao에 저장된다
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f); // State-setting function

    glGenVertexArrays(1, &vao); // 새로운 vao를 생성
    SPDLOG_INFO("Created vertex array({})", vao);
    glBindVertexArray(vao); // 사용할 vao를 지정

    glGenBuffers(1, &vbo); // 새로운 vbo를 생성
    SPDLOG_INFO("Created vertex buffer({})", vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo); // 사용할 vbo를 지정
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // vbo에 데이터를 전달

    // 초기에 `VertexAttribPointer`의 포인터는 각 버택스 버퍼에 바인딩된 배열의 시작 주소를 가리켰지만, vao가 등장하면서 vao가 가리키는 배열의 오프셋을 의미하게 되었다
    // 속성 0번: position
    glEnableVertexAttribArray(0);  // vao의 0번 속성을 활성화
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, reinterpret_cast<const void*>(sizeof(float) * 0)); // vao의 속성 0번에 해당하는 vbo 데이터를 전달
    // 속성 1번: color
    glEnableVertexAttribArray(1);  // vao의 1번 속성을 활성화
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, reinterpret_cast<const void *>(sizeof(float) * 3)); // vao의 속성 1번에 해당하는 vbo 데이터를 전달

    glGenBuffers(1, &ebo);  // 새로운 ebo를 생성
    SPDLOG_INFO("Created element buffer({})", ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);  // 사용할 ebo를 지정
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); // ebo에 데이터를 전달

    return std::unique_ptr<Context>(new Context(move(program.value()), vao, vbo, ebo));
}

void Context::render() const {
    glClear(GL_COLOR_BUFFER_BIT); // State-using function
    program->use();
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
}

Context::Context(std::unique_ptr<Program> program, uint32_t vao, uint32_t vbo, uint32_t ebo) : program(move(program)), vao(vao), vbo(vbo), ebo(ebo) {}

Context::~Context() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    SPDLOG_INFO("Destroyed vertex array({})", vao);
    SPDLOG_INFO("Destroyed vertex buffer({})", vbo);
    SPDLOG_INFO("Destroyed element buffer({})", ebo);
}