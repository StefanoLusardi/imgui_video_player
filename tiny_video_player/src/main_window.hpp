#pragma once

#include <memory>
#include <thread>

#include "video_capture/video_capture.hpp"
#include "video_capture/raw_frame.hpp"
#include "video_capture/frame_queue.hpp"

namespace tvp
{
class main_window
{
public:
    explicit main_window();
    ~main_window();

    bool init();
    void update();
    void decode_thread();

private:
    std::unique_ptr<vc::video_capture> _video_decoder;
    std::unique_ptr<vc::raw_frame> _current_frame;
    vc::frame_queue<std::unique_ptr<vc::raw_frame>> _frame_queue;
    std::thread _decode_thread;
    unsigned int _frame_texture_id;
};

} // namespace app