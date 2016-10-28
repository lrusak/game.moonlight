project(pugixml)
cmake_minimum_required(VERSION 2.8.9)

add_library(${PROJECT_NAME} STATIC src/pugixml.cpp)

set_property(TARGET ${PROJECT_NAME}
             PROPERTY POSITION_INDEPENDENT_CODE ON)

install(TARGETS ${PROJECT_NAME}
        ARCHIVE DESTINATION lib)
install(FILES src/pugixml.hpp src/pugiconfig.hpp
        DESTINATION include)

# Write the pugixml-config.cmake script
file(WRITE ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}-config.cmake
    "set(PUGIXML_LIBRARIES ${CMAKE_INSTALL_PREFIX}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}${PROJECT_NAME}${CMAKE_STATIC_LIBRARY_SUFFIX})\n \
     set(PUGIXML_INCLUDE_DIRS ${CMAKE_INSTALL_PREFIX}/include)")
