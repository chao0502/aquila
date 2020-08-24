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
#include <stdint.h>
#include <string.h>
#include <cfenv>
#include <cmath>

char* decode(uint32_t inst);

int main(){
	uint32_t ins = 0x00440503;
	char* a = decode(ins);
	printf("String:%s\n",a);

	/*char a2[100];
	int a3 = 123123;
	sprintf(a2,"%d",a3);
	printf("A2:%c %c %c\n",a2[0],a2[1],a2[2]);*/
}

char* decode(uint32_t inst){

	static void *opcodeLabels[] = { &&l0, &&l1, &&l2, &&l3, &&l4, &&l5,
				  &&l6, &&l7, &&l8, &&l9, &&l10, &&l11,
				  &&l12, &&l13, &&l14, &&l15, &&l16, &&l17,
				  &&l18, &&l19, &&l20, &&l21, &&l22, &&l23,
				  &&l24, &&l25, &&l26, &&l27, &&l28, &&l29,
				  &&l30, &&l31 };
	char* tem;
	tem = (char*)malloc(10);
	strcpy(tem,"456\n");
	bool quad3 = (inst & 0x3) == 0x3;
	if(quad3){
    	unsigned opcode = (inst & 0x7f) >> 2;  // Upper 5 bits of opcode.
		goto *opcodeLabels[opcode];

    l0:  // 00000   I-form
    {
		int funct3 = (inst >> 12) & 0x7; 
		int rd = (inst >> 6) & 0x1f;
		int rs1 = (inst >> 15) & 0x1f;
		int imme = (inst >> 20) & 0xfff;
		char* op_c = (char*)malloc(5);
		char* rd_c = (char*)malloc(3);
		char* rs1_c = (char*)malloc(3);
		char* imme_c = (char*)malloc(13);
		switch (funct3){
			case 0:  strcpy(op_c,"lb "); break;
			case 1:  strcpy(op_c,"lh "); break;
			case 2:  strcpy(op_c,"lw "); break;
			//case 3:  return instTable_.getEntry(InstId::ld);
			case 4:  strcpy(op_c,"lbu "); break;
			case 5:  strcpy(op_c,"lhu "); break;
			//case 6:  return instTable_.getEntry(InstId::lwu);
			default: printf("illegal\n");
		}
		sprintf(rd_c,"r%d",rd);
		sprintf(rs1_c,"r%d",rs1);
		sprintf(imme_c,"%d",imme);
		strcat(op_c,rd_c);
		strcat(op_c," ");
		strcat(op_c,imme_c);
		strcat(op_c,"(");
		strcat(op_c,rs1_c);
		strcat(op_c,")");
		return op_c;
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
		return tem;
    l3: // 00011  I-form
    {
		int funct3 = (inst >> 12) & 0x7;
		int rd = (inst >> 6) & 0x1f;
		int rs1 = (inst >> 15) & 0x1f;
		char* op_c = (char*)malloc(10);
		if(rd == 0 && rs1 == 0){
			if(funct3 == 0)
				strcpy(op_c,"fence");
			else if(funct3 == 1)
				strcpy(op_c,"fencei");
		}
		return op_c;
    }
      	printf("illegal\n");
		return tem;
    l4:  // 00100  I-form
    {
		int funct3 = (inst >> 12) & 0x7;
		int rd = (inst >> 6) & 0x1f;
		int rs1 = (inst >> 15) & 0x1f;
		int imme = (inst >> 20) & 0xfff;
		char* op_c = (char*)malloc(7);
		char* rd_c = (char*)malloc(3);
		char* rs1_c = (char*)malloc(3);
		char* imme_c = (char*)malloc(13);
		if(funct3 == 0) strcpy(op_c,"addi ");
		else if (funct3 == 1) strcpy(op_c,"slli ");
		else if (funct3 == 2) strcpy(op_c,"slti ");
		else if (funct3 == 3) strcpy(op_c,"sltiu ");
		else if (funct3 == 4) strcpy(op_c,"xori ");
		else if (funct3 == 5){
			int top5 = (inst >> 27) & 0x1f;
	    	if (top5 == 0) strcpy(op_c,"srli ");
	    	if (top5 == 0x8) strcpy(op_c,"srai ");
	  	}
		else if (funct3 == 6) strcpy(op_c,"ori ");
		else if (funct3 == 7) strcpy(op_c,"andi ");

		sprintf(rd_c,"r%d",rd);
		sprintf(rs1_c,"r%d",rs1);
		sprintf(imme_c,"%d",imme);
		strcat(op_c,rd_c);
		strcat(op_c," ");
		strcat(op_c,rs1_c);
		strcat(op_c," ");
		strcat(op_c,imme_c);
		return op_c;
    }
      	printf("illegal\n");
		return tem;

    l5:  // 00101   U-form
    {	
		char* op_c = (char*)malloc(7);
		strcpy(op_c,"auipc");
		return op_c;
    }
		printf("illegal\n");
		return tem;

    l6:  // 00110  I-form
    l8:  // 01000  S-form
    {
		int funct3 = (inst >> 12) & 0x7;
		int rd = (inst >> 6) & 0x1f;
		int rs1 = (inst >> 15) & 0x1f;
		int imme = (inst >> 20) & 0xfff;
		char* op_c = (char*)malloc(5);
		char* rd_c = (char*)malloc(3);
		char* rs1_c = (char*)malloc(3);
		char* imme_c = (char*)malloc(13);
		if (funct3 == 0) strcpy(op_c,"sb ");
		if (funct3 == 1) strcpy(op_c,"sh ");
		if (funct3 == 2) strcpy(op_c,"sw ");
		sprintf(rd_c,"r%d",rd);
		sprintf(rs1_c,"r%d",rs1);
		sprintf(imme_c,"%d",imme);
		strcat(op_c,rd_c);
		strcat(op_c," ");
		strcat(op_c,imme_c);
		strcat(op_c,"(");
		strcat(op_c,rs1_c);
		strcat(op_c,")\n");
		return op_c;
    }
      	printf("illegal\n");
		return tem;
    l11:  // 01011  R-form atomics
    {
		int funct3 = (inst >> 12) & 0x7;
		int top5 = (inst >> 27) & 0x1f;
		char* op_c = (char*)malloc(12);
        if (funct3 == 2){
            if (top5 == 0)    strcpy(op_c,"amoadd_w ");
            else if (top5 == 1)    strcpy(op_c,"amoswap_w ");
            else if (top5 == 2)    strcpy(op_c,"lr_w ");
            else if (top5 == 3)    strcpy(op_c,"sc_w ");
            else if (top5 == 4)    strcpy(op_c,"amoxor_w ");
            else if (top5 == 8)    strcpy(op_c,"amoor_w ");
            else if (top5 == 0x0c) strcpy(op_c,"amoand_w ");
            else if (top5 == 0x10) strcpy(op_c,"amomin_w ");
            else if (top5 == 0x14) strcpy(op_c,"amomax_w ");
            else if (top5 == 0x18) strcpy(op_c,"amominu_w ");
            else if (top5 == 0x1c) strcpy(op_c,"amomaxu_w ");
        }
		return op_c;
    }
    	printf("illegal\n");
		return tem;
    l12:  // 01100  R-form
    {
		int funct3 = (inst >> 12) & 0x7;
		int funct7 = (inst >> 25) & 0x7f;
		int top5 = (inst >> 27) & 0x1f;
		int rd = (inst >> 6) & 0x1f;
		int rs1 = (inst >> 15) & 0x1f;
		int rs2 = (inst >> 20) & 0x1f;
		char* op_c = (char*)malloc(5);
		char* rd_c = (char*)malloc(3);
		char* rs1_c = (char*)malloc(3);
		char* rs2_c = (char*)malloc(3);
		if (funct7 == 0){
			if      (funct3 == 0) strcpy(op_c,"add ");
			else if (funct3 == 1) strcpy(op_c,"sll ");
			else if (funct3 == 2) strcpy(op_c,"slt ");
			else if (funct3 == 3) strcpy(op_c,"sltu ");
			else if (funct3 == 4) strcpy(op_c,"xor_ ");
			else if (funct3 == 5) strcpy(op_c,"srl ");
			else if (funct3 == 6) strcpy(op_c,"or_ ");
			else if (funct3 == 7) strcpy(op_c,"and_ ");
		}
		else if (funct7 == 1){
			if (funct3 == 0) strcpy(op_c,"mul ");
			else if (funct3 == 1) strcpy(op_c,"mulh ");
			else if (funct3 == 2) strcpy(op_c,"mulhsu ");
			else if (funct3 == 3) strcpy(op_c,"mulhu ");
			else if (funct3 == 4) strcpy(op_c,"div ");
			else if (funct3 == 5) strcpy(op_c,"divu ");
			else if (funct3 == 6) strcpy(op_c,"rem ");
			else if (funct3 == 7) strcpy(op_c,"remu ");
		}
		else if (funct7 == 0x20){
			if      (funct3 == 0) strcpy(op_c,"sub ");
			else if (funct3 == 5) strcpy(op_c,"sra ");
		}

		sprintf(rd_c,"r%d",rd);
		sprintf(rs1_c,"r%d",rs1);
		sprintf(rs2_c,"r%d",rs2);
		strcat(op_c,rd_c);
		strcat(op_c," ");
		strcat(op_c,rs1_c);
		strcat(op_c," ");
		strcat(op_c,rs2_c);
		return op_c;
	}
		printf("illegal\n");
		return tem;
    l13:  // 01101  U-form
    {
		char* op_c = (char*)malloc(10);
		strcpy(op_c,"lui ");
		return op_c;
    }
    l14: // 01110  R-Form
		printf("illegal\n");
		return tem;
    l24: // 11000   B-form
	{
		int funct3 = (inst >> 12) & 0x7;
		int rs1 = (inst >> 15) & 0x1f;
		int rs2 = (inst >> 20) & 0x1f;
		char* op_c = (char*)malloc(10);
		char* rs1_c = (char*)malloc(3);
		char* rs2_c = (char*)malloc(3);
		if      (funct3 == 0)  strcpy(op_c,"beq ");
		else if (funct3 == 1)  strcpy(op_c,"bne ");
		else if (funct3 == 4)  strcpy(op_c,"blt ");
		else if (funct3 == 5)  strcpy(op_c,"bge ");
		else if (funct3 == 6)  strcpy(op_c,"bltu ");
		else if (funct3 == 7)  strcpy(op_c,"bgeu ");

		sprintf(rs1_c,"r%d",rs1);
		sprintf(rs2_c,"r%d",rs2);
		strcat(op_c,rs1_c);
		strcat(op_c," ");
		strcat(op_c,rs2_c);
		return op_c;
    }
      	printf("illegal\n");
		return tem;
    l25:  // 11001  I-form
    {
		char* op_c = (char*)malloc(10);
	  	strcpy(op_c,"jalr ");
		return op_c;
    }
    	printf("illegal\n");
		return tem;
    l27:  // 11011  J-form
    {
		char* op_c = (char*)malloc(10);
		strcpy(op_c,"jal ");
		return op_c;
    }
    l28:  // 11100  I-form
    {
		int funct3 = (inst >> 12) & 0x7;
		int funct7 = (inst >> 25) & 0x7f;
		int imme = (inst >> 20) & 0xfff;
		char* op_c = (char*)malloc(10);
		switch(funct3){
			case 0:{
				if (funct7 == 0){
					if (imme == 0)
						strcpy(op_c,"ecall ");
					else if (imme == 1)
						strcpy(op_c,"ebreak ");
				}
			}
			case 1:  strcpy(op_c,"csrrw ");
			case 2:  strcpy(op_c,"csrrs ");
			case 3:  strcpy(op_c,"csrrc ");
			case 5:  strcpy(op_c,"csrrwi ");
			case 6:  strcpy(op_c,"csrrsi ");
			case 7:  strcpy(op_c,"csrrci ");
			default: strcpy(op_c,"illegal ");
		}
		return op_c;
    }
		printf("illegal\n");
		return tem;
	}
}
