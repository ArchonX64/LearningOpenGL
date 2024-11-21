
#include "Window.h"

void Window::processInput() {
    camera->camMoveKeyCallback(window, getDeltaTime());
}

void Window::keyCallback(int key, int scancode, int action, int mods) {
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(this->window, true);
    }
    if(key == GLFW_KEY_P && action == GLFW_PRESS) {
        paused = !paused;
    }
    if(key == GLFW_KEY_F && action == GLFW_PRESS) {
        if(isFullscreen) {
            isFullscreen = false;
            width = windowed_width;
            height = windowed_height;
            glfwSetWindowMonitor(window, nullptr, windowed_x, windowed_y,
                                 width, height, 0);
        } else {
            isFullscreen = true;
            const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
            if(!mode) {
                util::log(util::LogLevel::ERROR, "Failed to get video mode!");
                glfwTerminate();
                exit(-1);
            }
            width = mode->width;
            height = mode->height;
            glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0,
                                 width, height, refreshRate);
        }
    }
}

void Window::init() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

void Window::cursorMoveCallback(double xpos, double ypos) {
    camera->cursorMoveCallback(xpos, ypos, getDeltaTime());
}


Window::Window(std::string name, int width, int height, int refreshRate)
    : name(std::move(name)), windowed_width(width), windowed_height(height),
    isFullscreen(true), refreshRate(refreshRate), paused(false) {

    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    if(!mode) {
        util::log(util::LogLevel::ERROR, "Failed to get video mode!");
        glfwTerminate();
        exit(-1);
    }
    this->width = mode->width;
    this->height = mode->height;
    this->windowed_x = mode->width / 2;
    this->windowed_y = mode-> height / 2;
    this->window = glfwCreateWindow(this->width, this->height, this->name.c_str(), glfwGetPrimaryMonitor(),
                                    nullptr);
    if(window == nullptr) {
        util::log(util::LogLevel::ERROR, "Failed to create GLFW window!");
        glfwTerminate();
        exit(-1);
    }

    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        util::log(util::LogLevel::ERROR, "Failed to load GLAD!");
        glfwTerminate();
        exit(-1);
    }
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glEnable(GL_CULL_FACE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 0.0f),
                                      glm::vec3(0.0f, 0.0f, -1.0f),
                                      1.0f, 50.0f, 5.0f);

    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
        auto* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
        if(!win->isFullscreen) {
            win->windowed_width = width;
            win->windowed_height = height;
        }
    });
    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
        auto* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
        win->cursorMoveCallback(xpos, ypos);
    });
    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        auto* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
        win->keyCallback(key, scancode, action, mods);
    });
    glfwSetWindowPosCallback(window, [](GLFWwindow* window, int xpos, int ypos) {
        auto* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
        if(!win->isFullscreen) {
            win->windowed_x = xpos;
            win->windowed_y = ypos;
        }
    });

    fontRenderer = std::make_unique<FontRenderer>();
    fontRenderer->addFont("../res/fonts/arial.ttf", "arial");
    fontRenderer->unloadLib();

    blockRenderer = std::make_unique<BlockRenderer>();

    boxRenderer = std::make_unique<BoxRenderer>(weak_this);

}

Window::~Window() {
    glfwTerminate();
}

void Window::windowMainLoop(const std::shared_ptr<Texture>& texture,
                            const std::vector<glm::vec3>& locs) {
    lastFrameTime = 0.0f;
    deltaTime = 0.0f;
    lastFps = 0.0f;

    while(!glfwWindowShouldClose(window)) {
        processInput();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if(!paused) {
            auto view = glm::mat4(1.0f);
            auto proj = glm::mat4(1.0f);

            view = camera->calculateViewMat();
            proj = glm::perspective(glm::radians(45.0f), (float) width / (float) height, 0.1f, 100.0f);

            blockRenderer->renderAll(texture, locs, view, proj);

            metricShow();
        }

        glfwSwapBuffers(window);
        glfwPollEvents();

        // Calculate deltatime
        double timeHold = glfwGetTime();
        deltaTime = timeHold - lastFrameTime;
        lastFrameTime = timeHold;
    }
}

void Window::metricShow() {
    if(glfwGetTime() - lastFps > 1) {
        fps = static_cast<int>(1 / deltaTime);
        lastFps = glfwGetTime();
#ifdef _WIN32
        PROCESS_MEMORY_COUNTERS_EX pmc;
        GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
        memUse = pmc.PrivateUsage;
#endif
    }

    std::stringstream metricStream;
    metricStream << fps << " FPS";
#ifdef _WIN32
    metricStream << "     " << std::setprecision(3) << memUse / 10e6 << " MB";
#endif
    glm::vec2 pos(5.0f, height - 50);
    fontRenderer->renderFlatString("arial", metricStream.str(), pos, 1.0f,
                                   glm::vec3(0.5, 0.8f, 0.2f),
                                   glm::ivec2(width, height));
}

double Window::getDeltaTime() const {
    return deltaTime;
}

int Window::getWidth() const {
    return width;
}

int Window::getHeight() const {
    return height;
}