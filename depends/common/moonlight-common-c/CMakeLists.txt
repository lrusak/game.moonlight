project(moonlight)
cmake_minimum_required(VERSION 2.8)

find_package(OpenSSL REQUIRED)
find_package(enet REQUIRED)

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
    ${OPENSSL_INCLUDE_DIRS}
    enet/include
)

set(CMAKE_POSITION_INDEPENDENT_CODE ON) 
add_library(${PROJECT_NAME} STATIC ${MOONLIGHT_SOURCES})

# Install the generated static library
install(TARGETS ${PROJECT_NAME}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

# Install the header
install(FILES src/Limelight.h
        DESTINATION ${CMAKE_INSTALL_PREFIX}/include)

# Write the moonlight-config.cmake script
file(WRITE ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}-config.cmake
     "set(MOONLIGHT_LIB ${CMAKE_INSTALL_PREFIX}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}${PROJECT_NAME}${CMAKE_STATIC_LIBRARY_SUFFIX})")
