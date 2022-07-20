#include "main_window.hpp"
#include "video_capture/raw_frame.hpp"
#include <imgui.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <thread>


namespace tvp
{
main_window::main_window()
    : _video_decoder { std::make_unique<vc::video_capture>() }
    , _current_frame { std::make_unique<vc::raw_frame>() }
    , _frame_queue { vc::frame_queue<std::unique_ptr<vc::raw_frame>>(16) }
{
}

main_window::~main_window()
{
}

bool main_window::init()
{
    vc::video_capture vc;
    const auto video_path = "v.mkv";

	if (!_video_decoder->open(video_path, vc::decode_support::SW))
    {
        // log error
        return false;
    }

	glGenTextures(1, &_frame_texture_id);
	glBindTexture(GL_TEXTURE_2D, _frame_texture_id);
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    _decode_thread = std::thread([this]{ decode_thread(); });

    return true;
}

void main_window::decode_thread()
{
    int frames_decoded = 0;
	while(true)
	{
		auto next_frame = std::make_unique<vc::raw_frame>();
		if(!_video_decoder->read(next_frame.get()))
		{
			std::cout << "Video finished" << std::endl;
			std::cout << "frames decoded: " << frames_decoded << std::endl;
			break;
		}

		_frame_queue.put(std::move(next_frame));
		++frames_decoded;
	}
}

void main_window::update()
{
    if (glfwGetTime() > _current_frame->pts)
    {
        if(_frame_queue.try_get(&_current_frame))
        {
            const auto size = _video_decoder->get_frame_size();
            const auto [frame_width, frame_height] = size.value();
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, frame_width, frame_height, 0, GL_RGB, GL_UNSIGNED_BYTE, (const GLvoid*)_current_frame->data_buffer);
        }
    }

    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);

    static ImGuiWindowFlags main_window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBringToFrontOnFocus;

    ImGui::Begin("MainWindow", nullptr, main_window_flags);
    ImGui::Image((void*)static_cast<uintptr_t>(_frame_texture_id), viewport->Size);
    ImGui::End();
}

} // namespace app
