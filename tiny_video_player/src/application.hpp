#pragma once

#include <memory>

struct GLFWwindow;

namespace tvp
{
class main_window;

class application
{
public:
    explicit application();
    ~application();

    int run(int argc, char **argv);

private:
    bool init();
    void update();

    std::unique_ptr<main_window> _main_window;
    GLFWwindow *window;
};

std::unique_ptr<application> create_application();

} // namespace app
