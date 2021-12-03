find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets LinguistTools REQUIRED)

add_executable(${PROJECT_NAME}
    main.cpp
    mainwindow.h
    mainwindow.cpp
    utils.h
    utils.cpp

    mainwindow.ui
)

if(WIN32)
    set(RESOURCES "${PROJECT_SOURCE_DIR}/resources/icon.rc")

    set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)

    configure_file("${PROJECT_SOURCE_DIR}/cmake/installer.iss.in" "${PROJECT_BINARY_DIR}/installer.iss")
endif()

if(APPLE)
    set(RESOURCES "${PROJECT_SOURCE_DIR}/resources/Icon.icns")
    set_source_files_properties("${RESOURCES}" PROPERTIES MACOSX_PACKAGE_LOCATION Resources)

    set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_NAME "${PROJECT_DISPLAY_NAME}"
        MACOSX_BUNDLE TRUE
    )
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy_directory
                "${PROJECT_BINARY_DIR}/translations"
                "${PROJECT_BINARY_DIR}/${PROJECT_DISPLAY_NAME}.app/Contents/Resources/translations"
        COMMENT "Copying translation files into the bundle 'Resources' folder"
        VERBATIM
    )
endif()

target_sources(${PROJECT_NAME} PRIVATE ${RESOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES
    ${DEFAULT_PROPERTIES}

    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}"
)

configure_file("${PROJECT_SOURCE_DIR}/cmake/config.h.in" "${PROJECT_BINARY_DIR}/include/config.h")

target_include_directories(${PROJECT_NAME}
    PRIVATE
        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
)

target_compile_definitions(${PROJECT_NAME}
    ${DEFAULT_COMPILE_DEFINITIONS}
)

target_compile_options(${PROJECT_NAME}
    ${DEFAULT_COMPILE_OPTIONS}
)

target_link_libraries(${PROJECT_NAME}
    ${DEFAULT_LINK_LIBRARIES}

    PRIVATE
        Qt${QT_VERSION_MAJOR}::Widgets
)

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION "${INSTALL_BIN}" COMPONENT runtime
    BUNDLE DESTINATION "." COMPONENT runtime
)

set(LANGUAGES
    # add below the translation languages you want to support
    it
)

foreach(_lang ${LANGUAGES})
    list(APPEND TS_FILES "../translations/${PROJECT_NAME}_${_lang}.ts")
endforeach()

set_source_files_properties(${TS_FILES} PROPERTIES
    OUTPUT_LOCATION "${PROJECT_BINARY_DIR}/translations"
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_translations(${PROJECT_NAME}
        TS_FILES ${TS_FILES}
        QM_FILES_OUTPUT_VARIABLE QM_FILES
        LUPDATE_OPTIONS -no-obsolete
    )
else()
    # add target to update the translation files all at once
    add_custom_target(ts_files_update)

    # add targets to update the translation files one by one
    foreach(_ts_file ${TS_FILES})
        get_filename_component(_ts_name ${_ts_file} NAME_WE)
        add_custom_target("ts_${_ts_name}"
            "${Qt5_LUPDATE_EXECUTABLE}" -no-obsolete "${PROJECT_SOURCE_DIR}/src" -ts ${_ts_file}
            WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
            VERBATIM
        )
        add_dependencies(ts_files_update "ts_${_ts_name}")
    endforeach()

    qt5_add_translation(QM_FILES ${TS_FILES})

    # add target to generate binary translation files and run it at every build
    add_custom_target(qm_files_update ALL DEPENDS ${QM_FILES})
endif()

install(FILES ${QM_FILES} DESTINATION "${INSTALL_TRANSLATIONS}" COMPONENT runtime)
