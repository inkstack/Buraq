
# 
# Executable name and options
# 

# Target name
set(target ${META_PROJECT_NAME_LOWER}-test)
message(STATUS "Test ${target}")


# 
# Sources
# 

set(sources
    main.cpp
    fibonacci_test.cpp
    swap_test.cpp
    gemm_test.cpp
)


# 
# Create executable
# 

# Build executable
add_executable(${target}
    ${sources}
)


# 
# Project options
# 

set_target_properties(${target}
    PROPERTIES
    ${DEFAULT_PROJECT_OPTIONS}
    FOLDER "${IDE_FOLDER}"
)


# 
# Include directories
# 

target_include_directories(${target}
    PRIVATE
    ${DEFAULT_INCLUDE_DIRECTORIES}
    ${PROJECT_BINARY_DIR}/include
    ${PROJECT_SOURCE_DIR}/include
)


# 
# Libraries
# 

target_link_libraries(${target}
    PRIVATE
    ${DEFAULT_LIBRARIES}
    ${META_PROJECT_NAME_LOWER}
    ${META_PROJECT_NAME_LOWER}_ocl
    ${META_PROJECT_NAME_LOWER}_cuda
    gmock
)


# 
# Compile definitions
# 

target_compile_definitions(${target}
    PRIVATE
    ${DEFAULT_COMPILE_DEFINITIONS}
)


# 
# Compile options
# 

target_compile_options(${target}
    PRIVATE
    ${DEFAULT_COMPILE_OPTIONS}
)


# 
# Linker options
# 

target_link_libraries(${target}
    PRIVATE
    ${DEFAULT_LINKER_OPTIONS}
)
