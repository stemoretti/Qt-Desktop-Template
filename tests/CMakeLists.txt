find_package(Qt5 ${QT_MINIMUM_REQUIRED}
    REQUIRED
    COMPONENTS
        Test
)

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

    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(test_main
    PROPERTIES
        ${DEFAULT_PROPERTIES}
)

target_compile_options(test_main
    ${DEFAULT_COMPILE_OPTIONS}
)

target_link_libraries(test_main
    ${DEFAULT_LINK_LIBRARIES}

    PRIVATE
        Qt5::Test
)
