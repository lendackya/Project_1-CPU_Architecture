#include <stdio.h>
#include "P1CPU.h"

void print_Rtype_instruction(R_type_instruction instruxn) {
	printf("0x%0.1X|", instruxn.opcode);
	printf("%0.1X|", instruxn.rs_addr);
	printf("%0.1X|", instruxn.rt_addr);
	printf("%0.1X|", instruxn.rd_addr);
	printf("%0.1X|", instruxn.shamt);
	printf("%0.1X", instruxn.func);
	printf("\n");
}

void print_Itype_instruction(I_type_instruction instruxn) {
	printf("0x%0.1X|", instruxn.opcode);
	printf("%0.1X|", instruxn.rs_addr);
	printf("%0.1X|", instruxn.rt_addr);
	printf("%0.2X", instruxn.imm);
	printf("\n");
}

int main(int argc, char *argv[]) {
	printf("test output\n");
	
	reg32_addr rs_addr;
	reg32 rs_reg;
	regfile32x32 regfile;
	
	rs_addr = 0x1;
	rs_reg = 0x0001;
	regfile[0] = 0x0000;
	
	R_type_instruction myRinstruxn;
	myRinstruxn.opcode = (char) 0x0;
	myRinstruxn.rs_addr = 0x0;
	myRinstruxn.rt_addr = 0x0;
	myRinstruxn.rd_addr = 0x1;
	myRinstruxn.shamt = (char) 0x0;
	myRinstruxn.func = (char) 0x0;
	
	I_type_instruction myIinstruxn;
	myIinstruxn.opcode = (char) 0x1;
	myIinstruxn.rs_addr = 0x4;
	myIinstruxn.rt_addr = 0x5;
	myIinstruxn.imm = (__uint16_t) 0x0A;
	
	printf("value of rs_addr: %i\n", (int) rs_addr);
	printf("value of rs_reg: 0x%x\n", rs_reg);
	printf("value of regfile[0]: 0x%0.4x\n", regfile[0]);
	
	print_Rtype_instruction(myRinstruxn);
	print_Itype_instruction(myIinstruxn);
	
}

