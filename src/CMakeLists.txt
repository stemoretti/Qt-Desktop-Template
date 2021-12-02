configure_file(config.h.in "${CMAKE_BINARY_DIR}/include/config.h")

set(SOURCES
    main.cpp
    mainwindow.h
    mainwindow.cpp
    utils.h
    utils.cpp

    # ui files
    mainwindow.ui
)

if(WIN32)
    set(RESOURCES "${PROJECT_SOURCE_DIR}/resources/icon.rc")
elseif(APPLE)
    set(RESOURCES "${PROJECT_SOURCE_DIR}/resources/Icon.icns")
    set_source_files_properties("${RESOURCES}" PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
endif()

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME} MANUAL_FINALIZATION ${SOURCES} ${RESOURCES})
else()
    add_executable(${PROJECT_NAME} ${SOURCES} ${RESOURCES})
endif()

target_include_directories(${PROJECT_NAME}
    ${DEFAULT_INCLUDE_DIRECTORIES}
)

target_compile_definitions(${PROJECT_NAME}
    ${DEFAULT_COMPILE_DEFINITIONS}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    ${DEFAULT_PROPERTIES}

    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)

if(WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)
elseif(APPLE AND BUILD_MACOSX_BUNDLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_NAME "${PROJECT_DISPLAY_NAME}"
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_INFO_PLIST "${PROJECT_SOURCE_DIR}/package/Info.plist.in"
    )
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_BINARY_DIR}/translations
                ${CMAKE_BINARY_DIR}/${PROJECT_DISPLAY_NAME}.app/Contents/Resources/translations
        COMMENT "Copying translation files into the bundle 'Resources' folder"
        VERBATIM
    )
endif()

target_compile_options(${PROJECT_NAME}
    ${DEFAULT_COMPILE_OPTIONS}
)

target_link_libraries(${PROJECT_NAME}
    ${DEFAULT_LINK_LIBRARIES}
)

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION "${INSTALL_BIN}" COMPONENT runtime
    BUNDLE DESTINATION . COMPONENT runtime
)

set(LANGUAGES
    # add below the translation languages you want to support
    it
)

foreach(_lang ${LANGUAGES})
    list(APPEND TS_FILES "../translations/${PROJECT_NAME}_${_lang}.ts")
endforeach()

set_source_files_properties(${TS_FILES} PROPERTIES
    OUTPUT_LOCATION "${CMAKE_BINARY_DIR}/translations"
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
            ${Qt5_LUPDATE_EXECUTABLE} -no-obsolete "${PROJECT_SOURCE_DIR}/src" -ts ${_ts_file}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            VERBATIM
        )
        add_dependencies(ts_files_update "ts_${_ts_name}")
    endforeach()

    qt5_add_translation(QM_FILES ${TS_FILES})

    # add target to generate binary translation files and run it at every build
    add_custom_target(qm_files_update ALL DEPENDS ${QM_FILES})
endif()

install(FILES ${QM_FILES} DESTINATION "${INSTALL_TRANSLATIONS}" COMPONENT runtime)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif()
