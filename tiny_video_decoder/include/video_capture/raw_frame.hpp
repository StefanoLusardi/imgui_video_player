#pragma once

#include "api.hpp"

#include <vector>
#include <cstdint>

namespace vc
{
struct API_VIDEO_CAPTURE raw_frame
{
    explicit raw_frame() = default;
    ~raw_frame() = default;
    
    uint8_t* data_buffer;
    size_t data_size;
	double pts = 0.0;
};

// struct raw_frame
// {
//     explicit raw_frame() = default;
//     ~raw_frame() = default;
    
//     std::vector<uint8_t> data;
// 	double pts = 0.0;
// };

}