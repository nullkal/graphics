find_package(Boost REQUIRED)
find_package(wxWidgets COMPONENTS gl core base REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(Doxygen)

include(${wxWidgets_USE_FILE})
IF(MSVC)
    set(wxWidgets_CONFIGURATION mswu)
endif()

set(TARGET_NAME opengl-common)
set(PUBLIC_HEADERS
    include/opengl-common/misc.hpp
    include/opengl-common/exceptions.hpp
    include/opengl-common/shader.hpp
    include/opengl-common/program.hpp
)
set(SRCS
    misc.cpp
    exceptions.cpp
    shader.cpp
	shader-holders.cpp
	shader-holders.hpp
    program.cpp
	program-holders.cpp
	program-holders.hpp
	${PUBLIC_HEADERS}
)

add_library(${TARGET_NAME} ${SRCS})
source_group("Public Header Files" FILES ${PUBLIC_HEADERS})
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