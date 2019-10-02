set(TS_FILES
    # add the translation files here
    qt-desktop-template_it.ts
)

find_package(Qt5 ${QT_MINIMUM_REQUIRED}
    REQUIRED
    COMPONENTS
        LinguistTools
)

# add ts_files_update target for manually updating every translation instead of
# using qt5_create_translation() because it has the bad behaviour of automatically
# updating the translation if a source file has changed
add_custom_target(ts_files_update)

# add targets for the individual update of each translation file
foreach(_ts_file ${TS_FILES})
    get_filename_component(_ts_name ${_ts_file} NAME_WE)
    add_custom_target("ts_${_ts_name}"
        ${Qt5_LUPDATE_EXECUTABLE} -no-obsolete "${CMAKE_SOURCE_DIR}/src" -ts ${_ts_file}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        VERBATIM
    )
    add_dependencies(ts_files_update "ts_${_ts_name}")
endforeach()

qt5_add_translation(QM_FILES ${TS_FILES})

# add qm_files_update target for generating binary translation files
# and run it at every build
add_custom_target(qm_files_update ALL DEPENDS ${QM_FILES})

install(FILES ${QM_FILES} DESTINATION "${INSTALL_TRANSLATIONS}" COMPONENT runtime)
