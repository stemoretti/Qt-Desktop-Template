if(APPLE)
    install(FILES
        "Icon.icns"
        DESTINATION "${INSTALL_DATA}"
        COMPONENT runtime
    )
elseif(UNIX)
    install(FILES
        "${PROJECT_NAME}.desktop"
        DESTINATION "${INSTALL_DATAROOT}/applications"
        COMPONENT runtime
    )
endif()

install(DIRECTORY icons DESTINATION "${INSTALL_DATAROOT}" COMPONENT runtime)
