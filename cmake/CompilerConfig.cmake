set(DEFAULT_PROPERTIES
    CXX_STANDARD              11
    CXX_STANDARD_REQUIRED     YES
    CXX_EXTENSIONS            NO
)

set(DEFAULT_INCLUDE_DIRECTORIES
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include>
)

set(DEFAULT_COMPILE_DEFINITIONS
    PRIVATE
        # enable deprecated warnings for qt < 5.13
        $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_DEPRECATED_WARNINGS>

        # disable deprecated warnings for qt >= 5.13
        $<$<CONFIG:Release>:QT_NO_DEPRECATED_WARNINGS>
)

set(DEFAULT_COMPILE_OPTIONS
    PRIVATE
        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:
            -Wall
            -Wextra
            -Wpedantic
        >

        $<$<CXX_COMPILER_ID:MSVC>:
            /W4
        >
)
