include(FindPackageHandleStandardArgs)

# credit to:
# https://izzys.casa/2020/12/how-to-find-packages-with-cmake-the-basics/
# for making this a bit easier to figure out


find_library(GMP_LIBRARY NAMES gmp)
find_path(GMP_INCLUDE_DIR NAMES "gmp.h")
find_path(GMPXX_INCLUDE_DIR NAMES "gmpxx.h")


find_package_handle_standard_args(GMP REQUIRED_VARS GMP_LIBRARY GMP_INCLUDE_DIR GMPXX_INCLUDE_DIR)
if (GMP_FOUND AND NOT TARGET GMP::GMP)
	mark_as_advanced(GMP_LIBRARY)
	mark_as_advanced(GMP_PATH)
	add_library(GMP::GMP IMPORTED UNKNOWN)
	set_target_properties(GMP::GMP PROPERTIES IMPORTED_LOCATION ${GMP_LIBRARY})
	target_include_directories(GMP::GMP INTERFACE ${GMP_INCLUDE_DIR} ${GMPXX_INCLUDE_DIR})
endif()


