
message(STATUS "This is from the C:/dev/Paint/src directory")
message(STATUS "CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "CMAKE_CURRENT_BINARY_DIR: ${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
message(STATUS "CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}")
message(STATUS "CMAKE_CURRENT_LIST_DIR: ${CMAKE_CURRENT_LIST_DIR}")


add_executable(
    Paint
    Paint.cpp
    Screen.h
    Screen.cpp
    UserInput.h
    UserInput.cpp
    Button.h
    Coordinates.h
)

target_link_directories(Paint PRIVATE "${CMAKE_SOURCE_DIR}/dependencies/SDL2/lib/x64")
target_link_libraries(Paint PRIVATE SDL2.dll SDL2.lib SDL2main.lib)

add_custom_command(TARGET Paint
                    POST_BUILD COMMAND
                    ${CMAKE_COMMAND} -E copy_if_different
                    "${CMAKE_SOURCE_DIR}/dependencies/SDL2/lib/x64/SDL2.dll"
                    $<TARGET_FILE_DIR:Paint>)