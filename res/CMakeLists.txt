if(UNIX)
    install(FILES
        "qt-desktop-template.desktop"
        DESTINATION "${INSTALL_DATAROOT}/applications"
        COMPONENT runtime
    )
endif()

install(DIRECTORY icons DESTINATION "${INSTALL_DATAROOT}" COMPONENT runtime)
