cmake_minimum_required(VERSION 3.26)

# Set the project info
project(responder
        VERSION 1.0.0
        DESCRIPTION "A Telegram bot to interact with specified messages."
        HOMEPAGE_URL https://github.com/lbgracioso/responder
        LANGUAGES CXX
)

# Enable C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Include CPM.cmake for package management
# You can download CPM.cmake from https://github.com/cpm-cmake/CPM.cmake
# and place it in your project directory, or use the following snippet to download it automatically.

if (NOT CPM_SOURCE_CACHE)
    set(CPM_SOURCE_CACHE "${CMAKE_BINARY_DIR}/cpm_cache")
endif ()

if (NOT EXISTS "${CMAKE_BINARY_DIR}/CPM.cmake")
    message(STATUS "Downloading CPM.cmake to ${CMAKE_BINARY_DIR}")
    file(DOWNLOAD https://github.com/cpm-cmake/CPM.cmake/releases/latest/download/CPM.cmake
            "${CMAKE_BINARY_DIR}/CPM.cmake")
endif ()

include(${CMAKE_BINARY_DIR}/CPM.cmake)

# Download and link Boost
CPMAddPackage(
        NAME Boost
        VERSION 1.84.0
        URL https://github.com/boostorg/boost/releases/download/boost-1.84.0/boost-1.84.0.tar.xz
        URL_HASH SHA256=2e64e5d79a738d0fa6fb546c6e5c2bd28f88d268a2a080546f74e5ff98f29d0e
        OPTIONS "BOOST_ENABLE_CMAKE ON" "BOOST_INCLUDE_LIBRARIES container\\\;asio\\\;system"
)

if (Boost_ADDED)
    find_package(Boost REQUIRED)
    add_library(boost INTERFACE)
    target_link_libraries(boost INTERFACE Boost::asio Boost::container Boost::system)
endif ()

# Download and link FMT
CPMAddPackage("gh:fmtlib/fmt#10.2.1")

if (fmt_ADDED)
    find_package(fmt REQUIRED)
    target_link_libraries(fmt INTERFACE fmt::fmt)
endif ()

# Download and link tgbotxx
CPMAddPackage(
        NAME tgbotxx
        VERSION 1.0.6.9
        GIT_REPOSITORY https://github.com/baderouaich/tgbotxx
)

if (tgbotxx_ADDED)
    find_package(tgbotxx)
endif()

# Link subdirectories
include_directories(src)
add_subdirectory(src/app)
