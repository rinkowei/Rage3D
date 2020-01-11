cmake_minimum_required (VERSION 3.10)
if(COMMAND cmake_policy)
    # libraries linked via full path no longer produce linker search paths
    cmake_policy (SET CMP0003 NEW)
    # INTERFACE_LINK_LIBRARIES defines the link interface
    cmake_policy (SET CMP0022 NEW)
    # disallow use of the LOCATION target property - so we set to OLD as we still need it
    cmake_policy (SET CMP0026 OLD)
    # MACOSX_RPATH is enabled by default
    cmake_policy (SET CMP0042 NEW)
    # honor the visibility properties for SHARED target types only
    cmake_policy (SET CMP0063 OLD)
endif()

# set project name
project(Rage3D)