#include "application.hpp"
#include "main_window.hpp"

#include "video_capture/video_capture.hpp"
#include "video_capture/raw_frame.hpp"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>

#include <iostream>

namespace tvp
{
std::unique_ptr<application> create_application()
{
    return std::make_unique<application>();
}

application::application() 
: _main_window{ std::make_unique<main_window>() }
, _video_decoder { std::make_unique<vc::video_capture>() }
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
    vc::video_capture vc;
	const auto video_path = "v.mkv";

	if (!_video_decoder->open(video_path, vc::decode_support::SW))
    {
        // log error
        return false;
    }

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

    return true;
}

int application::run(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    if (!init())
        return 1;

    // 
    GLuint tex_handle;
	glGenTextures(1, &tex_handle);
	glBindTexture(GL_TEXTURE_2D, tex_handle);
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	std::unique_ptr<vc::raw_frame2> frame;
    frame = std::make_unique<vc::raw_frame2>();

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // update();

        {
            const auto size = _video_decoder->get_frame_size();
            const auto [frame_width, frame_height] = size.value();

            if (!_video_decoder->read(frame.get()))
            {
                std::cout << "Couldn't load video frame" << std::endl;
                std::cout << "Video finished" << std::endl;
                return false;
            }
            
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, frame_width, frame_height, 0, GL_RGB, GL_UNSIGNED_BYTE, (const GLvoid*)frame->data_buffer);

            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            
            {
                static ImGuiWindowFlags main_window_flags = 
                    ImGuiWindowFlags_AlwaysAutoResize | 
                    ImGuiWindowFlags_NoDecoration | 
                    ImGuiWindowFlags_NoMove | 
                    ImGuiWindowFlags_NoSavedSettings | 
                    ImGuiWindowFlags_NoTitleBar | 
                    ImGuiWindowFlags_NoCollapse;
                
                ImGui::SetNextWindowPos(viewport->Pos);
                ImGui::SetNextWindowSize(viewport->Size);

                ImGui::Begin("MainWindow", NULL, main_window_flags);
                ImGui::Image((void*)static_cast<uintptr_t>(tex_handle), viewport->Size);
                ImGui::End();
            }

            {
                ImGui::Begin("Player Info");
                ImGui::Text("Window Size: [%d, %d]", static_cast<int>(viewport->Size.x), static_cast<int>(viewport->Size.y));
                ImGui::Text("Rendering: %.1f (FPS)", ImGui::GetIO().Framerate);
                ImGui::End();
            }
        }

        ImGui::Render();
        
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.f, 0.f, 0.f, 0.f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    return 0;
}

void application::update()
{
/*
    const auto size = _video_decoder->get_frame_size();
	const auto [frame_width, frame_height] = size.value();

    auto frame = std::make_unique<vc::raw_frame>();
    if (!_video_decoder->read(frame.get()))
    {
        std::cout << "Couldn't load video frame" << std::endl;
        std::cout << "Video finished" << std::endl;
        return;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, frame_width, frame_height, 0, GL_RGB, GL_UNSIGNED_BYTE, frame->data.data());

    GLuint my_image_texture = 0;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, (GLuint)0); // tex_handle
    glBegin(GL_QUADS);

    glTexCoord2d(0, 0);
    glVertex2i(0, 0);

    glTexCoord2d(1, 0);
    glVertex2i(frame_width, 0);

    glTexCoord2d(1, 1);
    glVertex2i(frame_width, frame_height);

    glTexCoord2d(0, 1);
    glVertex2i(0, frame_height);

    glEnd();
    glDisable(GL_TEXTURE_2D);

    ImGui::Begin("OpenGL Texture Text");
    ImGui::Text("pointer = %p", my_image_texture);
    ImGui::Text("size = %d x %d", frame_width, frame_height);
    ImGui::Image((void*)(intptr_t)my_image_texture, ImVec2(frame_width, frame_height));
    ImGui::End();
*/
}

} // namespace app
