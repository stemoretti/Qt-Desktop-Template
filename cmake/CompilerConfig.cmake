set(DEFAULT_PROPERTIES
    CXX_STANDARD              11
    CXX_STANDARD_REQUIRED     YES
    CXX_EXTENSIONS            NO
)

set(DEFAULT_INCLUDE_DIRECTORIES
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include>
)

set(DEFAULT_COMPILE_OPTIONS
    PRIVATE
        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:
            -Wall
            -Wextra
            -Wpedantic
            -DQT_DEPRECATED_WARNINGS
        >

        $<$<CXX_COMPILER_ID:MSVC>:
            /W4
        >
)
