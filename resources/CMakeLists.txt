if(UNIX)
    install(FILES
        "${PROJECT_NAME}.desktop"
        DESTINATION "${INSTALL_ROOT}/applications"
    )
endif()

install(DIRECTORY icons DESTINATION "${INSTALL_ROOT}")
