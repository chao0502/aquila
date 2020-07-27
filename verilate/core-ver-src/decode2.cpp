#include "decode2.h"

//不小心沒注意順序＝ ＝ 
//opcode & funct3 & funct5 & funct7 不用反轉
//其他要轉
/*
int main()
{
    fstream log_file("test.txt",fstream::out);
    char* a = (char*)malloc(35);
    strcpy(a,"00000000110000010010000010000011");
    strcpy(a,"00000000111100010000011110100011");
    riscv_decode(a, &log_file);
    log_file<<endl;
}*/

void riscv_decode(char* bin_code_tra, fstream* log_file)
{
    char* ret = (char*)malloc(50);
    char* bin_code = (char*)malloc(35);
    bin_code = str_inverse(bin_code_tra);

    char *opcode, *funct3, *funct5, *funct7, *rd_str, *rs1_str, *rs2_str, *shamt;
    char *immi_31_12, *immi_11_0, *immi_11_5_4_0;
    opcode = (char*)malloc(8);
    funct3 = (char*)malloc(4);
    funct5 = (char*)malloc(6);
    funct7 = (char*)malloc(8);
    rd_str = (char*)malloc(6);
    rs1_str = (char*)malloc(6);
    rs2_str = (char*)malloc(6);
    shamt = (char*)malloc(6); 
    immi_31_12 = (char*)malloc(21);
    immi_11_0 = (char*)malloc(13);
    immi_11_5_4_0 = (char*)malloc(21);
    
    for(int i=0; i<7; i++)
        opcode[i] = bin_code[i];
    for(int i=0; i<3; i++)
        funct3[i] = bin_code[i+12];
    for(int i=0; i<5; i++)
        funct5[i] = bin_code[i+27];
    for(int i=0; i<7; i++) 
        funct7[i] = bin_code[i+25];
    for(int i=0; i<5; i++)
        rd_str[i] = bin_code[i+7];
    for(int i=0; i<5; i++)
        rs1_str[i] = bin_code[i+15];
    for(int i=0; i<5; i++)
        rs2_str[i] = bin_code[i+20];
    for(int i=0; i<20; i++)
        immi_31_12[i] = bin_code[i+12];
    for(int i=0; i<=11; i++)
        immi_11_0[i] = bin_code[i+20];
    for(int i=0; i<4; i++)
        immi_11_5_4_0[i] = bin_code[i+7];
    for(int i=5; i<=11; i++)
        immi_11_5_4_0[i] = bin_code[i+15];
    for(int i=0; i<5; i++)
        shamt[i] = bin_code[i+20];

    rd_str = str_inverse(rd_str);
    rs1_str = str_inverse(rs1_str);
    rs2_str = str_inverse(rs2_str);
    shamt = str_inverse(shamt);
    immi_31_12 = str_inverse(immi_31_12);
    immi_11_0 = str_inverse(immi_11_0);
    immi_11_5_4_0 = str_inverse(immi_11_5_4_0);

    int rd = str_to_int(rd_str);
    int rs1 = str_to_int(rs1_str);
    int rs2 = str_to_int(rs2_str);

    //LUI && AUIPC
    if(!strcmp(opcode,"1110110") || !strcmp(opcode,"1110100")){
    	char *immi_31_12_hex = (char *)malloc(21);
    	immi_31_12_hex = str_to_hex(immi_31_12);
    	*log_file << (!strcmp(opcode,"1110110") ? "LUI" : "AUIPC");
        *log_file <<" r"<<(int)rd<<",0x"<<immi_31_12_hex;
        free(immi_31_12_hex);
    }
    //JAL
    else if(!strcmp(opcode,"1111011"))
        *log_file <<"JAL ";              
    //JALR
    else if(!strcmp(opcode,"1110011"))
    	*log_file <<"JALR ";
    //BEQ...
    else if(!strcmp(opcode,"1100011")){
    	if(!strcmp(funct3,"000"))
    		*log_file <<"BEQ";
    	else if(!strcmp(funct3,"100"))
    		*log_file <<"BNE";
    	else if(!strcmp(funct3,"001"))
    		*log_file <<"BLT";
    	else if(!strcmp(funct3,"101"))
    		*log_file <<"BGE";
    	else if(!strcmp(funct3,"011"))
    		*log_file <<"BLTU";
    	else if(!strcmp(funct3,"111"))
    		*log_file <<"BGEU";
    	*log_file <<" r"<<(int)rs1<<", r"<<(int)rs2;
    }
    //LB...
    else if(!strcmp(opcode,"1100000")){
    	if(!strcmp(funct3,"000"))
    		*log_file <<"LB";
    	else if(!strcmp(funct3,"100"))
    		*log_file <<"LH";
    	else if(!strcmp(funct3,"010"))
    		*log_file <<"LW";
    	else if(!strcmp(funct3,"001"))
    		*log_file <<"LBU";
    	else if(!strcmp(funct3,"101"))
    		*log_file <<"LHU";
    	*log_file <<" r"<<(int)rd<<" "<<str_to_int(immi_11_0)<<"(r"<<(int)rs1<<") ";
    }
    //SB...
    else if(!strcmp(opcode,"1100010")){
    	if(!strcmp(funct3,"000"))
    		*log_file <<"SB";
    	else if(!strcmp(funct3,"100"))
    		*log_file <<"SH";
    	else if(!strcmp(funct3,"010"))
    		*log_file <<"SW";
    	*log_file <<" r"<<(int)rs2<<" "<<str_to_int(immi_11_5_4_0)<<"(r"<<(int)rs1<<") ";
    }
    //ADDI...
    else if(!strcmp(opcode,"1100100")){
    	if(!strcmp(funct3,"000"))
    		*log_file <<"ADDI"<<" r"<<(int)rd<<", "<<"r"<<(int)rs1<<", "<<str_to_int(immi_11_0);
    	else if(!strcmp(funct3,"010"))
    		*log_file <<"SLTI"<<" r"<<(int)rd<<", "<<"r"<<(int)rs1<<", "<<str_to_int(immi_11_0);
    	else if(!strcmp(funct3,"110"))
    		*log_file <<"SLTIU"<<" r"<<(int)rd<<", "<<"r"<<(int)rs1<<", "<<str_to_int(immi_11_0);
    	else if(!strcmp(funct3,"001"))
    		*log_file <<"XORI"<<" r"<<(int)rd<<", "<<"r"<<(int)rs1<<", "<<str_to_int(immi_11_0);
    	else if(!strcmp(funct3,"011"))
    		*log_file <<"ORI"<<" r"<<(int)rd<<", "<<"r"<<(int)rs1<<", "<<str_to_int(immi_11_0);
    	else if(!strcmp(funct3,"111"))
    		*log_file <<"ANDI"<<" r"<<(int)rd<<", "<<"r"<<(int)rs1<<", "<<str_to_int(immi_11_0);
    	else if(!strcmp(funct3,"100"))
    		*log_file <<"SLLI "<<"r"<<(int)rd<<", "<<"r"<<(int)rs1<<", "<<str_to_int(shamt);
    	else if(!strcmp(funct3,"101")){
    		if(funct7 == "0000000")
                *log_file <<"SRLI "<<"r"<<(int)rd<<", "<<"r"<<(int)rs1<<", "<<str_to_int(shamt);
            else
                *log_file <<"SRAI "<<"r"<<(int)rd<<", "<<"r"<<(int)rs1<<", "<<str_to_int(shamt);
    	}
    }
    //ADD...
    else if(!strcmp(opcode,"1100110") && strcmp(funct7,"1000000")){
    	if(!strcmp(funct3,"000")){
            if(!strcmp(funct7,"0000000") )
                *log_file <<"ADD ";
            else
                *log_file <<"SUB ";
        }
        else if(!strcmp(funct3,"101")){
            if(!strcmp(funct7,"0000000"))
                *log_file <<"SRL ";
            else
                *log_file <<"SRA ";
        }
        else if(!strcmp(funct3,"100"))
            *log_file <<"SLL ";
        else if(!strcmp(funct3,"010"))
            *log_file <<"SLT ";
        else if(!strcmp(funct3,"110"))
            *log_file <<"SLTU";
        else if(!strcmp(funct3,"001"))
            *log_file <<"XOR ";
        else if(!strcmp(funct3,"011"))
            *log_file <<"OR ";
        else if(!strcmp(funct3,"111"))
            *log_file <<"AND ";
        *log_file <<" r"<<(int)rd<<", r"<<(int)rs1<<", r"<<(int)rs2;
    }
    //MUL...
    else if(!strcmp(opcode,"1100110")){
        if(!strcmp(funct3,"000"))
            *log_file <<"MUL ";
        else if(!strcmp(funct3,"100"))
            *log_file <<"MULH ";
        else if(!strcmp(funct3,"010"))
            *log_file <<"MULHSU ";
        else if(!strcmp(funct3,"110"))
            *log_file <<"MULHU ";
        else if(!strcmp(funct3,"001"))
            *log_file <<"DIV ";
        else if(!strcmp(funct3,"101"))
            *log_file <<"DIVU ";
        else if(!strcmp(funct3,"011"))
            *log_file <<"REM ";
        else if(!strcmp(funct3,"111"))
            *log_file <<"REMU ";
        *log_file <<"r"<<(int)rd<<", r"<<(int)rs1<<", r"<<(int)rs2;
    }
    //Atomic
    else if(!strcmp(opcode,"1111010")){
    	if(!strcmp(funct5,"00011"))
            *log_file <<"SC.W ";
        else if(!strcmp(funct5,"10000"))
            *log_file <<"AMOSWAP.W ";
        else if(!strcmp(funct5,"00000"))
            *log_file <<"AMOADD.W ";
        else if(!strcmp(funct5,"00100"))
            *log_file <<"AMOXOR.W ";
        else if(!strcmp(funct5,"00110"))
            *log_file <<"AMOAND.W ";
        else if(!strcmp(funct5,"00010"))
            *log_file <<"AMDOR.W ";
        else if(!strcmp(funct5,"00001"))
            *log_file <<"ADMMIN.W ";
        else if(!strcmp(funct5,"00101"))
            *log_file <<"AMOMAX.W ";
        else if(!strcmp(funct5,"00011"))
            *log_file <<"AMOMINU.W ";
        else if(!strcmp(funct5,"00111"))
            *log_file <<"AMOMAXU.W ";
       	else if(!strcmp(funct5,"01000"))
       		*log_file <<"LR.W ";
    }
    //CSR
    else if(!strcmp(opcode,"1100111")){

    }
    
 }

