# VM Project

## Specs
- 8-bit word size
- 16-bit instruction size
- 256 bytes of memory
- 16 x 8-bit registers

## ISA
```
-> NOP : 0x xx
-> LDI : 1r ii
-> LDR : 2r aa
-> STR : 3r aa
-> ADD : 4r ii
-> SUB : 5r ii
-> JMP : 6x ii
-> JZ  : 7x ii
-> JC  : 8x ii
-> PSH : 9r xx
-> CAL : 9x 01
-> PLL : Ar xx
-> RET : Ax 01
-> OUT : Br xx
-> AND : Cr ii
-> OR  : Dr ii
-> NOT : Er xx
-> HLT : Fx xx
```