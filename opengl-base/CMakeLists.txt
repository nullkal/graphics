find_package(Boost REQUIRED)
find_package(wxWidgets COMPONENTS gl core base REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(Doxygen)

include(${wxWidgets_USE_FILE})
IF(MSVC)
    set(wxWidgets_CONFIGURATION mswu)
endif()

set(TARGET_NAME opengl-base)
set(APP_NAME "OpenGL-Base")
set(SHADERS
	shaders/sample.vert
	shaders/sample.frag
)
set(SRCS
	config.hpp
	app.hpp
    app.cpp
	canvas.hpp
	canvas.cpp
	frame.hpp
	frame.cpp
	${SHADERS}
)

add_executable(${TARGET_NAME} WIN32 ${SRCS})
source_group("Shader Files" FILES ${SHADERS})
set_property(TARGET ${TARGET_NAME} PROPERTY DEBUG_POSTFIX "_d")
target_link_libraries(${TARGET_NAME}
	opengl-common
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

if(DOXYGEN_FOUND)
	configure_file(
		doxygen.conf.in
		${CMAKE_CURRENT_BINARY_DIR}/doxygen.conf
	)
	add_custom_target(${TARGET_NAME}_doc
		${DOXYGEN_EXECUTABLE} doxygen.conf
		DEPENDS doxygen.conf
	)
	set_target_properties(${TARGET_NAME}_doc PROPERTIES FOLDER Documentations)
	add_dependencies(docs ${TARGET_NAME}_doc)
endif()