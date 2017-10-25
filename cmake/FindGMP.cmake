# - Try to find GMP headers and libraries
#
# Usage of this module as follows:
#
#     find_package(GMP)
#
# Variables used by this module, they can change the default behaviour and need
# to be set before calling find_package:
#
#  GMP_ROOT_DIR              Set this variable to the root installation of
#                            GMP if the module has problems finding the
#                            proper installation path.
#
# Variables defined by this module:
#
#  GMP_FOUND                        System has GMP libraries and headers
#  GMP_LIBRARY                      The GMP library
#  GMP_INCLUDE_DIR                  The location of GMP headers

find_path(GMP_ROOT_DIR
    NAMES include/gmp.h
)

find_library(GMP_LIBRARY
    NAMES gmp
    HINTS ${GMP_ROOT_DIR}/lib
)

find_path(GMP_INCLUDE_DIR
    NAMES gmp.h
		HINTS ${GMP_ROOT_DIR}/include
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GMP DEFAULT_MSG
    GMP_LIBRARY
    GMP_INCLUDE_DIR
)

mark_as_advanced(
    GMP_ROOT_DIR
    GMP_LIBRARY
    GMP_INCLUDE_DIR
)
