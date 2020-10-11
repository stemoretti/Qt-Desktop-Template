if(WIN32)
    configure_file(${PROJECT_NAME}.iss.in "${CMAKE_BINARY_DIR}/${PROJECT_NAME}.iss")
endif()
