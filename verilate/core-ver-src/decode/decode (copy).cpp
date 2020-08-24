//
// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright 2018 Western Digital Corporation or its affiliates.
// 
// This program is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation, either version 3 of the License, or (at your option)
// any later version.
// 
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
// more details.
// 
// You should have received a copy of the GNU General Public License along with
// this program. If not, see <https://www.gnu.org/licenses/>.
//

#include <stdio.h>
#include <stdlib.h>
#include <cfenv>
#include <cmath>

int decode2(uint32_t inst){

	static void *opcodeLabels[] = { &&l0, &&l1, &&l2, &&l3, &&l4, &&l5,
				  &&l6, &&l7, &&l8, &&l9, &&l10, &&l11,
				  &&l12, &&l13, &&l14, &&l15, &&l16, &&l17,
				  &&l18, &&l19, &&l20, &&l21, &&l22, &&l23,
				  &&l24, &&l25, &&l26, &&l27, &&l28, &&l29,
				  &&l30, &&l31 };

	bool quad3 = (inst & 0x3) == 0x3;
	if(quad3){
		
    	unsigned opcode = (inst & 0x7f) >> 2;  // Upper 5 bits of opcode.
		goto *opcodeLabels[opcode];

    l0:  // 00000   I-form
    {
		int funct3 = (inst >> 12) & 0x7; 
		switch (funct3){
			case 0:  printf("lb\n");
			case 1:  printf("lh\n");
			case 2:  printf("lw\n");
			//case 3:  return instTable_.getEntry(InstId::ld);
			case 4:  printf("lbu\n");
			case 5:  printf("lhu\n");
			//case 6:  return instTable_.getEntry(InstId::lwu);
			default: printf("illegal\n");
		}
		return 0;
    }
    l1:
    l2:
    l7:
    l9:
    l10:
    l15:
    l16:
    l17:
    l18:
    l19:
    l20:
    l21:
    l22:
    l23:
    l26:
    l29:
    l30:
    l31:
		printf("illegal\n");
		return 0;
    l3: // 00011  I-form
    {
		int funct3 = (inst >> 12) & 0x7;
		int rd = (inst >> 6) & 0x1f;
		int rs1 = (inst >> 15) & 0x1f;
		if(rd == 0 && rs1 == 0){
			if(funct3 == 0)
				printf("fence\n");
			else if(funct3 == 1)
				printf("fencei\n");
		}
    }
      	printf("illegal\n");
		return 0;
    l4:  // 00100  I-form
    {
		int funct3 = (inst >> 12) & 0x7;
		int rd = (inst >> 6) & 0x1f;
		int rs1 = (inst >> 15) & 0x1f;
		int imme = (inst >> 20) & 0xfff;
		if(funct3 == 0) printf("addi\n");
		else if (funct3 == 1) printf("slli\n");
		else if (funct3 == 2) printf("slti\n");
		else if (funct3 == 3) printf("sltiu\n");
		else if (funct3 == 4) printf("xori\n");
		else if (funct3 == 5){
			int top5 = (inst >> 27) & 0x1f;
	    	if (top5 == 0) printf("srli\n");
	    	if (top5 == 0x8) printf("srai\n");
	  	}
		else if (funct3 == 6) printf("ori\n");
		else if (funct3 == 7) printf("andi\n");
      }
      	printf("illegal\n");
		return 0;

    l5:  // 00101   U-form
    {
		printf("auipc\n");
    }
		printf("illegal\n");
		return 0;

    l6:  // 00110  I-form
    l8:  // 01000  S-form
    {
		int funct3 = (inst >> 12) & 0x7;
		int rd = (inst >> 6) & 0x1f;
		int rs1 = (inst >> 15) & 0x1f;
		int imme = (inst >> 20) & 0xfff;

		if (funct3 == 0) printf("sb\n");
		if (funct3 == 1) printf("sh\n");
		if (funct3 == 2) printf("sw\n");
    }
      	printf("illegal\n");
		return 0;
    l11:  // 01011  R-form atomics
    {
		int funct3 = (inst >> 12) & 0x7;
		int top5 = (inst >> 27) & 0x1f;
        if (funct3 == 2){
            if (top5 == 0)    printf("amoadd_w\n");
            else if (top5 == 1)    printf("amoswap_w\n");
            else if (top5 == 2)    printf("lr_w\n");
            else if (top5 == 3)    printf("sc_w\n");
            else if (top5 == 4)    printf("amoxor_w\n");
            else if (top5 == 8)    printf("amoor_w\n");
            else if (top5 == 0x0c) printf("amoand_w\n");
            else if (top5 == 0x10) printf("amomin_w\n");
            else if (top5 == 0x14) printf("amomax_w\n");
            else if (top5 == 0x18) printf("amominu_w\n");
            else if (top5 == 0x1c) printf("amomaxu_w\n");
        }
    }
    	printf("illegal\n");
		return 0;
    l12:  // 01100  R-form
    {
		int funct3 = (inst >> 12) & 0x7;
		int funct7 = (inst >> 25) & 0x7f;
		int top5 = (inst >> 27) & 0x1f;
		if (funct7 == 0){
			if      (funct3 == 0) printf("add\n");
			else if (funct3 == 1) printf("sll\n");
			else if (funct3 == 2) printf("slt\n");
			else if (funct3 == 3) printf("sltu\n");
			else if (funct3 == 4) printf("xor_\n");
			else if (funct3 == 5) printf("srl\n");
			else if (funct3 == 6) printf("or_\n");
			else if (funct3 == 7) printf("and_\n");
		}
		else if (funct7 == 1){
			if (funct3 == 0) printf("mul\n");
			else if (funct3 == 1) printf("mulh\n");
			else if (funct3 == 2) printf("mulhsu\n");
			else if (funct3 == 3) printf("mulhu\n");
			else if (funct3 == 4) printf("div\n");
			else if (funct3 == 5) printf("divu\n");
			else if (funct3 == 6) printf("rem\n");
			else if (funct3 == 7) printf("remu\n");
		}
		else if (funct7 == 0x20){
			if      (funct3 == 0) printf("sub\n");
			else if (funct3 == 5) printf("sra\n");
		}
			printf("illegal\n");
			return 0;
	}
    l13:  // 01101  U-form
    {
		printf("lui\n");
    }
    l14: // 01110  R-Form
		printf("illegal\n");
		return 0;
    l24: // 11000   B-form
	{
		int funct3 = (inst >> 12) & 0x7;
		if      (funct3 == 0)  printf("beq\n");
		else if (funct3 == 1)  printf("bne\n");
		else if (funct3 == 4)  printf("blt\n");
		else if (funct3 == 5)  printf("bge\n");
		else if (funct3 == 6)  printf("bltu\n");
		else if (funct3 == 7)  printf("bgeu\n");
    }
      	printf("illegal\n");
		return 0;
    l25:  // 11001  I-form
    {
		int funct3 = (inst >> 12) & 0x7;
		if (funct3 == 0)
	  		printf("jalr\n");
    }
    	printf("illegal\n");
		return 0;
    l27:  // 11011  J-form
    {
		printf("jal\n");
    }
    l28:  // 11100  I-form
    {
		int funct3 = (inst >> 12) & 0x7;
		int funct7 = (inst >> 25) & 0x7f;
		int imme = (inst >> 20) & 0xfff;
		switch(funct3){
			case 0:{
				if (funct7 == 0){
					if (imme == 0)
						printf("ecall\n");
					else if (imme == 1)
						printf("ebreak\n");
				}
			}
			case 1:  printf("csrrw\n");
			case 2:  printf("csrrs\n");
			case 3:  printf("csrrc\n");
			case 5:  printf("csrrwi\n");
			case 6:  printf("csrrsi\n");
			case 7:  printf("csrrci\n");
			default: printf("illegal\n");
		}
		printf("illegal\n");
		return 0;
    }
	}
}

void decode_ori(uint32_t inst){
  uint32_t op0 = 0, op1 = 0, op2 = 0, op3 = 0;

  InstEntry& entry = decode2(inst, op0, op1, op2, op3);
}

int main(){
	uint32_t ins = 100;
	printf("11\n");
	decode_ori(ins);
	printf("22\n");
}