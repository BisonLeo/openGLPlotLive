# Set minimum cmake
cmake_minimum_required(VERSION 3.10)

# get packages using vcpkg
message("see https://github.com/microsoft/vcpkg/blob/master/README.md
and https://cmake.org/cmake/help/latest/envvar/CMAKE_TOOLCHAIN_FILE.html")
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_TOOLCHAIN_FILE} "C:/dev/vcpkg/scripts/buildsystems/vcpkg.cmake")
message("Build CMakeLists with CMAKE_TOOLCHAIN_FILE = ${CMAKE_TOOLCHAIN_FILE}")

# Setup project
project(openGLPlotLive-proj)

# Resolves issue with unable to debug with CLion, reverts back to g++9
if(NOT MSVC)
add_compile_options(-gdwarf-4)
endif()

# Set OpenGL Policy
set(OpenGL_GL_PREFERENCE "GLVND")

# Add c++14 flag to compiler
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}") #  -Wall

# Add Cmake Module Path
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/")

# Windows specific setup
if(WIN32)
    message(${CMAKE_SOURCE_DIR}/include/)
    include_directories("${CMAKE_SOURCE_DIR}/include")
    set(GLM_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include/glm/glm.h")
    set(GLFW3_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include/GLFW/glfw3.h")
    set(GLFW3_LIBRARY "${CMAKE_SOURCE_DIR}/Lib/glfw3.lib")
    set(FREETYPE_LIBRARY "${CMAKE_SOURCE_DIR}/Lib/freetype.lib")
endif(WIN32)

# Find Packages
# GLM
find_package(GLM REQUIRED)
message(STATUS "GLM found: ${GLM_INCLUDE_DIR}")
# FREETYPE
find_package(FREETYPE REQUIRED)
MESSAGE(STATUS "Found FREETYPE: ${FREETYPE_LIBRARY}")
# GLFW3
find_package(GLFW3 REQUIRED)
message(STATUS "Found GlFW3: ${GLFW3_LIBRARY}")
# OpenGL
find_package(OpenGL REQUIRED)
add_definitions(${OPENGL_DEFINITIONS})
# X11
find_package(X11 REQUIRED)


# Set libraries
if(WIN32)
    if(MSVC)
    find_package(ZLIB REQUIRED)
    set(LIBS ${FREETYPE_LIBRARY} ${GLFW3_LIBRARY} ZLIB::ZLIB opengl32 )
    else()
    set(LIBS ${FREETYPE_LIBRARY} ${GLFW3_LIBRARY} z opengl32 )
    endif()
elseif(UNIX)
    set(LIBS ${GLFW3_LIBRARY} X11 Xrandr Xinerama Xi Xxf86vm Xcursor dl pthread freetype GL)
endif(WIN32)

# Stop conflicting order of GLAD and GLFW
add_definitions(-DGLFW_INCLUDE_NONE)

# Add subdirectories
add_subdirectory(src)
add_subdirectory(apps)
add_subdirectory(docs)
add_subdirectory(tests)
add_subdirectory(third_party/google-test)
