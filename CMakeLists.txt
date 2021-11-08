cmake_minimum_required(VERSION 3.14)

# uncomment these 2 lines if using clang
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -target x86_64-w64-mingw32")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -target x86_64-w64-mingw32")

project(ColorPicker)
set(BUILD_SHARED_LIBS FALSE)
set(SFML_BUILD_AUDIO FALSE)
set(SFML_BUILD_DOC FALSE)
set(SFML_BUILD_EXAMPLES FALSE)
set(SFML_BUILD_GRAPHICS TRUE)
set(SFML_BUILD_NETWORK FALSE)
set(SFML_BUILD_TEST_SUITE FALSE)
set(SFML_BUILD_WINDOW TRUE)
set(SFML_INSTALL_PKGCONFIG_FILES FALSE)
set(SFML_OPENGL_ES FALSE)
set(SFML_USE_STATIC_STD_LIBS FALSE)
set(SFML_USE_SYSTEM_DEPS TRUE)

add_subdirectory("SFML")

# uncomment this line if using msvc
# SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /subsystem:windows /ENTRY:mainCRTStartup")

# uncomment this line if using clang
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -Wl,--subsystem,windows")

add_executable(ColorPicker main.cpp)

target_link_libraries(ColorPicker sfml-graphics)
