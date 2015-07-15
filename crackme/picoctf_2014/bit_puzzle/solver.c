#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>

// The regexp is "^[a-z_]{32}$"

/*
  We know from the previous challenges that the flag is likely to composed of characters within the charset [a-z_].
  We know from the reverse enginnering that the flag is 32 bytes long (8 DWORD).
  The alphabet is composed of 26 letters.
  Each character must be between 0x61 ('a') and 0x7A ('z') or equals to 0x5F ('_').
  Each dword can have 531441 values (27 ^ 4);
  So for a dump brute force we would have to try 531441 ^ 8 (or 27 ^ 32) possibilites (that is 6362685441135942358474828762538534230890216321)
*/

#define MAX_DWORD_SIZE 531441

#define INIT_ALL_VAL(i, j, k, l) ( (uint32_t)(INIT_VAL(i) << 24 | INIT_VAL(j) << 16 | INIT_VAL(k) << 8 | INIT_VAL(l)) )
#define INIT_VAL(x) (x < 26 ? x + 'a' : '_')

typedef struct {
	uint32_t array[MAX_DWORD_SIZE];
	size_t size;
} dword_array_t;

bool dword_1_match(uint32_t value) {
	return (true);
}

bool dword_2_match(uint32_t value) {
	/* if (dword_1 + dword_2 == 0x0D5D3DDC) */
	return (value >= 0x5B000000 && value < 0x75000000);
}

bool dword_3_match(uint32_t value) {
	
	return (value >= 0x4C000000 && value < 0x66000000);
}

bool dword_4_match(uint32_t value) {
	
	return (true);
}
bool dword_5_match(uint32_t value) {
	
	return (true);
}
bool dword_6_match(uint32_t value) {
	
	return (value & 0x70000000 == 0x70000000);
}
bool dword_7_match(uint32_t value) {
	// dwprd_7 > dword_6
	return (true);
}

bool dword_8_match(uint32_t value) {
	
	return (true);
}


void init_dword(dword_array_t *dword_n, bool (*filter_match)(uint32_t value))
{
	int32_t i, j, k, l, cpt;
	
	dword_n->size = 0;
	for (i = 0; i < 27; i++) {
		for (j = 0; j < 27; j++) {
			for (k = 0; k < 27; k++) {
				for (l = 0; l < 27; l++) {
					uint32_t value = (uint32_t) INIT_ALL_VAL(i, j, k, l);
					if (filter_match(value)) {
						dword_n->array[cpt] = value;
						dword_n->size++;
					}
				}
			}
		}
	}
	printf("initialized %d values\n", dword_n->size);
}

int main(int argc, char *argv[])
{
	uint32_t i, j;
	
	dword_array_t dword_1;
	uint32_t dword_2, dword_3;
	init_dword(&dword_1, dword_1_match);
	

	for (i = 0; i < dword_1.size; i++) {
		
		dword_2 = 0xd5d3dddc - dword_1.array[i];
		if (dword_2 >= 0x5B000000 && dword_2 < 0x75000000) {
			dword_3 = 0xc0dcdfce - dword_2;
			if (dword_3 >= 0x4C000000 && dword_3 < 0x66000000) {
				if ( (((dword_1.array[i] * 3) & 0xFFFFFFFF) + ((dword_2 * 5) & 0xFFFFFFFF)) & 0xFFFFFFFF == 0x404a7666) {
					printf("not bad 3\n");
				}
			}
		}
		
	}
	return (0);
}
