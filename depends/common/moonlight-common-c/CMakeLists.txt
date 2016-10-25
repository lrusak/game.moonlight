cmake_minimum_required(VERSION 3.1)
project(moonlight)

find_package(OpenSSL REQUIRED)

set(MOONLIGHT_SOURCES
    src/AudioStream.c
    src/ByteBuffer.c
    src/Connection.c
    src/ControlStream.c
    src/FakeCallbacks.c
    src/InputStream.c
    src/LinkedBlockingQueue.c
    src/Misc.c
    src/Platform.c
    src/PlatformSockets.c
    src/RtpReorderQueue.c
    src/RtspConnection.c
    src/RtspParser.c
    src/SdpGenerator.c
    src/VideoDepacketizer.c
    src/VideoStream.c
)

include_directories(
    ${OPENSSL_INCLUDE_DIR}
    enet/include
)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
add_library(${PROJECT_NAME} STATIC ${MOONLIGHT_SOURCES} ${ENET_SOURCES})

add_subdirectory(enet)
target_link_libraries(${PROJECT_NAME} PRIVATE enet)

# Install the generated static library
install(TARGETS ${PROJECT_NAME}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
install(FILES "$<TARGET_FILE:enet>" DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

# Install the header
install(FILES src/Limelight.h
        DESTINATION ${CMAKE_INSTALL_PREFIX}/include)

# Write the moonlight-config.cmake script
file(WRITE ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}-config.cmake
    "set(MOONLIGHT_LIBRARIES ${CMAKE_INSTALL_PREFIX}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}${PROJECT_NAME}${CMAKE_STATIC_LIBRARY_SUFFIX}\n \
                             ${CMAKE_INSTALL_PREFIX}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}enet${CMAKE_STATIC_LIBRARY_SUFFIX})\n \
     set(MOONLIGHT_INCLUDE_DIRS ${CMAKE_INSTALL_PREFIX}/include)")
