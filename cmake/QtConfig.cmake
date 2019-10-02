# Qt default settings

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

if(NOT QT_MINIMUM_REQUIRED)
    set(QT_MINIMUM_REQUIRED 5.9.0)
endif()

find_package(Qt5 ${QT_MINIMUM_REQUIRED}
    REQUIRED
    COMPONENTS
        Core
        Gui
        Widgets
)

# Get upper case system name
string(TOUPPER ${CMAKE_SYSTEM_NAME} SYSTEM_NAME_UPPER)

# Determine architecture (32/64 bit)
set(X64 OFF)
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(X64 ON)
endif()

set(DEFAULT_PROPERTIES
    CXX_STANDARD              11
    CXX_STANDARD_REQUIRED     YES
    CXX_EXTENSIONS            YES
)

set(DEFAULT_INCLUDE_DIRECTORIES
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include>
)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

set(DEFAULT_LINK_LIBRARIES
    PRIVATE
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        ${CMAKE_THREAD_LIBS_INIT}
)

set(DEFAULT_COMPILE_DEFINITIONS
    SYSTEM_${SYSTEM_NAME_UPPER}
)

# MSVC compiler options
if("${CMAKE_CXX_COMPILER_ID}" MATCHES "MSVC")
    set(DEFAULT_COMPILE_DEFINITIONS ${DEFAULT_COMPILE_DEFINITIONS}
        # Calling any one of the potentially unsafe methods in the Standard C++ Library
        _SCL_SECURE_NO_WARNINGS
        # Calling any one of the potentially unsafe methods in the CRT Library
        _CRT_SECURE_NO_WARNINGS
    )
endif()

set(DEFAULT_COMPILE_OPTIONS)

# MSVC compiler options
if("${CMAKE_CXX_COMPILER_ID}" MATCHES "MSVC")
    set(DEFAULT_COMPILE_OPTIONS ${DEFAULT_COMPILE_OPTIONS}
        PRIVATE
            /MP     # build with multiple processes
            /W4     # warning level 4
            # /WX   # treat warnings as errors

            #$<$<CONFIG:Debug>:
                #/RTCc  # value is assigned to a smaller data type and results in a data loss
            #>

            $<$<CONFIG:Release>:
                /Gw     # whole program global optimization
                /GS-    # buffer security check: no
                /GL     # whole program optimization: enable link-time code generation (disables Zi)
                /GF     # enable string pooling
            >
            # No manual c++11 enable for MSVC as all supported MSVC versions
            # for cmake-init have C++11 implicitly enabled (MSVC >=2013)
        PUBLIC
            # disable warning: 'identifier': class 'type' needs to have
            # dll-interface to be used by clients of class 'type2'
            /wd4251
            # disable warning: 'identifier': symbol will be dynamically
            # initialized (implementation limitation)
            /wd4592
            # disable warning: nonstandard extension used: nameless
            # struct/union (caused by GLM)
            /wd4201
            # disable warning: conditional expression is
            # constant (caused by Qt)
            /wd4127
    )
# GCC and Clang compiler options
elseif("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU|Clang")
    set(DEFAULT_COMPILE_OPTIONS ${DEFAULT_COMPILE_OPTIONS}
        PRIVATE
            -Wall
            -Wextra
            -DQT_DEPRECATED_WARNINGS

            $<$<CXX_COMPILER_ID:GNU>:
                #-Wmaybe-uninitialized

                $<$<VERSION_GREATER:$<CXX_COMPILER_VERSION>,4.8>:
                    -Wpedantic

                    #-Wreturn-local-addr
                >
            >
            $<$<CXX_COMPILER_ID:Clang>:
                -Wpedantic
                # -Wreturn-stack-address # gives false positives
            >
            $<$<BOOL:${OPTION_COVERAGE_ENABLED}>:
                -fprofile-arcs
                -ftest-coverage
            >
        PUBLIC
            $<$<PLATFORM_ID:Darwin>:
            >
    )
endif()

# Linker options
set(DEFAULT_LINKER_OPTIONS)

# Use pthreads on mingw and linux
if("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU" OR "${CMAKE_SYSTEM_NAME}" MATCHES "Linux")
    set(DEFAULT_LINKER_OPTIONS ${DEFAULT_LINKER_OPTIONS}
    )

    if(${OPTION_COVERAGE_ENABLED})
        set(DEFAULT_LINKER_OPTIONS ${DEFAULT_LINKER_OPTIONS}
            PUBLIC
                -fprofile-arcs
                -ftest-coverage
        )
    endif()
endif()

if(WIN32)
    set(CMAKE_WIN32_EXECUTABLE ON)
endif()
