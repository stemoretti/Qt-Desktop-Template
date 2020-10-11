add_executable(${PROJECT_NAME} WIN32 "")

target_sources(${PROJECT_NAME}
    PRIVATE
        main.cpp
        mainwindow.h
        mainwindow.cpp
        utils.h
        utils.cpp

        # ui files
        mainwindow.ui
)

target_include_directories(${PROJECT_NAME}
    ${DEFAULT_INCLUDE_DIRECTORIES}
)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
        ${DEFAULT_PROPERTIES}

        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)

target_compile_options(${PROJECT_NAME}
    ${DEFAULT_COMPILE_OPTIONS}
)

target_link_libraries(${PROJECT_NAME}
    ${DEFAULT_LINK_LIBRARIES}
)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION "${INSTALL_BIN}")
