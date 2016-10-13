find_package(Boost REQUIRED)
find_package(wxWidgets COMPONENTS gl core base REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

include(${wxWidgets_USE_FILE})
IF(MSVC)
    set(wxWidgets_CONFIGURATION mswu)
endif()

set(TARGET_NAME opengl-base)
set(SRCS
	shaders/sample.vert
	shaders/sample.frag
	config.hpp
	app.hpp
    app.cpp
	canvas.hpp
	canvas.cpp
	frame.hpp
	frame.cpp
	utils.hpp
	utils.cpp
)

add_executable(${TARGET_NAME} WIN32 ${SRCS})
set_property(TARGET ${TARGET_NAME} PROPERTY DEBUG_POSTFIX "_d")
target_link_libraries(${TARGET_NAME}
	${wxWidgets_LIBRARIES}
	${OPENGL_gl_LIBRARY}
	${OPENGL_glu_LIBRARY}
	GLEW::GLEW
)

configure_file(
	config.hpp.in
	${CMAKE_CURRENT_BINARY_DIR}/config.hpp
)

copy_resource(${TARGET_NAME} shaders/sample.vert)
copy_resource(${TARGET_NAME} shaders/sample.frag)
