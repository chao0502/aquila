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

#include <cfenv>
#include <cmath>
#include "instforms.hpp"
#include "DecodedInst.hpp"


using namespace WdRiscv;

InstEntry& decode2(uint32_t inst, uint32_t& op0, uint32_t& op1, uint32_t& op2, uint32_t& op3){
	#pragma GCC diagnostic ignored "-Wpedantic"

	InstTable instTable_;

  static void *opcodeLabels[] = { &&l0, &&l1, &&l2, &&l3, &&l4, &&l5,
				  &&l6, &&l7, &&l8, &&l9, &&l10, &&l11,
				  &&l12, &&l13, &&l14, &&l15, &&l16, &&l17,
				  &&l18, &&l19, &&l20, &&l21, &&l22, &&l23,
				  &&l24, &&l25, &&l26, &&l27, &&l28, &&l29,
				  &&l30, &&l31 };

  op0 = 0; op1 = 0; op2 = 0; op3 = 0;

  bool quad3 = (inst & 0x3) == 0x3;
  if (quad3)
    {
      unsigned opcode = (inst & 0x7f) >> 2;  // Upper 5 bits of opcode.

      goto *opcodeLabels[opcode];


    l0:  // 00000   I-form
      {
	IFormInst iform(inst);
	op0 = iform.fields.rd;
	op1 = iform.fields.rs1;
	op2 = iform.immed(); 
	switch (iform.fields.funct3)
	  {
	  case 0:  return instTable_.getEntry(InstId::lb);
	  case 1:  return instTable_.getEntry(InstId::lh);
	  case 2:  return instTable_.getEntry(InstId::lw);
	  case 3:  return instTable_.getEntry(InstId::ld);
	  case 4:  return instTable_.getEntry(InstId::lbu);
	  case 5:  return instTable_.getEntry(InstId::lhu);
	  case 6:  return instTable_.getEntry(InstId::lwu);
	  default: return instTable_.getEntry(InstId::illegal);
	  }
      }
      return instTable_.getEntry(InstId::illegal);

    l1:
      {
	IFormInst iform(inst);
	op0 = iform.fields.rd;
	op1 = iform.fields.rs1;
	op2 = iform.immed();
	uint32_t f3 = iform.fields.funct3;
	if      (f3 == 2)  return instTable_.getEntry(InstId::flw);
	else if (f3 == 3)  return instTable_.getEntry(InstId::fld);
      }
      return instTable_.getEntry(InstId::illegal);

    l2:
    l7:
      return instTable_.getEntry(InstId::illegal);

    l9:
      {
	// For store instructions: op0 is the stored register.
	SFormInst sform(inst);
	op0 = sform.bits.rs2;
	op1 = sform.bits.rs1;
	op2 = sform.immed();
	unsigned funct3 = sform.bits.funct3;
	if      (funct3 == 2)  return instTable_.getEntry(InstId::fsw);
	else if (funct3 == 3)  return instTable_.getEntry(InstId::fsd);
      }
      return instTable_.getEntry(InstId::illegal);

    l10:
    l15:
      return instTable_.getEntry(InstId::illegal);

    l16:
      {
	RFormInst rform(inst);
	op0 = rform.bits.rd, op1 = rform.bits.rs1, op2 = rform.bits.rs2;
	unsigned funct7 = rform.bits.funct7;
	op3 = funct7 >> 2;
	if ((funct7 & 3) == 0)
	  return instTable_.getEntry(InstId::fmadd_s);
	if ((funct7 & 3) == 1)
	  return instTable_.getEntry(InstId::fmadd_d);
      }
      return instTable_.getEntry(InstId::illegal);

    l17:
      {
	RFormInst rform(inst);
	op0 = rform.bits.rd, op1 = rform.bits.rs1, op2 = rform.bits.rs2;
	unsigned funct7 = rform.bits.funct7;
	op3 = funct7 >> 2;
	if ((funct7 & 3) == 0)
	  return instTable_.getEntry(InstId::fmsub_s);
	if ((funct7 & 3) == 1)
	  return instTable_.getEntry(InstId::fmsub_d);
      }
      return instTable_.getEntry(InstId::illegal);

    l18:
      {
	RFormInst rform(inst);
	op0 = rform.bits.rd, op1 = rform.bits.rs1, op2 = rform.bits.rs2;
	unsigned funct7 = rform.bits.funct7;
	op3 = funct7 >> 2;
	if ((funct7 & 3) == 0)
	  return instTable_.getEntry(InstId::fnmsub_s);
	if ((funct7 & 3) == 1)
	  return instTable_.getEntry(InstId::fnmsub_d);
      }
      return instTable_.getEntry(InstId::illegal);

    l19:
      {
	RFormInst rform(inst);
	op0 = rform.bits.rd, op1 = rform.bits.rs1, op2 = rform.bits.rs2;
	unsigned funct7 = rform.bits.funct7;
	op3 = funct7 >> 2;
	if ((funct7 & 3) == 0)
	  return instTable_.getEntry(InstId::fnmadd_s);
	if ((funct7 & 3) == 1)
	  return instTable_.getEntry(InstId::fnmadd_d);
      }
      return instTable_.getEntry(InstId::illegal);

    l20: // 10100
      //return decodeFp(inst, op0, op1, op2, op3);

    l21:
    l22:
    l23:
    l26:
    l29:
    l30:
    l31:
      return instTable_.getEntry(InstId::illegal);

    l3: // 00011  I-form
      {
	IFormInst iform(inst);
	unsigned funct3 = iform.fields.funct3;
	if (iform.fields.rd == 0 and iform.fields.rs1 == 0)
	  {
	    if (funct3 == 0)
	      {
		if (iform.top4() == 0)
		  {
		    op0 = iform.pred();
		    op1 = iform.succ();
		    return instTable_.getEntry(InstId::fence);
		  }
	      }
	    else if (funct3 == 1)
	      {
		if (iform.uimmed() == 0)
		  return instTable_.getEntry(InstId::fencei);
	      }
	  }
      }
      return instTable_.getEntry(InstId::illegal);

    l4:  // 00100  I-form
      {
	IFormInst iform(inst);
	op0 = iform.fields.rd;
	op1 = iform.fields.rs1;
	op2 = iform.immed();
	unsigned funct3 = iform.fields.funct3;

	if      (funct3 == 0)  return instTable_.getEntry(InstId::addi);
	else if (funct3 == 1)
	  {
	    unsigned top5 = iform.uimmed() >> 7;
	    unsigned amt = iform.uimmed() & 0x7f;
	    if (top5 == 0)
	      {
		op2 = amt;
		return instTable_.getEntry(InstId::slli);
	      }
	    else if (top5 == 4)
	      {
		op2 = amt;
		return instTable_.getEntry(InstId::sloi);
	      }
	    else if (top5 == 5)
	      {
		op2 = amt;
		return instTable_.getEntry(InstId::sbseti);
	      }
	    else if (top5 == 8)
	      {
		if (amt == 0x18)
		  return instTable_.getEntry(InstId::rev8);
		else if (amt == 0x1f)
		  return instTable_.getEntry(InstId::rev);
	      }
	    else if (top5 == 9)
	      {
		op2 = amt;
		return instTable_.getEntry(InstId::sbclri);
	      }
	    else if (top5 == 0x0c)
	      {
		if (amt == 0)
		  return instTable_.getEntry(InstId::clz);
		else if (amt == 1)
		  return instTable_.getEntry(InstId::ctz);
		else if (amt == 2)
		  return instTable_.getEntry(InstId::pcnt);
	      }
	    else if (top5 == 0x0d)
	      {
		op2 = amt;
		return instTable_.getEntry(InstId::sbinvi);
	      }
	  }
	else if (funct3 == 2)  return instTable_.getEntry(InstId::slti);
	else if (funct3 == 3)  return instTable_.getEntry(InstId::sltiu);
	else if (funct3 == 4)  return instTable_.getEntry(InstId::xori);
	else if (funct3 == 5)
	  {
	    unsigned imm = iform.uimmed();  // 12-bit immediate
	    unsigned top5 = imm >> 7;
	    unsigned shamt = imm & 0x7f;    // Shift amount (low 7 bits of imm)
	    op2 = shamt;
	    if (top5 == 0)
	      return instTable_.getEntry(InstId::srli);
	    if (top5 == 4)
	      return instTable_.getEntry(InstId::sroi);
            if (top5 == 5)
              if (shamt == 0x18)
                return instTable_.getEntry(InstId::orc_b);
	    if (top5 == 0x8)
	      return instTable_.getEntry(InstId::srai);
	    if (top5 == 0x9)
	      return instTable_.getEntry(InstId::sbexti);
	    if (top5 == 0xc)
	      return instTable_.getEntry(InstId::rori);
	  }
	else if (funct3 == 6)  return instTable_.getEntry(InstId::ori);
	else if (funct3 == 7)  return instTable_.getEntry(InstId::andi);
      }
      return instTable_.getEntry(InstId::illegal);

    l5:  // 00101   U-form
      {
	UFormInst uform(inst);
	op0 = uform.bits.rd;
	op1 = uform.immed();
	return instTable_.getEntry(InstId::auipc);
      }
      return instTable_.getEntry(InstId::illegal);

    l6:  // 00110  I-form
      {
	IFormInst iform(inst);
	op0 = iform.fields.rd;
	op1 = iform.fields.rs1;
	op2 = iform.immed();
	unsigned funct3 = iform.fields.funct3;
	if (funct3 == 0)
	  return instTable_.getEntry(InstId::addiw);
	else if (funct3 == 1)
	  {
	    if (iform.top7() == 0)
	      {
		op2 = iform.fields2.shamt;
		return instTable_.getEntry(InstId::slliw);
	      }
	  }
	else if (funct3 == 5)
	  {
	    op2 = iform.fields2.shamt;
	    if (iform.top7() == 0)
	      return instTable_.getEntry(InstId::srliw);
	    else if (iform.top7() == 0x20)
	      return instTable_.getEntry(InstId::sraiw);
	  }
      }
      return instTable_.getEntry(InstId::illegal);

    l8:  // 01000  S-form
      {
	// For the store instructions, the stored register is op0, the
	// base-address register is op1 and the offset is op2.
	SFormInst sform(inst);
	op0 = sform.bits.rs2;
	op1 = sform.bits.rs1;
	op2 = sform.immed();
	uint32_t funct3 = sform.bits.funct3;

	if (funct3 == 0) return instTable_.getEntry(InstId::sb);
	if (funct3 == 1) return instTable_.getEntry(InstId::sh);
	if (funct3 == 2) return instTable_.getEntry(InstId::sw);
	//if (funct3 == 3 and isRv64()) return instTable_.getEntry(InstId::sd);
      }
      return instTable_.getEntry(InstId::illegal);

    l11:  // 01011  R-form atomics
      {
        /*if (not isRva())
          return instTable_.getEntry(InstId::illegal);*/

        RFormInst rf(inst);
        uint32_t top5 = rf.top5(), f3 = rf.bits.funct3;
        op0 = rf.bits.rd; op1 = rf.bits.rs1; op2 = rf.bits.rs2;

        if (f3 == 2)
          {
            if (top5 == 0)    return instTable_.getEntry(InstId::amoadd_w);
            if (top5 == 1)    return instTable_.getEntry(InstId::amoswap_w);
            if (top5 == 2)    return instTable_.getEntry(InstId::lr_w);
            if (top5 == 3)    return instTable_.getEntry(InstId::sc_w);
            if (top5 == 4)    return instTable_.getEntry(InstId::amoxor_w);
            if (top5 == 8)    return instTable_.getEntry(InstId::amoor_w);
            if (top5 == 0x0c) return instTable_.getEntry(InstId::amoand_w);
            if (top5 == 0x10) return instTable_.getEntry(InstId::amomin_w);
            if (top5 == 0x14) return instTable_.getEntry(InstId::amomax_w);
            if (top5 == 0x18) return instTable_.getEntry(InstId::amominu_w);
            if (top5 == 0x1c) return instTable_.getEntry(InstId::amomaxu_w);
          }
        else if (f3 == 3)
          {
            //if (not isRv64()) return instTable_.getEntry(InstId::illegal);
            if (top5 == 0)    return instTable_.getEntry(InstId::amoadd_d);
            if (top5 == 1)    return instTable_.getEntry(InstId::amoswap_d);
            if (top5 == 2)    return instTable_.getEntry(InstId::lr_d);
            if (top5 == 3)    return instTable_.getEntry(InstId::sc_d);
            if (top5 == 4)    return instTable_.getEntry(InstId::amoxor_d);
            if (top5 == 8)    return instTable_.getEntry(InstId::amoor_d);
            if (top5 == 0xc)  return instTable_.getEntry(InstId::amoand_d);
            if (top5 == 0x10) return instTable_.getEntry(InstId::amomin_d);
            if (top5 == 0x14) return instTable_.getEntry(InstId::amomax_d);
            if (top5 == 0x18) return instTable_.getEntry(InstId::amominu_d);
            if (top5 == 0x1c) return instTable_.getEntry(InstId::amomaxu_d);
          }
      }
      return instTable_.getEntry(InstId::illegal);

    l12:  // 01100  R-form
      {
	RFormInst rform(inst);
	op0 = rform.bits.rd;
	op1 = rform.bits.rs1;
	op2 = rform.bits.rs2;
	unsigned funct7 = rform.bits.funct7, funct3 = rform.bits.funct3;
	if (funct7 == 0)
	  {
	    if      (funct3 == 0) return instTable_.getEntry(InstId::add);
	    else if (funct3 == 1) return instTable_.getEntry(InstId::sll);
	    else if (funct3 == 2) return instTable_.getEntry(InstId::slt);
	    else if (funct3 == 3) return instTable_.getEntry(InstId::sltu);
	    else if (funct3 == 4) return instTable_.getEntry(InstId::xor_);
	    else if (funct3 == 5) return instTable_.getEntry(InstId::srl);
	    else if (funct3 == 6) return instTable_.getEntry(InstId::or_);
	    else if (funct3 == 7) return instTable_.getEntry(InstId::and_);
	  }
	else if (funct7 == 1)
	  {
	    //if      (not isRvm()) return instTable_.getEntry(InstId::illegal);
		if (funct3 == 0) return instTable_.getEntry(InstId::mul);
	    else if (funct3 == 1) return instTable_.getEntry(InstId::mulh);
	    else if (funct3 == 2) return instTable_.getEntry(InstId::mulhsu);
	    else if (funct3 == 3) return instTable_.getEntry(InstId::mulhu);
	    else if (funct3 == 4) return instTable_.getEntry(InstId::div);
	    else if (funct3 == 5) return instTable_.getEntry(InstId::divu);
	    else if (funct3 == 6) return instTable_.getEntry(InstId::rem);
	    else if (funct3 == 7) return instTable_.getEntry(InstId::remu);
	  }
	else if (funct7 == 4)
	  {
	    if      (funct3 == 0) return instTable_.getEntry(InstId::pack);
	  }
	else if (funct7 == 5)
	  {
	    if      (funct3 == 1) return instTable_.getEntry(InstId::clmul);
	    else if (funct3 == 2) return instTable_.getEntry(InstId::clmulr);
	    else if (funct3 == 3) return instTable_.getEntry(InstId::clmulh);
	    else if (funct3 == 4) return instTable_.getEntry(InstId::min);
	    else if (funct3 == 5) return instTable_.getEntry(InstId::max);
	    else if (funct3 == 6) return instTable_.getEntry(InstId::minu);
	    else if (funct3 == 7) return instTable_.getEntry(InstId::maxu);
	  }
	else if (funct7 == 0x10)
	  {
	    if      (funct3 == 1) return instTable_.getEntry(InstId::slo);
            else if (funct3 == 2) return instTable_.getEntry(InstId::sh1add);
            else if (funct3 == 4) return instTable_.getEntry(InstId::sh2add);
	    else if (funct3 == 5) return instTable_.getEntry(InstId::sro);
            else if (funct3 == 6) return instTable_.getEntry(InstId::sh3add);
	  }
	else if (funct7 == 0x14)
	  {
	    if      (funct3 == 1) return instTable_.getEntry(InstId::sbset);
	  }
	else if (funct7 == 0x20)
	  {
	    if      (funct3 == 0) return instTable_.getEntry(InstId::sub);
	    else if (funct3 == 4) return instTable_.getEntry(InstId::xnor);
	    else if (funct3 == 5) return instTable_.getEntry(InstId::sra);
	    else if (funct3 == 6) return instTable_.getEntry(InstId::orn);
	    else if (funct3 == 7) return instTable_.getEntry(InstId::andn);
	  }
	else if (funct7 == 0x24)
	  {
	    if      (funct3 == 1) return instTable_.getEntry(InstId::sbclr);
	    else if (funct3 == 5) return instTable_.getEntry(InstId::sbext);
	  }
	else if (funct7 == 0x30)
	  {
	    if      (funct3 == 1) return instTable_.getEntry(InstId::rol);
	    if      (funct3 == 5) return instTable_.getEntry(InstId::ror);
	  }
	else if (funct7 == 0x34)
	  {
	    if      (funct3 == 1) return instTable_.getEntry(InstId::sbinv);
	  }
      }
      return instTable_.getEntry(InstId::illegal);

    l13:  // 01101  U-form
      {
	UFormInst uform(inst);
	op0 = uform.bits.rd;
	op1 = uform.immed();
	return instTable_.getEntry(InstId::lui);
      }

    l14: // 01110  R-Form
      {
	const RFormInst rform(inst);
	op0 = rform.bits.rd;
	op1 = rform.bits.rs1;
	op2 = rform.bits.rs2;
	unsigned funct7 = rform.bits.funct7, funct3 = rform.bits.funct3;
	if (funct7 == 0)
	  {
	    if      (funct3 == 0) return instTable_.getEntry(InstId::addw);
	    else if (funct3 == 1) return instTable_.getEntry(InstId::sllw);
	    else if (funct3 == 5) return instTable_.getEntry(InstId::srlw);
	  }
	else if (funct7 == 1)
	  {
	    if      (funct3 == 0) return instTable_.getEntry(InstId::mulw);
	    else if (funct3 == 4) return instTable_.getEntry(InstId::divw);
	    else if (funct3 == 5) return instTable_.getEntry(InstId::divuw);
	    else if (funct3 == 6) return instTable_.getEntry(InstId::remw);
	    else if (funct3 == 7) return instTable_.getEntry(InstId::remuw);
	  }
	else if (funct7 == 0x20)
	  {
	    if      (funct3 == 0)  return instTable_.getEntry(InstId::subw);
	    else if (funct3 == 5)  return instTable_.getEntry(InstId::sraw);
	  }
      }
      return instTable_.getEntry(InstId::illegal);

    l24: // 11000   B-form
      {
	BFormInst bform(inst);
	op0 = bform.bits.rs1;
	op1 = bform.bits.rs2;
	op2 = bform.immed();
	uint32_t funct3 = bform.bits.funct3;
	if      (funct3 == 0)  return instTable_.getEntry(InstId::beq);
	else if (funct3 == 1)  return instTable_.getEntry(InstId::bne);
	else if (funct3 == 4)  return instTable_.getEntry(InstId::blt);
	else if (funct3 == 5)  return instTable_.getEntry(InstId::bge);
	else if (funct3 == 6)  return instTable_.getEntry(InstId::bltu);
	else if (funct3 == 7)  return instTable_.getEntry(InstId::bgeu);
      }
      return instTable_.getEntry(InstId::illegal);

    l25:  // 11001  I-form
      {
	IFormInst iform(inst);
	op0 = iform.fields.rd;
	op1 = iform.fields.rs1;
	op2 = iform.immed();
	if (iform.fields.funct3 == 0)
	  return instTable_.getEntry(InstId::jalr);
      }
      return instTable_.getEntry(InstId::illegal);

    l27:  // 11011  J-form
      {
	JFormInst jform(inst);
	op0 = jform.bits.rd;
	op1 = jform.immed();
	return instTable_.getEntry(InstId::jal);
      }

    l28:  // 11100  I-form
      {
	IFormInst iform(inst);
	op0 = iform.fields.rd;
	op1 = iform.fields.rs1;
	op2 = iform.uimmed(); // csr
	switch (iform.fields.funct3)
	  {
	  case 0:
	    {
	      uint32_t funct7 = op2 >> 5;
	      if (funct7 == 0) // ecall ebreak uret
		{
		  if (op1 != 0 or op0 != 0)
		    return instTable_.getEntry(InstId::illegal);
		  else if (op2 == 0)
		    return instTable_.getEntry(InstId::ecall);
		  else if (op2 == 1)
		    return instTable_.getEntry(InstId::ebreak);
		  else if (op2 == 2)
		    return instTable_.getEntry(InstId::uret);
		}
	      else if (funct7 == 9)
		{
		  if (op0 != 0)
		    return instTable_.getEntry(InstId::illegal);
		  else // sfence.vma
		    return instTable_.getEntry(InstId::illegal);
		}
	      else if (op2 == 0x102)
		return instTable_.getEntry(InstId::sret);
	      else if (op2 == 0x302)
		return instTable_.getEntry(InstId::mret);
	      else if (op2 == 0x105)
		return instTable_.getEntry(InstId::wfi);
	    }
	    break;
	  case 1:  return instTable_.getEntry(InstId::csrrw);
	  case 2:  return instTable_.getEntry(InstId::csrrs);
	  case 3:  return instTable_.getEntry(InstId::csrrc);
	  case 5:  return instTable_.getEntry(InstId::csrrwi);
	  case 6:  return instTable_.getEntry(InstId::csrrsi);
	  case 7:  return instTable_.getEntry(InstId::csrrci);
	  default: return instTable_.getEntry(InstId::illegal);
	  }
	return instTable_.getEntry(InstId::illegal);
      }
    }
  else
    return instTable_.getEntry(InstId::illegal);
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