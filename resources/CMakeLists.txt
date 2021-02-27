if(UNIX)
    install(FILES
        "${PROJECT_NAME}.desktop"
        DESTINATION "${INSTALL_DATAROOT}/applications"
    )
endif()

install(DIRECTORY icons DESTINATION "${INSTALL_DATAROOT}")
