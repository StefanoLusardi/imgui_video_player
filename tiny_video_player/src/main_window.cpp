#include "main_window.hpp"
#include <imgui.h>


namespace tvp
{
main_window::~main_window()
{
}

void main_window::update_ui()
{
    // ImGui::ShowDemoWindow();
    // return;

    {
        static ImGuiWindowFlags main_window_flags =
            ImGuiWindowFlags_NoBringToFrontOnFocus |
            ImGuiWindowFlags_NoDecoration |
            ImGuiWindowFlags_AlwaysAutoResize |
            ImGuiWindowFlags_NoSavedSettings |
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoNav;

        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);

        if (ImGui::Begin("MainWindow", NULL, main_window_flags))
        {
            // ImDrawList* draw_list = ImGui::GetWindowDrawList();
            // const float size = 50;
            // static ImVec4 rgba_color = ImVec4(1.0f, 1.0f, 0.4f, 1.0f);
            // const ImU32 color = ImColor(rgba_color);
            // auto window_center_w = ImGui::GetWindowWidth() * 0.5f;
            // auto window_center_h = ImGui::GetWindowHeight() * 0.5f;
            // draw_list->AddCircle(ImVec2(window_center_w, window_center_h), size, color);

            // draw_list->AddCircle(ImVec2(size, size), size, color);
            // draw_list->AddCircle(ImVec2(ImGui::GetWindowWidth() - size, ImGui::GetWindowHeight() - size), size, color);
        }

        ImGui::End();
    }

    {
        static ImGuiWindowFlags ui_info_flags =
            ImGuiWindowFlags_NoDecoration |
            ImGuiWindowFlags_AlwaysAutoResize |
            ImGuiWindowFlags_NoSavedSettings |
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoNav |
            ImGuiWindowFlags_NoFocusOnAppearing;

        const float PAD = 10.0f;
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        const auto window_pos = ImVec2{ viewport->WorkSize.x - PAD, viewport->WorkSize.y - PAD };
        const auto window_pos_pivot = ImVec2{ 1.0f, 1.0f };
        ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
        ImGui::SetNextWindowBgAlpha(0.2f);

        ImGui::Begin("UI Info", nullptr, ui_info_flags);
        ImGui::Text("%.3f ms/frame", 1000.0f / ImGui::GetIO().Framerate);
        ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);
        ImGui::End();
    }
}

} // namespace app
