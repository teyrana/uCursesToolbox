#===========================================================================
# FILE:  uNCMS/CMakeLists.txt
# DATE:  2012/07/24
# INFO:  Top-level CMakeLists.txt file for the moos-ivp-extend project
# NAME:  Maintained by Mike Benjamin - Original setup by Christian Convey
#        Chris Gagner, and tips borrowed from Dave Billin
#===========================================================================

CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

#=============================================================================
# Set the output directories for the binary and library files
#=============================================================================

GET_FILENAME_COMPONENT(IVP_EXTEND_BIN_DIR "${CMAKE_SOURCE_DIR}/bin"  ABSOLUTE )
GET_FILENAME_COMPONENT(IVP_EXTEND_LIB_DIR "${CMAKE_SOURCE_DIR}/lib"  ABSOLUTE )

SET( LIBRARY_OUTPUT_PATH      "${IVP_EXTEND_LIB_DIR}" CACHE PATH "" )
SET( ARCHIVE_OUTPUT_DIRECTORY "${IVP_EXTEND_LIB_DIR}" CACHE PATH "" )
SET( LIBRARY_OUTPUT_DIRECTORY "${IVP_EXTEND_LIB_DIR}" CACHE PATH "" )

SET( EXECUTABLE_OUTPUT_PATH    "${IVP_EXTEND_BIN_DIR}" CACHE PATH "" )
SET( RUNTIME_OUTPUT_DIRECTORY "${IVP_EXTEND_BIN_DIR}"  CACHE PATH "" )

#=============================================================================
# Find MOOS
#=============================================================================
find_package(MOOS 10.0)
INCLUDE_DIRECTORIES( SYSTEM ${MOOS_INCLUDE_DIRS})

#=============================================================================
# Find the "moos-ivp" base directory
#=============================================================================

# Search for the moos-ivp folder
find_path( MOOSIVP_SOURCE_TREE_BASE
           NAMES build-ivp.sh build-moos.sh configure-ivp.sh
           PATHS "~/moos-ivp" "~/moos-ivp/trunk/"
           DOC "Base directory of the MOOS-IvP source tree"
           NO_DEFAULT_PATH
)

if (NOT MOOSIVP_SOURCE_TREE_BASE)
    message("Please set MOOSIVP_SOURCE_TREE_BASE to  ")
    message("the location of the \"moos-ivp\" folder ")
    return()
endif()

# ---------------------------------------
# Libraries have been installed in:
#    /usr/local/lib
#
# If you ever happen to want to link against installed libraries
# in a given directory, LIBDIR, you must either use libtool, and
# specify the full pathname of the library, or use the '-LLIBDIR'
# flag during linking and do at least one of the following:
#    - add LIBDIR to the 'LD_LIBRARY_PATH' environment variable
#      during execution
#    - add LIBDIR to the 'LD_RUN_PATH' environment variable
#      during linking
#    - use the '-Wl,-rpath -Wl,LIBDIR' linker flag
#    - have your system administrator add LIBDIR to '/etc/ld.so.conf'
#
# See any operating system documentation about shared libraries for
# more information, such as the ld(1) and ld.so(8) manual pages.
# ----------------------------------------------------------------------

SET(PROJ_LIBRARIES proj)
LINK_DIRECTORIES(/usr/local/lib)

#=============================================================================
# Specify where to find IvP's headers and libraries...
#=============================================================================

FILE(GLOB IVP_INCLUDE_DIRS ${MOOSIVP_SOURCE_TREE_BASE}/ivp/src/lib_* )
INCLUDE_DIRECTORIES(SYSTEM ${IVP_INCLUDE_DIRS})

FILE(GLOB IVP_LIBRARY_DIRS ${MOOSIVP_SOURCE_TREE_BASE}/lib )
LINK_DIRECTORIES(${IVP_LIBRARY_DIRS})

#=============================================================================
# Specify where to find Curses
#=============================================================================

find_package(Curses REQUIRED)

# Linux and Apple Libraries
SET(SYSTEM_LIBS
    m
    pthread )

#=============================================================================
# Specify Compiler Flags
#=============================================================================


#---------------------------------------------
# Linux and Apple Compiler Flags
#---------------------------------------------
# Force -fPIC because gcc complains when we don't use it with x86_64 code.
# Note sure why: -fPIC should only be needed for shared objects, and
# AFAIK, CMake gets that right when building shared objects. -CJC
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -g -std=c++17")
SET_PROPERTY(TARGET ${EXE} PROPERTY CXX_STANDARD 17)
IF(CMAKE_COMPILER_IS_GNUCXX)
  # Flags for the GNU C++ Compiler
  SET( WALL_ON OFF CACHE BOOL
    "tell me about all compiler warnings (-Wall) ")
  IF(WALL_ON)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
  ENDIF( WALL_ON)
ELSE(CMAKE_COMPILER_IS_GNUCXX)

ENDIF(CMAKE_COMPILER_IS_GNUCXX)


#=============================================================================
# Add Subdirectories
#=============================================================================
ADD_SUBDIRECTORY( src )
