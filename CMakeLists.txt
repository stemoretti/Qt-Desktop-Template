cmake_minimum_required(VERSION 3.19)

project(qt-desktop-template VERSION 0.1.0 LANGUAGES CXX)

set(PROJECT_DISPLAY_NAME "Qt Desktop Template")
set(PROJECT_URL "https://github.com/stemoretti/qt-desktop-template")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 COMPONENTS Core Gui Widgets LinguistTools REQUIRED)

qt_add_executable(qt-desktop-template
    src/main.cpp
    src/mainwindow.h
    src/mainwindow.cpp
    src/utils.h
    src/utils.cpp

    src/mainwindow.ui
)

if(WIN32)
    # Install into local directory
    set(INSTALL_DATAROOT     ".")
    set(INSTALL_BIN          ".")
    set(INSTALL_DOC          "doc")
    set(INSTALL_DATA         ".")
    set(INSTALL_TRANSLATIONS "translations")

    target_sources(qt-desktop-template PRIVATE "${PROJECT_SOURCE_DIR}/packaging/windows/icon.rc")

    set_target_properties(qt-desktop-template PROPERTIES WIN32_EXECUTABLE TRUE)

    configure_file(
        "${PROJECT_SOURCE_DIR}/packaging/windows/installer.iss.in"
        "${PROJECT_BINARY_DIR}/installer.iss"
    )

    install(TARGETS qt-desktop-template
        RUNTIME DESTINATION "${INSTALL_BIN}" COMPONENT runtime
    )
elseif(APPLE)
    set(INSTALL_DATAROOT     "Resources")
    set(INSTALL_BIN          "MacOS")
    set(INSTALL_DOC          "${INSTALL_DATAROOT}/doc")
    set(INSTALL_DATA         "${INSTALL_DATAROOT}")
    set(INSTALL_TRANSLATIONS "${INSTALL_DATAROOT}/translations")

    set(ICON "${PROJECT_SOURCE_DIR}/packaging/macos/Icon.icns")
    set_source_files_properties("${ICON}" PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
    target_sources(qt-desktop-template PRIVATE ${ICON})

    set_target_properties(qt-desktop-template PROPERTIES
        OUTPUT_NAME "${PROJECT_DISPLAY_NAME}"
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_INFO_PLIST "${PROJECT_SOURCE_DIR}/packaging/macos/Info.plist.in"
    )

    install(TARGETS qt-desktop-template BUNDLE DESTINATION "." COMPONENT runtime)
elseif(UNIX)
    include(GNUInstallDirs)
    set(INSTALL_DATAROOT     "${CMAKE_INSTALL_DATAROOTDIR}")
    set(INSTALL_BIN          "${CMAKE_INSTALL_BINDIR}")
    set(INSTALL_DOC          "${CMAKE_INSTALL_DOCDIR}")
    set(INSTALL_DATA         "${CMAKE_INSTALL_DATAROOTDIR}/qt-desktop-template")
    set(INSTALL_TRANSLATIONS "${INSTALL_DATA}/translations")

    add_subdirectory(packaging/linux)

    install(TARGETS qt-desktop-template
        RUNTIME DESTINATION "${INSTALL_BIN}" COMPONENT runtime
    )
endif()

configure_file("${PROJECT_SOURCE_DIR}/src/appinfo.h.in" "${PROJECT_BINARY_DIR}/include/appinfo.h")

set_target_properties(qt-desktop-template
    PROPERTIES
        CXX_STANDARD              17
        CXX_STANDARD_REQUIRED     YES
        CXX_EXTENSIONS            NO
)

target_include_directories(qt-desktop-template
    PRIVATE
        "${PROJECT_BINARY_DIR}/include"
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

install(FILES
    LICENSE
    README.rst

    DESTINATION "${INSTALL_DOC}"
    COMPONENT runtime
)
