set(TARGET_NAME tiny_video_player)

add_executable(${TARGET_NAME}
	src/application.cpp
	src/application.hpp
	src/main_window.cpp
	src/main_window.hpp
	src/main.cpp
	
	${CMAKE_BINARY_DIR}/bindings/imgui_impl_glfw.cpp
	${CMAKE_BINARY_DIR}/bindings/imgui_impl_glfw.h
	${CMAKE_BINARY_DIR}/bindings/imgui_impl_opengl3.cpp
	${CMAKE_BINARY_DIR}/bindings/imgui_impl_opengl3.h
)

find_package(imgui)
find_package(glfw3)

target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_BINARY_DIR}/bindings)

target_link_libraries(${TARGET_NAME}
	PRIVATE tiny_video_decoder
	PRIVATE imgui::imgui
	PRIVATE glfw
)