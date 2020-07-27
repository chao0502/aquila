#include "decode.h"


int main(){

    char a[100] = "10000000001";
    initial();
    int num = str_to_int(a);
    cout<<num<<endl;
}

void initial()
{
    ins[0].opcode = "0110111";
    ins[0].opstring = "LUI";

    ins[1].opcode = "0010111";
    ins[1].opstring = "AUIPC";

    ins[2].opcode = "1101111";
    ins[2].opstring = "JAL";

    ins[3].opcode = "1100111";
    ins[3].opstring = "JALR";
    ins[3].funct3 = "000";

    ins[4].opcode = "1100011";
    ins[4].opstring = "BEQ";
    ins[4].funct3 = "000";

    ins[5].opcode = "1100011";
    ins[5].opstring = "BNE";
    ins[5].funct3 = "001";

    ins[6].opcode = "1100011";
    ins[6].opstring = "BLT";
    ins[6].funct3 = "100";

    ins[7].opcode = "1100011";
    ins[7].opstring = "BGE";
    ins[7].funct3 = "101";

    ins[8].opcode = "1100011";
    ins[8].opstring = "BLTU";
    ins[8].funct3 = "110";

    ins[9].opcode = "1100011";
    ins[9].opstring = "BGEU";
    ins[9].funct3 = "111";

    ins[10].opcode = "0000011";
    ins[10].opstring = "LB";
    ins[10].funct3 = "000";

    ins[11].opcode = "0000011";
    ins[11].opstring = "LH";
    ins[11].funct3 = "001";

    ins[12].opcode = "0000011";
    ins[12].opstring = "LW";
    ins[12].funct3 = "010";

    ins[13].opcode = "0000011";
    ins[13].opstring = "LBU";
    ins[13].funct3 = "100";

    ins[14].opcode = "0000011";
    ins[14].opstring = "LHU";
    ins[14].funct3 = "101";

    ins[15].opcode = "0100011";
    ins[15].opstring = "SB";
    ins[15].funct3 = "000";

    ins[16].opcode = "0100011";
    ins[16].opstring = "SＨ";
    ins[16].funct3 = "001";

    ins[17].opcode = "0100011";
    ins[17].opstring = "SW";
    ins[17].funct3 = "010";

    ins[18].opcode = "0010011";
    ins[18].opstring = "ADDI";
    ins[18].funct3 = "000";

    ins[19].opcode = "0010011";
    ins[19].opstring = "SLTI";
    ins[19].funct3 = "010";

    ins[20].opcode = "0010011";
    ins[20].opstring = "SLTIU";
    ins[20].funct3 = "011";
        
    ins[21].opcode = "0010011";
    ins[21].opstring = "XORI";
    ins[21].funct3 = "100";

    ins[22].opcode = "0010011";
    ins[22].opstring = "ORI";
    ins[22].funct3 = "110";

    ins[23].opcode = "0010011";
    ins[23].opstring = "ANDI";
    ins[23].funct3 = "111";

    ins[24].opcode = "0010011";
    ins[24].opstring = "SLLI";
    ins[24].funct3 = "001";
    ins[24].funct7 = "0000000";

    ins[25].opcode = "0010011";
    ins[25].opstring = "SRLI";
    ins[25].funct3 = "101";
    ins[25].funct7 = "0000000";

    ins[26].opcode = "0010011";
    ins[26].opstring = "SRAI";
    ins[26].funct3 = "101";
    ins[26].funct7 = "0100000";

    ins[27].opcode = "0110011";
    ins[27].opstring = "ADD";
    ins[27].funct3 = "000";
    ins[27].funct7 = "0000000";

    ins[28].opcode = "0110011";
    ins[28].opstring = "SUB";
    ins[28].funct3 = "000";    
    ins[28].funct7 = "0100000";

    ins[29].opcode = "0110011";
    ins[29].opstring = "SLL";
    ins[29].funct3 = "001";
    ins[29].funct7 = "0000000";

    ins[30].opcode = "0110011";
    ins[30].opstring = "SLT";
    ins[30].funct3 = "010";
    ins[30].funct7 = "0000000";

    ins[31].opcode = "0110011";
    ins[31].opstring = "SLTU";
    ins[31].funct3 = "011";
    ins[31].funct7 = "0000000";

    ins[32].opcode = "0110011";
    ins[32].opstring = "XOR";
    ins[32].funct3 = "100";
    ins[32].funct7 = "0000000";

    ins[33].opcode = "0110011";
    ins[33].opstring = "SRL";
    ins[33].funct3 = "101";
    ins[33].funct7 = "0000000";

    ins[34].opcode = "0110011";
    ins[34].opstring = "SRA";
    ins[34].funct3 = "101";
    ins[34].funct7 = "0100000";

    ins[35].opcode = "0110011";
    ins[35].opstring = "OR";
    ins[35].funct3 = "110";
    ins[35].funct7 = "0000000";

    ins[37].opcode = "0110011";
    ins[37].opstring = "AND";
    ins[37].funct3 = "111";
    ins[37].funct7 = "0000000";

    ins[38].opcode = "0001111";
    ins[38].opstring = "FENCE";
    ins[38].funct3 = "000";

    ins[39].opcode = "1110011";
    ins[39].opstring = "ECALL";

    ins[40].opcode = "0110011";
    ins[40].opstring = "EBREAK";

    ins[41].opcode = "0110011";
    ins[41].opstring = "MUL";
    ins[41].funct3 = "000";
    ins[41].funct7 = "0000001";

    ins[42].opcode = "0110011";
    ins[42].opstring = "MULH";
    ins[42].funct3 = "001";
    ins[42].funct7 = "0000001";

    ins[43].opcode = "0110011";
    ins[43].opstring = "MULHSU";
    ins[43].funct3 = "010";
    ins[43].funct7 = "0000001";

    ins[44].opcode = "0110011";
    ins[44].opstring = "MULHU";
    ins[44].funct3 = "011";
    ins[44].funct7 = "0000001";

    ins[45].opcode = "0110011";
    ins[45].opstring = "DIV";
    ins[45].funct3 = "100";
    ins[45].funct7 = "0000001";

    ins[46].opcode = "0110011";
    ins[46].opstring = "DIVU";
    ins[46].funct3 = "101";
    ins[46].funct7 = "0000001";

    ins[47].opcode = "0110011";
    ins[47].opstring = "REM";
    ins[47].funct3 = "110";
    ins[47].funct7 = "0000001";

    ins[48].opcode = "0110011";
    ins[48].opstring = "REMU";
    ins[48].funct3 = "111";
    ins[48].funct7 = "0000001";

    ins[49].opcode = "0101111";
    ins[49].opstring = "LR.W";
    ins[49].funct3 = "010";
    ins[49].funct7 = "00010";

    ins[50].opcode = "0101111";
    ins[50].opstring = "SC.W";
    ins[50].funct3 = "010";
    ins[50].funct7 = "00011";

    ins[51].opcode = "0101111";
    ins[51].opstring = "AMOSWAP.W";
    ins[51].funct3 = "010";
    ins[51].funct7 = "00001";

    ins[52].opcode = "0101111";
    ins[52].opstring = "AMOADD.W";
    ins[52].funct3 = "010";
    ins[52].funct7 = "00000";

    ins[53].opcode = "0101111";
    ins[53].opstring = "AMOXOR.W";
    ins[53].funct3 = "010";
    ins[53].funct7 = "00100";

    ins[54].opcode = "0101111";
    ins[54].opstring = "AMOAND.W";
    ins[54].funct3 = "010";
    ins[54].funct7 = "01100";

    ins[55].opcode = "0101111";
    ins[55].opstring = "AMOOR.W";
    ins[55].funct3 = "010";
    ins[55].funct7 = "01000";

    ins[56].opcode = "0101111";
    ins[56].opstring = "AMOMIN.W";
    ins[56].funct3 = "010";
    ins[56].funct7 = "10000";

    ins[57].opcode = "0101111";
    ins[57].opstring = "AMOMAX.W";
    ins[57].funct3 = "010";
    ins[57].funct7 = "10100";

    ins[58].opcode = "0101111";
    ins[58].opstring = "AMOMINU.W";
    ins[58].funct3 = "010";
    ins[58].funct7 = "11000";

    ins[59].opcode = "0101111";
    ins[59].opstring = "AMOMAXU.W";
    ins[59].funct3 = "010";
    ins[59].funct7 = "11100";

    ins[60].opcode = "1110011";
    ins[60].opstring = "CSRRW";
    ins[60].funct3 = "001";

    ins[61].opcode = "1110011";
    ins[61].opstring = "CSRRS";
    ins[61].funct3 = "010";

    ins[62].opcode = "1110011";
    ins[62].opstring = "CSRRC";
    ins[62].funct3 = "011";

    ins[63].opcode = "1110011";
    ins[63].opstring = "CSRRWI";
    ins[63].funct3 = "101";

    ins[64].opcode = "1110011";
    ins[64].opstring = "CSRRSI";
    ins[64].funct3 = "110";

    ins[65].opcode = "1110011";
    ins[65].opstring = "CSRRCI";
    ins[65].funct3 = "111";
}

int str_to_int(char* str)
{
    int total = 0;
    for(int i = strlen(str); i >= 0; i--){
        total*=2;
        total += (str[i] == '1') ? 1 : 0;
    }
    return total;
}