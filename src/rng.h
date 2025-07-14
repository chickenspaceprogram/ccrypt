#pragma once
#include <stddef.h>
#include <stdint.h>

struct ccrypt_prng {
	int (*gen)(uint8_t *dest, size_t nbytes, void *ctx);
	void *ctx;
};
int ccrypt_prng_rand_bytes(uint8_t *dest, size_t nbytes, struct ccrypt_prng *prng);

#ifdef CCRYPT_HAVE_GETENTROPY
// returns a ccrypt_prng that uses the getentropy generator
struct ccrypt_prng ccrypt_prng_getentropy(void);
#endif

#ifdef CCRYPT_HAVE_ARC4RANDOM
// returns a ccrypt_prng that uses the arc4random generator
struct ccrypt_prng ccrypt_prng_arc4random(void);
#endif

#ifdef CCRYPT_HAVE_BCRYPT
// returns a ccrypt_prng that uses the BCryptGenRandom generator
struct ccrypt_prng ccrypt_prng_bcrypt(void);
#endif


