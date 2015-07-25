#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>

#define DWORD_6_SIZE 216513

#define INIT_ALL_VAL(i, j, k, l) ( INIT_VAL(i) | INIT_VAL(j) << 8 | INIT_VAL(k) << 16 | INIT_VAL(l) << 24 )
#define INIT_VAL(x) ((x) < 26 ? (x) + 'a' : '_')

// ((dword_6 & 0x70000000) == 0x70000000)
void init_dword_6_array(uint32_t array[DWORD_6_SIZE])
{
    uint32_t i, j, k, l;
    uint32_t cpt = 0;
    
    // Lower byte from the dword (first character from the dword string)
    for (i = 0; i < 27; i++) {
        for (j = 0; j < 27; j++) {
            for (k = 0; k < 27; k++) {
                // Higher byte from the dword (last character byte from the dword string)
                // Iterate only 11 times
                for (l = 'p' - 'a'; l < 'z' - 'a'; l++) {
                    uint32_t value = INIT_ALL_VAL(i, j, k, l);
                    array[cpt++] = value;
                }
            }
        }
    }
}

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv;

    uint32_t dword_6_array[DWORD_6_SIZE];
    init_dword_6_array(dword_6_array);

    uint32_t i;
    for (i = 0; i < DWORD_6_SIZE; i++) {

        // (dword_6 % dword_7 == 0x0E000CEC)
        uint32_t dword_7 = dword_6_array[i] - 0x0E000CEC;
      
       
       // (dword_6 / dword_7 == 1)
       // (dword_6 % dword_7 == 0x0E000CEC)
        if (dword_6_array[i] / dword_7 == 1 && dword_6_array[i] % dword_7 == 0x0E000CEC) {

            // (dword_5 + (dword_6 * 2) == 0x5C483831)
            uint32_t dword_5 = 0x5C483831 - (2 * dword_6_array[i]);

            
            // ((dword_5 * 3) + (dword_8 * 2) == 0x3726EB17)
            int32_t dword_8 = (0x3726EB17 - (dword_5 * 3)) / 2;
            
            // (dword_8 * 3) + dword_4 == 0xB9CF9C91)
            uint32_t dword_4 = 0xB9CF9C91 - (dword_8 * 3);

            // ((dword_4 ^ dword_1) == 0x18030607)
            uint32_t dword_1 = dword_4 ^ 0x18030607;

            // ((dword_1 & dword_4) == 0x666C6970)
            if ((dword_1 & dword_4) == 0x666C6970) {

                // (dword_2 + dword_1 = 0x0D5D3DDDC)
                uint32_t dword_2 = 0x0D5D3DDDC - dword_1;
                
                // (dword_2 * 5) + (dword_1 * 3) = 0x404A7666
                if ((dword_2 * 5) + (dword_1 * 3) == 0x404A7666) {
                    
                    // (dword_2 * dword_5 == 0xB180902B)
                    if (dword_2 * dword_5 == 0xB180902B) {

                        // (dword_3 + dword_2 = 0x0C0DCDFCE)
                        uint32_t dword_3 = 0x0C0DCDFCE - dword_2;
                         
                        // (dword_5 * dword_3 == 0x3E436B5F)
                        if (dword_5 * dword_3 == 0x3E436B5F) {
                        
                            // ((dword_8 * 7) + (dword_3 * 4) == 0x8B0B922D)
                            if ((dword_8 * 7) + (dword_3 * 4) == 0x8B0B922D) {
                                printf("The flag is: %.*s%.*s%.*s%.*s%.*s%.*s%.*s%.*s\n", 
                                       4, (char *)&dword_1, 4, (char *)&dword_2,
                                       4, (char *)&dword_3, 4, (char *)&dword_4,
                                       4, (char *)&dword_5, 4, (char *)&dword_6_array[i],
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
