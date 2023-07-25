install(FILES
    "qt-desktop-template.desktop"
    DESTINATION "${INSTALL_DATAROOT}/applications"
    COMPONENT runtime
)
install(DIRECTORY icons DESTINATION "${INSTALL_DATAROOT}" COMPONENT runtime)
install(
    FILES "../qt-desktop-template.svg"
    DESTINATION "${INSTALL_DATAROOT}/icons/hicolor/scalable/apps"
    COMPONENT runtime
)
