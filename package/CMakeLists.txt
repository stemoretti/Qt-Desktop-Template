if(WIN32)
    configure_file(installer.iss.in "${CMAKE_BINARY_DIR}/installer.iss")
endif()
