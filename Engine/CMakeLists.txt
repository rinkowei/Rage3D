include(CheckIncludeFile)
foreach(HEADER stdint.h inttypes.h malloc.h)
    string(TOUPPER HAVE_${HEADER} HAVE_HEADER)
    string(REPLACE . _ HAVE_HEADER ${HAVE_HEADER})
    check_include_file(${HEADER} ${HAVE_HEADER})
endforeach()

include(CheckFunctionExists)
foreach(FUNCT __sincosf malloc_usable_size)
    string(TOUPPER HAVE_${FUNCT} HAVE_FUNCT)
    check_function_exists (${FUNCT} ${HAVE_FUNCT})
endforeach()

include(CheckLibraryExists)
check_library_exists(m sincosf "" HAVE_SINCOSF)
if(MINGW)
    include(CheckStructHasMember)
    check_struct_has_member(RTL_OSVERSIONINFOW dwOSVersionInfoSize minwindef.h\;winnt.h HAVE_RTL_OSVERSIONINFOW)
endif()

# Setup RPATH settings
if(RAGE3D_LIB_TYPE STREQUAL SHARED AND NOT WIN32 AND NOT ANDROID AND NOT IOS AND NOT TVOS AND NOT WEB)
    # add RPATH entries when building
    set(CMAKE_SKIP_BUILD_RPATH FALSE)
    # and set the RPATH entries so that the executable works both in the build tree and install destination
    set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
    if(APPLE)
        set(CMAKE_MACOSX_RPATH TRUE)
        set(ORIGIN @loader_path)
    else()
        set(ORIGIN $ORIGIN)
    endif()

    # Library location relative to the executable in the build tree
    set (CMAKE_INSTALL_RPATH ${ORIGIN}/../lib)

    # Library location relative to the executable in the tool directory in the build tree
    list (APPEND CMAKE_INSTALL_RPATH ${ORIGIN}/../../lib)                               # The tools are installed one directory further down from normal executable
    # Library location relative to the executable in the install destination
    list (APPEND CMAKE_INSTALL_RPATH ${ORIGIN}/../lib${LIB_SUFFIX}/${PATH_SUFFIX})      # The library location is based on SDK install destination
    # Library location relative to the executable in the tool directory in the install destination
    list (APPEND CMAKE_INSTALL_RPATH ${ORIGIN}/../../lib${LIB_SUFFIX}/${PATH_SUFFIX})
    # The last entry to the install destination of the library, if the destination location is not in the system default search path, e.g. /usr/local/lib
    list (FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES ${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX} isSystemDir)
    if (isSystemDir STREQUAL -1)
        list (APPEND CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/${DEST_LIBRARY_DIR})
    endif ()
endif ()

# add targets
foreach(TARGET ETCPACK FreeType LZ4 PugiXml rapidjson SDL StanHull STB)
    add_subdirectory(ThirdParty/${TARGET})
endforeach()

if(RAGE3D_ANGELSCRIPT)
    add_subdirectory (ThirdParty/AngelScript)
    if(WEB OR (ARM AND RAGE3D_64BIT))
        add_subdirectory(ThirdParty/boost)
    endif()
endif()

if(RAGE3D_LUA)
    add_subdirectory(ThirdParty/Lua${JIT})
    add_subdirectory(ThirdParty/toluapp/src/lib)
endif()

if(RAGE3D_NETWORK)
    add_subdirectory(ThirdParty/Civetweb)
    add_subdirectory(ThirdParty/SLikeNet)
endif()

if(RAGE3D_DATABASE_ODBC)
    add_subdirectory (ThirdParty/nanodbc)
endif()

if(RAGE3D_DATABASE_SQLITE)
    add_subdirectory(ThirdParty/SQLite)
endif()

if(RAGE3D_IK)
    add_subdirectory(ThirdParty/ik)
endif()

if (RAGE3D_NAVIGATION)
    add_subdirectory (ThirdParty/Detour)
    add_subdirectory (ThirdParty/DetourCrowd)
    add_subdirectory (ThirdParty/DetourTileCache)
    add_subdirectory (ThirdParty/Recast)
endif ()

if (RAGE3D_RAGE2D)
    add_subdirectory (ThirdParty/Box2D)
    if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/spine)
        add_subdirectory (ThirdParty/spine)
        # Add definition for Spine
        add_definitions (-DRAGE3D_SPINE)
    endif ()
endif ()

if (RAGE3D_WEBP)
    add_subdirectory(ThirdParty/WebP)
endif ()

if (RAGE3D_PHYSICS)
    add_subdirectory(ThirdParty/Bullet)
endif ()

if (NOT ANDROID AND NOT ARM AND NOT WEB)
    if (RAGE3D_OPENGL)
        add_subdirectory(ThirdParty/GLEW)
    elseif (NOT RAGE3D_D3D11)
        add_subdirectory(ThirdParty/MojoShader)
    endif ()
    if (NOT CMAKE_SYSTEM_NAME STREQUAL Linux)
        add_subdirectory(ThirdParty/LibCpuId)
    endif ()
endif ()

add_subdirectory(Source)

if (RAGE3D_CLANG_TOOLS)
    add_subdirectory(Clang-Tools)
endif ()

add_subdirectory (Tools)

add_subdirectory (Samples)

if (RAGE3D_EXTRAS)
    add_subdirectory (Extras)
endif ()
