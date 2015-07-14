#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

int main(int argc, char *argv)
{
	uint32_t dword_1, dword_2, dword_3, dword_4, dword_5, dword_6, dword_7, dword_8;
	char input_buffer[80];

	puts("Bet you can't solve my puzzle!");
	puts("Give me a string.");
	
	// mov [esp+8], eax              ; where eax = stdin
	// mov dword ptr [esp+4], 50h    ; size = 0x50 = 80
	// mov [esp], ebx                ; esp + 1Ch
	// call fgets
	fgets(input_buffer, 80, stdin);
	size_t len = strlen(input_buffer);
	
	// (gdb) x /x $esp+0x1a+$ecx
	// 0xffffcd60:	0x0a
	input_buffer[len - 1] = '\0';

	len = strlen(input_buffer);

	bool ecx;

	if (len == 32) {
		// First check
		dword_1 = *((uint32_t *)input_buffer + 0);
		dword_2 = *((uint32_t *)input_buffer + 1);
		dword_3 = *((uint32_t *)input_buffer + 2);
		dword_4 = *((uint32_t *)input_buffer + 3);
		dword_5 = *((uint32_t *)input_buffer + 4);
		dword_6 = *((uint32_t *)input_buffer + 5);
		dword_7 = *((uint32_t *)input_buffer + 6);
		dword_8 = *((uint32_t *)input_buffer + 7);

		//ecx = 0
		if (dword_2 + dword_3 == 0x0C0DCDFCE) {
			
			if (dword_2 + dword_1 == 0x0D5D3DDDC) {
				ecx = true;
			}
			else {
				ecx = false;
			}
		}
		// Second check
		if (!((dword_2 + dword_2 * 4) + (dword_1 + dword_1 * 2) == 0x404A7666)) {
			// cmovnz  ecx, 0
			ecx = false;
		}
		// ebx = 0
		if (!(dword_4 ^ dword_1 == 0x18030607)) {
			ecx = false;
		}
		// ebx = 0
		if (!(dword_1 & dword_4 == 0x666C6970)) {
			ecx = false;
		}
		// edx = 0
		if (!(dword_2 * dword_5 == 0x0B180902B)) {
			ecx = false;
		}
		// eax = 0
		if (!(dword_5 * dword_3 == 0x3E436B5F)) {
			ecx = false;
		}
		// eax = 0
		if (!(dword_5 + dword_6 * 2 == 0x5C483831)) {
			ecx = false;
		}
		// eax = 0
		if (!(dword_6 & 0x70000000 == 0x70000000)) {
			ecx = false;
		}
		// eax = 0
		if (!(dword_7 / dword_6 == 1)) {
			ecx = false;
		}
		// eax = 0
		if (!(dword_7 % dword_6 == 0x0E000CEC)) {
			ecx = false;
		}
		// eax = 0
		if (!((dword_5 + dword_5 * 2) + (dword_8 * 2) == 0x3726EB17)) {
			ecx = false;
		}
		// edx = 0
		if (!((0 - dword_8 * 8) + (dword_3 * 4) == 0x8B0B922D)) {
			ecx = false;
		}
		if (!((dword_8 + dword_8 * 2) + dword_4 == 0xB9CF9C91)) {
			ecx = false;
		}
		// edx = 0
		if (ecx) {
			printf("Sorry, %s is not the right string\n", input_buffer);
			return (0);
		}
		else {
			// SUCESS
		}
	}
	else {
		printf("Sorry, %s is not the right string\n", input_buffer);
		return (0);
	}
}
