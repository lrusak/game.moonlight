project(moonlight)
cmake_minimum_required(VERSION 2.8)

set(MOONLIGHT_SOURCES
    limelight-common/OpenAES/oaes_base64.c
    limelight-common/OpenAES/oaes_lib.c
    limelight-common/AudioStream.c
    limelight-common/ByteBuffer.c
    limelight-common/Connection.c
    limelight-common/ControlStream.c
    limelight-common/FakeCallbacks.c
    limelight-common/InputStream.c
    limelight-common/LinkedBlockingQueue.c
    limelight-common/Misc.c
    limelight-common/Platform.c
    limelight-common/PlatformSockets.c
    limelight-common/RtpReorderQueue.c
    limelight-common/RtspConnection.c
    limelight-common/RtspParser.c
    limelight-common/SdpGenerator.c
    limelight-common/VideoDepacketizer.c
    limelight-common/VideoStream.c
)

set(CMAKE_POSITION_INDEPENDENT_CODE ON) 
add_library(${PROJECT_NAME} STATIC ${MOONLIGHT_SOURCES})

# Install the generated static library
install(TARGETS ${PROJECT_NAME}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

# Install the header
install(FILES limelight-common/Limelight.h
        DESTINATION ${CMAKE_INSTALL_PREFIX}/include)

# Write the moonlight-config.cmake script
file(WRITE ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}-config.cmake
     "set(MOONLIGHT_LIB ${CMAKE_INSTALL_PREFIX}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}${PROJECT_NAME}${CMAKE_STATIC_LIBRARY_SUFFIX})")
