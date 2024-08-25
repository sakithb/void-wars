cmake_minimum_required(VERSION 3.11)

project(void_wars)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 23)

if (${PLATFORM} MATCHES "Web")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s USE_GLFW=3 -s WASM=1 -s ALLOW_MEMORY_GROWTH=1")
  set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif()

# Dependencies
set(RAYLIB_VERSION 5.0)
find_package(raylib ${RAYLIB_VERSION} QUIET)
if (NOT raylib_FOUND)
  include(FetchContent)
  FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED)
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
  endif()
endif()

set(raylib_USE_STATIC_LIBS ON)

file(GLOB_RECURSE sources
	"${CMAKE_SOURCE_DIR}/src/*.c"
)

add_executable(${PROJECT_NAME} ${sources})
target_link_libraries(${PROJECT_NAME} raylib)

if (${PLATFORM} MATCHES "Web")
  set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "--preload-file ../assets --shell-file ../shell.html")
endif ()

