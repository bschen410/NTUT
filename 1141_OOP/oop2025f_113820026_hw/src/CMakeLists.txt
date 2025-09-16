# Create a library for the sample code
add_library(
    sample_lib
    INTERFACE
)

target_include_directories(sample_lib INTERFACE src/)

# Add main executable
add_executable(
    main
    main.cpp
)

target_link_libraries(
    main
    sample_lib
)
