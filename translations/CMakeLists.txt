set(LANGUAGES
    # add below the translation languages you want to support
    it
)

foreach(_lang ${LANGUAGES})
    list(APPEND TS_FILES "${PROJECT_NAME}_${_lang}.ts")
endforeach()

find_package(Qt5 ${QT_MINIMUM_REQUIRED}
    REQUIRED
    COMPONENTS
        LinguistTools
)

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

install(FILES ${QM_FILES} DESTINATION "${INSTALL_TRANSLATIONS}" COMPONENT runtime)
