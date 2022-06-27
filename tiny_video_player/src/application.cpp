#include "application.hpp"
#include "main_window.hpp"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>
#include <thread>

// #include <iostream>

namespace tvp
{
std::unique_ptr<application> create_application()
{
    return std::make_unique<application>();
}

application::application()
: _main_window{ std::make_unique<main_window>() }
{
}

application::~application()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}

bool application::init()
{
    if (!glfwInit())
    {
        // log error
        return false;
    }

    const char* glsl_version = "#version 330";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(1280, 720, "Tiny Video Player", NULL, NULL);
    if (!window)
    {
        // log error
        return false;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync
    glfwSetWindowAspectRatio(window, 1280, 720);

    int screen_width, screen_height;
	glfwGetFramebufferSize(window, &screen_width, &screen_height);
	glViewport(0, 0, screen_width, screen_height);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    ImGui::StyleColorsDark();

    ImGuiStyle &style = ImGui::GetStyle();
    style.WindowBorderSize = 0.0f;
    style.WindowPadding = { 0.0f, 0.0f };

    _main_window->init();

    return true;
}

int application::run(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    if (!init())
        return 1;

    glClearColor(0.f, 0.f, 0.f, 0.f);

    const int TARGET_FPS = 30;
    double lasttime = glfwGetTime();
    while (!glfwWindowShouldClose(window))
    {
        // while (glfwGetTime() < lasttime + 1.0/TARGET_FPS)
        // {
        //     std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(1000 * 1/TARGET_FPS)));
        // }
        // lasttime += 1.0/TARGET_FPS;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // ImGui::ShowDemoWindow();
        // return;

       _main_window->update();

        {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();

            ImGui::Begin("Player Info");
            ImGui::Text("Window Size: [%d, %d]", static_cast<int>(viewport->Size.x), static_cast<int>(viewport->Size.y));
            ImGui::Text("Rendering: %.1f (FPS)", ImGui::GetIO().Framerate);
            ImGui::End();
        }

        ImGui::Render();

        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}

} // namespace app
