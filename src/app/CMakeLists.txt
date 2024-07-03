# Create the main executable
add_executable(responder
        main.cpp
        bot.cpp
        bot.h)

# Link libraries to the executable
target_link_libraries(responder PRIVATE
        boost fmt tgbotxx)

# Properties
set_target_properties(responder PROPERTIES
        WIN32_EXECUTABLE ON
        MACOSX_BUNDLE ON
)
