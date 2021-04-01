cmake_minimum_required(VERSION 3.16)

project(ecsP2_8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

find_package(SFML 2.5 COMPONENTS audio graphics window system REQUIRED)

set(APP_SOURCES 
    src/Bitmask.cpp
    src/C_KeyboardMovement.cpp
    src/C_Sprite.cpp
    src/C_Transform.cpp
    src/Game.cpp
    src/Input.cpp
    src/Main.cpp
    src/Object.cpp
    src/SceneGame.cpp
    src/SceneSplashScreen.cpp
    src/SceneStateMachine.cpp
    src/Window.cpp
    src/WorkingDirectory.cpp
)

file(COPY resources DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
add_executable(${PROJECT_NAME} ${APP_SOURCES})
target_link_libraries(${PROJECT_NAME} sfml-audio sfml-graphics sfml-window sfml-system)
