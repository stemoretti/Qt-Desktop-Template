cmake_minimum_required(VERSION 3.5)

project(qt-desktop-template VERSION 0.1.0 LANGUAGES CXX)

set(PROJECT_DISPLAY_NAME "Qt Desktop Template")
set(PROJECT_URL "https://github.com/stemoretti/qt-desktop-template")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

option(BUILD_TESTS "Build tests" OFF)

include(BuildType)
include(CompilerConfig)
include(QtConfig)
include(GNUInstallDirs)

# Installation paths
if(UNIX)
    set(INSTALL_ROOT         "${CMAKE_INSTALL_DATAROOTDIR}")
    set(INSTALL_BIN          "${CMAKE_INSTALL_BINDIR}")
    set(INSTALL_DOC          "${CMAKE_INSTALL_DOCDIR}")
    set(INSTALL_DATA         "${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}")
    set(INSTALL_TRANSLATIONS "${INSTALL_DATA}/translations")
else()
    # Install into local directory
    set(INSTALL_ROOT         ".")
    set(INSTALL_BIN          ".")
    set(INSTALL_DOC          "doc")
    set(INSTALL_DATA         ".")
    set(INSTALL_TRANSLATIONS "translations")
endif()

add_subdirectory(translations)
add_subdirectory(include)
add_subdirectory(resources)
add_subdirectory(package)
add_subdirectory(src)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

install(FILES
    LICENSE
    README.rst

    DESTINATION "${INSTALL_DOC}"
    COMPONENT runtime
)

message(STATUS "Build ${PROJECT_NAME} version: ${PROJECT_VERSION}")
