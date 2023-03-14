cmake_minimum_required(VERSION 3.21)

set(project_name "no-crt-template")
project(${project_name} C CXX)

if(NOT WIN32)
    message(FATAL_ERROR "Unsupported platform detected")
endif()

file(GLOB src
    ${CMAKE_CURRENT_LIST_DIR}/*.c
    ${CMAKE_CURRENT_LIST_DIR}/*.cpp
    ${CMAKE_CURRENT_LIST_DIR}/*.h
    ${CMAKE_CURRENT_LIST_DIR}/*.def
    ${CMAKE_CURRENT_LIST_DIR}/*.rc
)

include(WinCompat)

add_executable(${project_name} ${src})

target_compile_definitions(${project_name}
    PRIVATE "_CRT_SECURE_NO_WARNINGS"
    PRIVATE "_CRT_NONSTDC_NO_DEPRECATE"
    PRIVATE "_TIMESPEC_DEFINED"
    PRIVATE "_WIN32_WINNT=0x0400"
    PRIVATE "WINVER=0x0400"
    PRIVATE "WIN32"
    PRIVATE "_UNICODE"
    PRIVATE "UNICODE"
)

if(MSVC)
    add_wincompat(${project_name})

    set_property(TARGET ${project_name} PROPERTY
        MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

    target_compile_options(${project_name}
        PRIVATE /Gm
        PRIVATE /GX
        PRIVATE /ZI
        PRIVATE /GR-
        PRIVATE /c
        PRIVATE /GS-
        PRIVATE /Gy
        PRIVATE /Oi
        PRIVATE /arch:IA32
        PRIVATE -march=pentium-mmx
        PRIVATE -Gs9999999
    )

    target_link_options(${project_name}
        PRIVATE /MANIFEST:NO
        PRIVATE /machine:I386
        PRIVATE /nodefaultlib
        PRIVATE /SAFESEH:NO
        PRIVATE /OPT:REF
        PRIVATE /subsystem:console,4.0
    )
elseif(CMAKE_CXX_IS_CLANG_WIN)
    target_link_options(${project_name}
        PRIVATE -Xlinker "/subsystem:console,4.0"
        # PRIVATE "-Xlinker /force"
        # PRIVATE -Wl,-nodefaultlib
    )

    add_wincompat(${project_name})
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    target_compile_options(${project_name}
        PRIVATE -static-libgcc
        PRIVATE -static-libstdc++
        PRIVATE -Wl,--enable-stdcall-fixup
    )

    target_link_options(${project_name}
        # PRIVATE -nodefaultlibs
        # PRIVATE -nostdlib
        PRIVATE -static-libgcc
        PRIVATE -static-libstdc++
    )
endif()

set_target_properties(${project_name} PROPERTIES PREFIX "")
