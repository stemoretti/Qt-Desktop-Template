find_package(QT NAMES Qt6 Qt5 COMPONENTS Test REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Test REQUIRED)

add_executable(test_main
    test_main.cpp
    test_suite.h
    test_suite.cpp
)

add_test(
    NAME test_main
    COMMAND test_main
)

target_include_directories(test_main
    ${DEFAULT_INCLUDE_DIRECTORIES}
)

set_target_properties(test_main PROPERTIES
    ${DEFAULT_PROPERTIES}
)

target_compile_options(test_main
    ${DEFAULT_COMPILE_OPTIONS}
)

target_link_libraries(test_main
    ${DEFAULT_LINK_LIBRARIES}

    PRIVATE
        Qt${QT_VERSION_MAJOR}::Test
)
