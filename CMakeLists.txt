cmake_minimum_required(VERSION 3.15)

# Define project name
project(TestJuce VERSION 1.0 LANGUAGES CXX)

# Set JUCE directory (Modify this path to your JUCE installation)
set(JUCE_DIR "C:/Users/guifernandespro/Documents/University of London/juce-8.0.6-windows")  # Change this to the actual JUCE path

# Find JUCE
find_package(JUCE CONFIG REQUIRED)

# Add the JUCE executable
add_executable(TestJuce
    Source/Main.cpp
    Source/MainComponent.cpp
)

# Link JUCE modules
target_link_libraries(TestJuce PRIVATE
    juce::juce_core
    juce::juce_gui_basics
    juce::juce_audio_basics
    juce::juce_audio_devices
)

# Enable JUCE GUI App (If this is a GUI-based project)
juce_generate_juce_main(TestJuce)

# Set C++ Standard
set_property(TARGET TestJuce PROPERTY CXX_STANDARD 17)

# Print JUCE path for debugging
message(STATUS "JUCE Directory: ${JUCE_DIR}")
