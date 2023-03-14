find_package(Threads REQUIRED)

include(FetchContent)
include(CheckIncludeFileCXX)

cmake_policy(SET CMP0097 NEW)

if(CMAKE_CXX_IS_CLANG_WIN)
    # EnlyzeWinCompatLib
    FetchContent_Declare(enlyze_win_compat_lib
        GIT_REPOSITORY https://github.com/LonghronShen/EnlyzeWinCompatLib.git
        GIT_TAG clang
        GIT_SHALLOW TRUE
        GIT_SUBMODULES "")

    FetchContent_GetProperties(enlyze_win_compat_lib)
    if(NOT enlyze_win_compat_lib_POPULATED)
        FetchContent_Populate(enlyze_win_compat_lib)
        add_subdirectory(${enlyze_win_compat_lib_SOURCE_DIR} ${enlyze_win_compat_lib_BINARY_DIR} EXCLUDE_FROM_ALL)
    endif()
endif()