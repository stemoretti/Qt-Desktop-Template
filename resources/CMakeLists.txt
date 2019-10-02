if(UNIX)
    install(FILES
        qt-desktop-template.desktop
        DESTINATION "${INSTALL_SHARE}/applications"
        COMPONENT runtime
    )
endif()

install(DIRECTORY icons DESTINATION "${INSTALL_SHARE}" COMPONENT runtime)
