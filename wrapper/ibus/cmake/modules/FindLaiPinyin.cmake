# - Try to find laipinyin
# Once done, this will define
#
#  laipinyin_FOUND - system has iBus
#  laipinyin_INCLUDE_DIRS - the iBus include directories
#  laipinyin_LIBRARIES - link these to use iBus

include(LibFindMacros)

# Dependencies

# Use pkg-config to get hints about paths
libfind_pkg_check_modules(laipinyin_PKGCONF laipinyin-2.0)

# Include dir
find_path(laipinyin_INCLUDE_DIR
  NAMES laipinyin.h
  PATHS ${laipinyin_PKGCONF_INCLUDE_DIRS}
)

# Finally the library itself
find_library(laipinyin_LIBRARY
  NAMES laipinyin
  PATHS ${laipinyin_PKGCONF_LIBRARY_DIRS}
)

# Set the include dir variables and the libraries and let libfind_process do the
# rest.
# NOTE: Singular variables for this library, plural for libraries this this lib
# depends on.
set(laipinyin_PROCESS_INCLUDES laipinyin_INCLUDE_DIR)
set(laipinyin_PROCESS_LIBS laipinyin_LIBRARY)
libfind_process(laipinyin)

# -*- indent-tabs-mode: nil -*- vim:et:ts=4
