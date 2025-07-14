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
#include <WiNdOwS.h>
#include <stdbool.h>

// this is a hack, because including Ntdef.h (as Win32 docs say to do)
// results in a bunch of structs and such being included twice
//
// we also need Windows.h here for BCryptGenRandom, there's no avoiding it
//
// (Ntdef.h provides an NT_SUCCESS macro which does the same thing as nt_success here)
static inline bool nt_success(NTSTATUS ntstatus) {
	return ntstatus <= 0x7FFFFFFF;
}

static int bcrypt_wrapper(uint8_t *dest, size_t nbytes, void *ctx)
{
	NTSTATUS result = BCryptGenRandom(NULL, dest, nbytes, BCRYPT_USE_SYSTEM_PREFERRED_RNG);
	if (!nt_success(result))
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

