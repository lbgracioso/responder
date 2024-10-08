cmake_minimum_required(VERSION 3.26)

# Set the project info
project(responder
        VERSION 1.0.0
        DESCRIPTION "A Telegram bot to use some random free APIs and try them out."
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

# Download and link nlohmann_json
CPMAddPackage("gh:nlohmann/json#v3.11.3")

if(json_ADDED)
    find_package(json REQUIRED)
endif()

# Download and link nlohmann_json
CPMAddPackage("gh:brofield/simpleini#v4.22")

if(json_ADDED)
    find_package(json REQUIRED)
endif()

# Download and link libcpr
#CPMAddPackage("gh:libcpr/cpr#1.10.5")

#if(libcpr_ADDED)
#    find_package(libcpr REQUIRED)
#endif()
# This is not exactly needed because "tgbot" lib already includes this one.

# Download and link spdlog
CPMAddPackage("gh:gabime/spdlog#v1.14.1")

if(spdlog_ADDED)
    find_package(spdlog REQUIRED)
endif()

# Link subdirectories
include_directories(include config src)
add_subdirectory(src/app)
