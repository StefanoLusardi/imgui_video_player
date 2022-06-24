set(TARGET_NAME tiny_video_decoder)

add_library(${TARGET_NAME} STATIC
    include/video_capture/api.hpp
    include/video_capture/raw_frame.hpp
    include/video_capture/frame_queue.hpp
    include/video_capture/video_capture.hpp
    
    src/video_capture.cpp
    src/hw_acceleration.hpp
    src/logger.hpp
)

find_package(ffmpeg)

target_compile_definitions(${TARGET_NAME} PRIVATE LIB_VIDEO_CAPTURE)

target_include_directories(${TARGET_NAME} PUBLIC include)

target_link_libraries(${TARGET_NAME}
	PRIVATE ffmpeg::ffmpeg
)
