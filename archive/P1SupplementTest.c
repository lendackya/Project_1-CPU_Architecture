#include <stdio.h>
#include "P1Supplement.h"

int main(int argc, char *argv[]) {
	printf("Testing Supplementary Code for Project 1:\n");

	reg_addr aRegAddr = 31;
	register32_t aRegister = 0xABCD;
	regfile32x32_t aRegFile;
	aRegFile[0] = 0x0000;
	instruction_t anInstrxn = (instruction_t) 0xFEDC;

	Rinstr_t myRinstrxn;
	myRinstrxn.opcode = 0x0;
	myRinstrxn.rs_addr = 0x0;
	myRinstrxn.rt_addr = 0x0;
	myRinstrxn.rd_addr = 0x1;
	myRinstrxn.shamt = 0x0;
	myRinstrxn.func = 0x0;

	Iinstr_t myIinstrxn;
	myIinstrxn.opcode = 0x1;
	myIinstrxn.rs_addr = 0x4;
	myIinstrxn.rt_addr = 0x5;
	myIinstrxn.immediate = 0x0A;
	
	Jinstr_t myJinstrxn;
	myJinstrxn.opcode = 0x2;
	myJinstrxn.immediate = 0x0123;

	printf("a register address: %i\n", aRegAddr);
	printf(" register aRegster: 0x%0.4X\n", aRegister);
	printf("   registerFile[0]: 0x%0.4X\n", aRegFile[0]);
	printf("	 anInstrxn: 0x%0.4X\n", anInstrxn);
	printf("	myRinstrxn: ");
	print_Rinstrxn(myRinstrxn);
	printf("	myIinstrxn: ");
	print_Iinstrxn(myIinstrxn);
	printf("	myJinstrxn: ");
	print_Jinstrxn(myJinstrxn);
	
	printf("End testing routine\n");
}
