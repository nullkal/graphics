find_package(Boost REQUIRED)
find_package(wxWidgets COMPONENTS gl core base REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

include(${wxWidgets_USE_FILE})
IF(MSVC)
    set(wxWidgets_CONFIGURATION mswu)
endif()

set(TARGET_NAME opengl-common)
set(SRCS
    misc.cpp
    include/opengl-common/misc.hpp
    exceptions.cpp
    include/opengl-common/exceptions.hpp
    shader.cpp
    include/opengl-common/shader.hpp
	shader-holders.cpp
	shader-holders.hpp
    program.cpp
    include/opengl-common/program.hpp
)

add_library(${TARGET_NAME} ${SRCS})
set_property(TARGET ${TARGET_NAME} PROPERTY DEBUG_POSTFIX "_d")
target_link_libraries(${TARGET_NAME}
	${wxWidgets_LIBRARIES}
	${OPENGL_gl_LIBRARY}
	${OPENGL_glu_LIBRARY}
	GLEW::GLEW
)
target_include_directories(${TARGET_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
