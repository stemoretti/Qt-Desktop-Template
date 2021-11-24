if(WIN32)
    configure_file(installer.iss.in "${CMAKE_BINARY_DIR}/installer.iss")
endif()

if(APPLE)
    set(INFO_PLIST_FILE "${CMAKE_BINARY_DIR}/Info.plist")
    configure_file(Info.plist.in ${INFO_PLIST_FILE})
    install(FILES ${INFO_PLIST_FILE} DESTINATION "." COMPONENT runtime)
endif()
