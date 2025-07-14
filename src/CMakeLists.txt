# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

# SPDX-License-Identifier: MPL-2.0

cmake_minimum_required(VERSION 3.21)

add_library(ccrypt_rng rng.h rng.c)

include(CheckSymbolExists)

check_symbol_exists("getentropy" "unistd.h" HAVE_GETENTROPY)
if (HAVE_GETENTROPY)
	target_compile_definitions(ccrypt_rng PUBLIC CCRYPT_HAVE_GETENTROPY)
endif()

check_symbol_exists("arc4random_buf" "stdlib.h" HAVE_ARC4RANDOM)
if (HAVE_ARC4RANDOM)
	target_compile_definitions(ccrypt_rng PUBLIC CCRYPT_HAVE_ARC4RANDOM)
endif()

if (WIN32)
	set(HAVE_BCRYPT ON) # this is 100% a hack
	message(NOTICE "Found BCrypt!")
	target_compile_definitions(ccrypt_rng PUBLIC CCRYPT_HAVE_BCRYPT)

	# the CI/CD passes without this, but on my windows test VM this is 
	# necessary to avoid linker errors

	target_link_libraries(ccrypt_rng PRIVATE bcrypt)
endif()

