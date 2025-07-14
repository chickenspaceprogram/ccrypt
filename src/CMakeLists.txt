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

check_symbol_exists("BCryptGenRandom" "Bcrypt.h;Windows.h" HAVE_BCRYPT)
if (HAVE_BCRYPTGENRANDOM)
	target_compile_definitions(ccrypt_rng PUBLIC CCRYPT_HAVE_BCRYPT)
endif()