int str_to_int(char* str)
{
    int total = 0;
    for(int i = 0; i < strlen(str); i++){
        total*=2;
        total += (str[i] == '1') ? 1 : 0;
    }
    return total;
}

char* str_inverse(char* str)
{
    char* tem = (char*)malloc(35);
    for(int i = 0; i < strlen(str); i++)
        tem[strlen(str)-i-1] = str[i];
    return tem;
}

char* str_to_hex(char* str)
{
    char* tem = (char*)malloc(21); 
    for(int i = 0; i < strlen(str) - 4; i+=4){
        for(int j = 0; j < 4; j++)
            tem[j] = str[i+j];
        if(tem == "0000")
            tem[i] = '0';
        else if(tem == "0001")
            tem[i] = '1';
        else if(tem == "0010")
            tem[i] = '2';
        else if(tem == "0011")
            tem[i] = '3';
        else if(tem == "0100")
            tem[i] = '4';
        else if(tem == "0101")
            tem[i] = '5';
        else if(tem == "0110")
            tem[i] = '6';
        else if(tem == "0111")
            tem[i] = '7';
        else if(tem == "1000")
            tem[i] = '8';
        else if(tem == "1001")
            tem[i] = '9';
        else if(tem == "1010")
            tem[i] = 'A';
        else if(tem == "1011")
            tem[i] = 'B';
        else if(tem == "1100")
            tem[i] = 'C';
        else if(tem == "1101")
            tem[i] = 'D';
        else if(tem == "1110")
            tem[i] = 'E';
        else if(tem == "1111")
            tem[i] = 'F';
    }
    return tem;
}

char* int_to_str(unsigned int num){
    char *a = (char*)malloc(33);
    for(int i = 31; i >= 3; i-=4){
        int k = num % 16;
        num /= 16;
        a[i] = k % 2 + 48;
        k /= 2;
        a[i-1] = k % 2 + 48;
        k /= 2;
        a[i-2] = k % 2 + 48;
        k /= 2;
        a[i-3] = k % 2 + 48;
        k /= 2;
    }
    return a;
}