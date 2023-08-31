cmake_minimum_required(VERSION 3.8)
project(warhammer-battlefleet VERSION 0.1)

set(__SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(__DATA_DIR ${CMAKE_SOURCE_DIR}/data)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# set(CMAKE_COLOR_DIAGNOSTICS ON)



# |--------------------------------------------------|
# |                 +++LIBRARIES+++                  |
# |--------------------------------------------------|



find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
set(__CLIENT_LIBS
    SDL2::SDL2
    SDL2_image::SDL2_image
)



# |--------------------------------------------------|
# |                    +++SRCS+++                    |
# |--------------------------------------------------|



# set(__OBJECT_SRCS
#     ${__SRC_DIR}/object/armament.h
#     ${__SRC_DIR}/object/vessel.h
#     ${__SRC_DIR}/object/vesseltype.h
# )
# set(__SETTINGS_SRCS
#     ${__SRC_DIR}/settings/settings.h
# )
set(__SRCS
    ${__SRC_DIR}/window.cpp
    ${__SRC_DIR}/renderer.cpp
    ${__SRC_DIR}/init.cpp
    ${__SRC_DIR}/loop.cpp
    ${__SRC_DIR}/debug.cpp
)


set(__CLIENT_SRCS
    ${__SRC_DIR}/client/main.cpp

    ${__SRCS}
)



# |--------------------------------------------------|
# |                   +++BUILDS+++                   |
# |--------------------------------------------------|


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${__BUILD_DIR})

# add_definitions(-D CLIENT=${COMMIT_VERSION})
add_executable(client ${__CLIENT_SRCS})
target_link_libraries (client ${__CLIENT_LIBS})
install(TARGETS client)

add_executable(server ${__CLIENT_SRCS})
target_link_libraries (server ${__CLIENT_LIBS})
install(TARGETS server)



# |--------------------------------------------------|
# |                    +++DATA+++                    |
# |--------------------------------------------------|



file(COPY ${__DATA_DIR} DESTINATION ${__BUILD_DIR})