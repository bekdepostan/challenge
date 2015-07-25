# Actually the hint section for this challenge says: 
# USE CONSTRAIT SOLVER
# So while my poor CPU was burning compiling z3, I wrote this little python script
# This nice tutorial helped me for playing with z3. 
# http://cpl0.net/~argp/papers/z3py-guide.pdf

import sys
from z3 import Solver, BitVec

def print_dword(dword):
	sys.stdout.write(chr(dword & 0xFF) + chr((dword >> 8) & 0xFF) + chr((dword >> 16) & 0xFF) + chr((dword >> 24) & 0xFF))

dword_1 = BitVec('dword_1', 32)
dword_2 = BitVec('dword_2', 32)
dword_3 = BitVec('dword_3', 32)
dword_4 = BitVec('dword_4', 32)
dword_5 = BitVec('dword_5', 32)
dword_6 = BitVec('dword_6', 32)
dword_7 = BitVec('dword_7', 32)
dword_8 = BitVec('dword_8', 32)

s = Solver()

s.add(dword_3 + dword_2 == 0x0C0DCDFCE)
s.add(dword_3 + dword_2 == 0x0C0DCDFCE)
s.add(dword_2 + dword_1 == 0x0D5D3DDDC)
s.add((dword_2 * 5) + (dword_1 * 3) == 0x404A7666)
s.add((dword_4 ^ dword_1) == 0x18030607)
s.add((dword_1 & dword_4) == 0x666C6970)
s.add(dword_2 * dword_5 == 0xB180902B)
s.add(dword_5 * dword_3 == 0x3E436B5F)
s.add(dword_5 + (dword_6 * 2) == 0x5C483831)
s.add((dword_6 & 0x70000000) == 0x70000000)
s.add(dword_6 / dword_7 == 1)
s.add(dword_6 % dword_7 == 0x0E000CEC)
s.add((dword_5 * 3) + (dword_8 * 2) == 0x3726EB17)
s.add((dword_8 * 7) + (dword_3 * 4) == 0x8B0B922D)
s.add((dword_8 * 3) + dword_4 == 0xB9CF9C91)

s.check()
m = s.model() 

dword_map = {}

for d in m.decls():
	dword_map[d.name()] = m[d].as_signed_long()

for key in sorted(dword_map):
	print_dword(dword_map[key])

print ""
