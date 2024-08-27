# Create the main executable
add_executable(responder
        main.cpp
        bot.cpp
        handler.cpp
        mememaker.cpp
        log.cpp
)

# Link libraries to the executable
target_link_libraries(responder PRIVATE
        boost fmt tgbotxx nlohmann_json SimpleIni spdlog)

# Properties
set_target_properties(responder PROPERTIES
        WIN32_EXECUTABLE ON
        MACOSX_BUNDLE ON
)
