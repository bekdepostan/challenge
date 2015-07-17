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

#define INIT_ALL_VAL(i, j, k, l) ( (INIT_VAL(l) << 24 | INIT_VAL(k) << 16 | INIT_VAL(j) << 8 | INIT_VAL(i)) )
#define INIT_VAL(x) (x < 26 ? x + 'a' : '_')

typedef struct {
	uint32_t array[MAX_DWORD_SIZE];
	size_t size;
} dword_array_t;

bool dword_6_match(uint32_t value) {

	return ((value & 0x70000000) == 0x70000000);
}

void init_dword(dword_array_t *dword_n, bool (*filter_match)(uint32_t value))
{
	uint32_t i, j, k, l;

	dword_n->size = 0;
	for (i = 0; i < 27; i++) {
		for (j = 0; j < 27; j++) {
			for (k = 0; k < 27; k++) {
				for (l = 0; l < 27; l++) {
					uint32_t value = INIT_ALL_VAL(i, j, k, l);
					if (filter_match(value)) {
						dword_n->array[dword_n->size] = value;
						dword_n->size++;
					}
				}
			}
		}
	}
	printf("initialized %ld values\n", dword_n->size);
}

int main(int argc, char *argv[])
{

	dword_array_t dword_6;
	init_dword(&dword_6, dword_6_match);

	// solving_equations_is_lots_of_fun
	char *solv_1 = "solv";
	char *solv_2 = "ing_";
	char *solv_3 = "equa";
	char *solv_4 = "tion";
	char *solv_5 = "s_is";
	char *solv_6 = "_lot";
	char *solv_7 = "s_of";
	char *solv_8 = "_fun";

	uint32_t i;

	for (i = 0; i < dword_6.size; i++) {

		uint32_t dword_7 = dword_6.array[i] - 0x0E000CEC;

		if (dword_6.array[i] / dword_7 == 1 && dword_6.array[i] % dword_7 == 0x0E000CEC) {

			//dword_5 + dword_6 * 2 == 0x5C483831
			uint32_t dword_5 = 0x5C483831 - (2 * dword_6.array[i]);

			int32_t dword_8 = (0x3726EB17 - (dword_5 * 3)) / 2;

			// (dword_8 * 3) + dword_4 == 0xB9CF9C91)
			uint32_t dword_4 = 0xB9CF9C91 - (dword_8 * 3);

			// dword_4 ^ dword_1 == 0x18030607
			uint32_t dword_1 = dword_4 ^ 0x18030607;

			if ((dword_1 & dword_4) == 0x666C6970) {

				uint32_t dword_2 = 0x0D5D3DDDC - dword_1;
				
				if ((dword_2 * 5) + (dword_1 * 3) == 0x404A7666) {
					
					if (dword_2 * dword_5 == 0xb180902b) {

						//dword_2 + dword_3 == 0x0C0DCDFCE
						uint32_t dword_3 = 0x0C0DCDFCE - dword_2;
						
						if (dword_3 * dword_5 == 0x3E436B5F) {
						
							if ((dword_8 * 7) + (dword_3 * 4) == 0x8b0b922d) {
								printf("flag is: %.*s%.*s%.*s%.*s%.*s%.*s%.*s%.*s", 
									   4, (char *)&dword_1, 4, (char *)&dword_2,
									   4, (char *)&dword_3, 4, (char *)&dword_4,
									   4, (char *)&dword_5, 4, (char *)&dword_6.array[i],
									   4, (char *)&dword_7, 4, (char *)&dword_8);
								return(0);
							}
						}
					}
				}
			}
		}
	}
	return (0);
}
