cmake_minimum_required(VERSION 3.19)

project(qt-desktop-template VERSION 0.1.0 LANGUAGES CXX)

set(PROJECT_DISPLAY_NAME "Qt Desktop Template")
set(PROJECT_URL "https://github.com/stemoretti/qt-desktop-template")

include(GNUInstallDirs)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 COMPONENTS Core Gui Widgets LinguistTools REQUIRED)

# Installation paths
if(APPLE)
    set(INSTALL_DATAROOT     "Resources")
    set(INSTALL_BIN          "MacOS")
    set(INSTALL_DOC          "${INSTALL_DATAROOT}/doc")
    set(INSTALL_DATA         "${INSTALL_DATAROOT}")
    set(INSTALL_TRANSLATIONS "${INSTALL_DATAROOT}/translations")
elseif(UNIX)
    set(INSTALL_DATAROOT     "${CMAKE_INSTALL_DATAROOTDIR}")
    set(INSTALL_BIN          "${CMAKE_INSTALL_BINDIR}")
    set(INSTALL_DOC          "${CMAKE_INSTALL_DOCDIR}")
    set(INSTALL_DATA         "${CMAKE_INSTALL_DATAROOTDIR}/qt-desktop-template")
    set(INSTALL_TRANSLATIONS "${INSTALL_DATA}/translations")
else()
    # Install into local directory
    set(INSTALL_DATAROOT     ".")
    set(INSTALL_BIN          ".")
    set(INSTALL_DOC          "doc")
    set(INSTALL_DATA         ".")
    set(INSTALL_TRANSLATIONS "translations")
endif()

add_subdirectory(res)

add_executable(qt-desktop-template
    src/main.cpp
    src/mainwindow.h
    src/mainwindow.cpp
    src/utils.h
    src/utils.cpp

    src/mainwindow.ui
)

if(WIN32)
    set(RESOURCES "${PROJECT_SOURCE_DIR}/res/icon.rc")

    set_target_properties(qt-desktop-template PROPERTIES WIN32_EXECUTABLE TRUE)

    configure_file("${PROJECT_SOURCE_DIR}/cmake/installer.iss.in" "${PROJECT_BINARY_DIR}/installer.iss")
endif()

if(APPLE)
    set(RESOURCES "${PROJECT_SOURCE_DIR}/res/Icon.icns")
    set_source_files_properties("${RESOURCES}" PROPERTIES MACOSX_PACKAGE_LOCATION Resources)

    set_target_properties(qt-desktop-template PROPERTIES
        OUTPUT_NAME "${PROJECT_DISPLAY_NAME}"
        MACOSX_BUNDLE TRUE
    )
    add_custom_command(TARGET qt-desktop-template POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy_directory
                "${PROJECT_BINARY_DIR}/translations"
                "${PROJECT_BINARY_DIR}/${PROJECT_DISPLAY_NAME}.app/Contents/Resources/translations"
        COMMENT "Copying translation files into the bundle 'Resources' folder"
        VERBATIM
    )
    add_custom_command(TARGET qt-desktop-template POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy_directory
                "${PROJECT_SOURCE_DIR}/res/icons"
                "${PROJECT_BINARY_DIR}/${PROJECT_DISPLAY_NAME}.app/Contents/Resources/icons"
        COMMENT "Copying icons files into the bundle 'Resources' folder"
        VERBATIM
    )
endif()

target_sources(qt-desktop-template PRIVATE ${RESOURCES})

set_target_properties(qt-desktop-template
    PROPERTIES
        CXX_STANDARD              17
        CXX_STANDARD_REQUIRED     YES
        CXX_EXTENSIONS            NO
)

configure_file("${PROJECT_SOURCE_DIR}/cmake/appinfo.h.in" "${PROJECT_BINARY_DIR}/include/appinfo.h")

target_include_directories(qt-desktop-template
    PRIVATE
        "${PROJECT_BINARY_DIR}/include"
)

target_compile_options(qt-desktop-template
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

target_link_libraries(qt-desktop-template
    PRIVATE
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

set(TS_FILES
    translations/qt-desktop-template_it.ts
)

set_source_files_properties(${TS_FILES} PROPERTIES
    OUTPUT_LOCATION "${CMAKE_CURRENT_BINARY_DIR}/translations"
)

qt_add_translations(qt-desktop-template
    TS_FILES ${TS_FILES}
    QM_FILES_OUTPUT_VARIABLE QM_FILES
    LUPDATE_OPTIONS -no-obsolete
)

install(FILES ${QM_FILES} DESTINATION "${INSTALL_TRANSLATIONS}" COMPONENT runtime)

install(TARGETS qt-desktop-template
    RUNTIME DESTINATION "${INSTALL_BIN}" COMPONENT runtime
    BUNDLE DESTINATION "." COMPONENT runtime
)

install(FILES
    LICENSE
    README.rst

    DESTINATION "${INSTALL_DOC}"
    COMPONENT runtime
)
