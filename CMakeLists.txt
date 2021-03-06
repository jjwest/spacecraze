cmake_minimum_required(VERSION 3.5)
project(spacecraze)
set (TARGET spacecraze)
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${spacecraze_SOURCE_DIR}/cmake")
set (CMAKE_CXX_FLAGS "-std=c++14 -O2 -Wall -Wextra -Wold-style-cast -Woverloaded-virtual -pedantic -g")

file(GLOB SOURCES "src/*.cc")
add_executable(${TARGET} ${SOURCES})

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

target_include_directories(
  ${TARGET} PUBLIC
  ${SDL2_INCLUDE_DIR}
  ${SDL2_IMAGE_INCLUDE_DIR}
  ${SDL2_TTF_INCLUDE_DIR}
  ${SDL2_MIXER_INCLUDE_DIR}
)

target_link_libraries(${TARGET} ${SDL2_LIBRARY}
                                ${SDL2_IMAGE_LIBRARIES}
                                ${SDL2_TTF_LIBRARIES}
                                ${SDL2_MIXER_LIBRARIES})
