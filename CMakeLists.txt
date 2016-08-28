project(game.moonlight)

cmake_minimum_required(VERSION 2.6)
enable_language(CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR})

find_package(Kodi           REQUIRED)
find_package(kodiplatform   REQUIRED)
find_package(p8-platform    REQUIRED)
find_package(moonlight      REQUIRED)
find_package(OpenSSL        REQUIRED)
find_package(CURL           REQUIRED)
find_package(pugixml        REQUIRED)
find_package(enet           REQUIRED)

include_directories(
        ${INCLUDES}
        ${KODI_INCLUDE_DIR}
        ${kodiplatform_INCLUDE_DIRS}
        ${p8-platform_INCLUDE_DIRS}
        ${OPENSSL_INCLUDE_DIRS}
        ${CURL_INCLUDE_DIR}
        ${PROJECT_SOURCE_DIR}/src)

list(APPEND DEPLIBS
            ${kodiplatform_LIBRARIES}
            ${p8-platform_LIBRARIES}
            ${OPENSSL_LIBRARIES}
            ${CURL_LIBRARIES}
            ${PUGIXML_LIBRARY}
            ${MOONLIGHT_LIB}
            ${ENET_LIB})

set(MOONLIGHT_SOURCES
        src/MoonlightClient.cpp
        src/MoonlightEnvironment.cpp
        src/input/InputManager.cpp
        src/log/Log.cpp
        src/log/LogAddon.cpp
        src/log/LogConsole.cpp
        src/log/LogSyslog.cpp
        src/nvstream/CertKeyPair.cpp
        src/nvstream/NvApp.cpp
        src/nvstream/NvHTTP.cpp
        src/nvstream/PairingManager.cpp
        src/nvstream/http.c
        src/settings/Resolution.cpp
        src/settings/Settings.cpp
        src/callbacks/VideoCallbacks.cpp
        src/callbacks/ConnectionCallbacks.cpp
        src/callbacks/AudioCallbacks.cpp)


# build standalone
set(STANDALONE_SOURCES ${MOONLIGHT_SOURCES} src/main.cpp)
add_executable(moonlight_client ${STANDALONE_SOURCES})
target_link_libraries(moonlight_client ${DEPLIBS})

# build addon
set(ADDON_SOURCES ${MOONLIGHT_SOURCES} src/addon.cpp)
build_addon(game.moonlight ADDON DEPLIBS)

include(CPack)

################################################################################
#
#  Warnings
#
################################################################################

# Uncomment to compile with pedantic warnings. Disabled because of excessive
# warnings despite valid behavior in add-on API callbacks:
#
#   warning: ISO C++ forbids casting between pointer-to-function and pointer-to-object
#
#set(WARN_PEDANTIC "-Wpedantic")

if(MSVC)
    # Force to always compile with W4
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    # Update if necessary
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long ${WARN_PEDANTIC}")
endif()

