cmake_minimum_required(VERSION 3.8)
project(warhammer-battlefleet VERSION 0.1)

set(__BUILD_DIR ${CMAKE_SOURCE_DIR}/build)
set(__SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(__LIB_DIR ${CMAKE_SOURCE_DIR}/src/libs)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${__BUILD_DIR})
set(CMAKE_COLOR_DIAGNOSTICS ON)

# set(CMAKE_SYSTEM_NAME Windows)
# set(CMAKE_SYSTEM_PROCESSOR x86_64)

# SET(CMAKE_C_COMPILER i686-w64-mingw32-gcc)
# SET(CMAKE_CXX_COMPILER i686-w64-mingw32-g++)


include(FetchContent)

# |--------------------------------------------------|
# |                 +++LIBRARIES+++                  |
# |--------------------------------------------------|

# find_package(SDL2 REQUIRED)
# include_directories(${SDL2_INCLUDE_DIRS})
# find_package(SDL2_image REQUIRED)
# include_directories(${SDL2_IMAGE_INCLUDE_DIRS})

# find_package(SFML REQUIRED)
# include_directories(${SFML_INCLUDE_DIRS})

# /SFML\
message(STATUS "Downloading SFML")
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)
message(STATUS "Downloaded SFML")
# \SFML/


# |--------------------------------------------------|
# |                   +++CLIENT+++                   |
# |--------------------------------------------------|


set(__CLIENT_DIR ${CMAKE_SOURCE_DIR}/src/client) 

set(__CLIENT_SRCS 
    ${__CLIENT_DIR}/test.cpp
)

set(__CLIENT_LIBS
    sfml-graphics
    # ${SFML_LIBRARIES}
    # ${SDL2_LIBRARIES}
    # ${SDL2_IMAGE_LIBRARIES}
)

add_executable(client ${__CLIENT_SRCS})
target_link_libraries (client ${__CLIENT_LIBS})
install(TARGETS client)


# |--------------------------------------------------|
# |                   +++SERVER+++                   |
# |--------------------------------------------------|


# set(__SERVER_DIR ${CMAKE_SOURCE_DIR}/src/server) 

# set(__SERVER_SRCS 
#     # ${__SERVER_DIR}/armament.h
# )

# add_executable(server ${__SERVER_SRCS})
