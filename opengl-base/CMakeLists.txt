IF(MSVC)
    set(wxWidgets_CONFIGURATION mswu)
endif()

find_package(Boost REQUIRED)
find_package(wxWidgets COMPONENTS gl core base REQUIRED)
find_package(OpenGL REQUIRED)

include(${wxWidgets_USE_FILE})

set(SRCS
	app.hpp
    app.cpp
	canvas.hpp
	canvas.cpp
	frame.hpp
	frame.cpp
)
add_executable(opengl-base WIN32 ${SRCS})
target_link_libraries(opengl-base ${wxWidgets_LIBRARIES} ${OPENGL_gl_LIBRARY})
