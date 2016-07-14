project(enet)
cmake_minimum_required(VERSION 2.8)

set(ENET_SOURCES
    callbacks.c
    compress.c
    host.c
    list.c
    packet.c
    peer.c
    protocol.c
    unix.c
    win32.c
)

include_directories(include)

add_library(${PROJECT_NAME} STATIC ${ENET_SOURCES})

# Install the generated static library
install(TARGETS ${PROJECT_NAME}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

# Install the header
install(DIRECTORY include/enet
        DESTINATION ${CMAKE_INSTALL_PREFIX}/include)

# Write the enet-config.cmake script
file(WRITE ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}-config.cmake
     "set(ENET_LIB ${CMAKE_INSTALL_PREFIX}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}${PROJECT_NAME}${CMAKE_STATIC_LIBRARY_SUFFIX})")
