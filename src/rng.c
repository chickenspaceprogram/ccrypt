#include "rng.h"

int crypt_prng_rand_bytes(uint8_t *dest, size_t nbytes, struct ccrypt_prng *prng)
{
	return prng->gen(dest, nbytes, prng->ctx);
}

#ifdef CCRYPT_HAVE_GETENTROPY
#include <unistd.h>

static int getentropy_wrapper(uint8_t *dest, size_t nbytes, void *ctx)
{
	return getentropy(dest, nbytes);
}

// returns a ccrypt_prng that uses the getentropy generator
struct ccrypt_prng ccrypt_prng_getentropy(void)
{
	return (struct ccrypt_prng){
		.gen = getentropy_wrapper,
		.ctx = NULL,
	};
}

#endif

#ifdef CCRYPT_HAVE_ARC4RANDOM
#include <stdlib.h>

static int arc4random_wrapper(uint8_t *dest, size_t nbytes, void *ctx)
{
	arc4random_buf(dest, nbytes);
	return 0;
}

// returns a ccrypt_prng that uses the arc4random generator
struct ccrypt_prng ccrypt_prng_arc4random(void) {
	return (struct ccrypt_prng){
		.gen = arc4random_wrapper,
		.ctx = NULL,
	};
}

#endif

#ifdef CCRYPT_HAVE_BCRYPT
// returns a ccrypt_prng that uses the BCryptGenRandom generator
#include <bcrypt.h>

static int bcrypt_wrapper(uint8_t *dest, size_t nbytes, void *ctx)
{
	NTSTATUS result = BCryptGenRandom(NULL, dest, nbytes, BCRYPT_USE_SYSTEM_PREFERRED_RNG);
	if (result != STATUS_SUCCESS)
		return -1;
	return 0;
}

struct ccrypt_prng ccrypt_prng_bcrypt(void) {
	return (struct ccrypt_prng){
		.gen = bcrypt_wrapper,
		.ctx = NULL,
	};
}

#endif

