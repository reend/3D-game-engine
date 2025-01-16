cmake_minimum_required(VERSION 3.14)
project(raylib-game-engine)

# Включаем C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавляем raylib
include(FetchContent)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 4.5.0
)
FetchContent_MakeAvailable(raylib)

# Добавляем raylib-cpp
FetchContent_Declare(
    raylib_cpp
    GIT_REPOSITORY https://github.com/RobLoach/raylib-cpp.git
    GIT_TAG v4.5.0
)
FetchContent_MakeAvailable(raylib_cpp)

# Создаем исполняемый файл
add_executable(${PROJECT_NAME} 
    src/main.cpp
    src/core/GameEngine.cpp
    src/rendering/Renderer.cpp
    src/models/ModelLoader.cpp
    src/camera/CameraController.cpp
)

# Подключаем библиотеки и включаем пути
target_include_directories(${PROJECT_NAME} PRIVATE
    ${raylib_SOURCE_DIR}/src
    ${raylib_cpp_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    raylib
    raylib_cpp
)