
set(Headers 
    Screen.hpp)
set(Sources
    Paint.cpp
    Screen.cpp)

add_executable(
    Paint
    ${Headers}
    ${Sources}
)

target_link_directories(Paint PRIVATE "${CMAKE_SOURCE_DIR}/dependencies/SDL2/lib/x64") #set directory for linking libraries
target_link_libraries(Paint PRIVATE SDL2.dll SDL2.lib SDL2main.lib) #linke libraries to Paint (using directory specified above)
target_include_directories(Paint PRIVATE "${CMAKE_SOURCE_DIR}/dependencies/SDL2/include") #set include header file path for Paint

file(COPY "${CMAKE_SOURCE_DIR}/dependencies/SDL2/lib/x64/SDL2.dll" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/Debug") #copy SDL2.dll into Paint.exe directory

#add_custom_command(TARGET Paint
#                    POST_BUILD COMMAND
#                    ${CMAKE_COMMAND} -E copy_if_different
#                    SDL2.dll
#                    $<TARGET_FILE_DIR:Paint>)
