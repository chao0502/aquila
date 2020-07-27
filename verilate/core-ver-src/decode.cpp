#include "decode.h"

#define instruction_count 65


int main()
{
    //cout<<"1";
    //initial();
    char* a = (char*)malloc(35);
    strcpy(a,"00000010010001111000010100010011");
    cout<<a<<endl;
    //riscv_decode(a);
}

void riscv_decode(char* bin_code_tra)
{
    //待修正：不能讓func回傳string
    char* bin_code = (char*)malloc(35);
    bin_code = str_traverse(bin_code_tra);
    /*printf("%d:",strlen(bin_code));
    for(int i=0; i<strlen(bin_code); i++)
        printf("%c",bin_code[i]);
    cout<<endl;*/
    char *opcode, *funct3, *funct5, *funct7, *rd_str, *rs1_str, *rs2_str, *shamt;
    char *immi_31_12, *immi_11_0, *immi_11_5_4_0;
    opcode = (char*)malloc(35);
    funct3 = (char*)malloc(35);
    funct5 = (char*)malloc(35);
    funct7 = (char*)malloc(35);
    rd_str = (char*)malloc(35);
    rs1_str = (char*)malloc(35);
    rs2_str = (char*)malloc(35);
    shamt = (char*)malloc(35); 
    immi_31_12 = (char*)malloc(35);
    immi_11_0 = (char*)malloc(35);
    immi_11_5_4_0 = (char*)malloc(35);
    
    for(int i=0; i<6; i++)
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

    int rd = str_to_int(rd_str);
    int rs1 = str_to_int(rs1_str);
    int rs2 = str_to_int(rs2_str);

    for(int i=0; i<instruction_count-1; i++){
        //printf("%d:%s vs %s\n",i,opcode,ins[i].opcode);
        if(!strcmp(ins[i].opcode,opcode)){
            //JAL&JALR
            printf("FIND:%d\n",i);
            if(i>=2 && i<=3){
                if(strcmp(funct3,"000"))
                    cout<<"JAL ";
                else
                    cout<<"JALR ";
            }
            //BEQ...
            else if(i>=4 && i<=9 && !strcmp(funct3,ins[i].funct3)){
                cout<<ins[i].opstring<<"r "<<rs1<<", r"<<rs2;
            }
            //LB...
            else if(i>=10 && i<=14 && !strcmp(funct3,ins[i].funct3)){
                cout<<ins[i].opstring<<" r"<<rd<<" "<<str_to_int(immi_11_0)<<"(r"<<rs1<<") ";
            }
            //SB...
            else if(i>=15 && i<=17 && !strcmp(funct3,ins[i].funct3)){
                cout<<ins[i].opstring<<" r"<<rs2<<" "<<str_to_int(immi_11_5_4_0)<<"(r"<<rs1<<") ";
            }
            //ADDI...
            else if(i>=18 && i<=23 && !strcmp(funct3,ins[i].funct3)){
                cout<<ins[i].opstring<<" r"<<rd<<", "<<"r"<<rs1<<", "<<str_to_int(immi_11_0);
            }
            //SLL...
            else if(i>=24 && i<=26){
                if(!strcmp(funct3,"001"))
                    cout<<"SLLI ";
                else if(!strcmp(funct3,"101")){
                    if(funct7 == "0000000")
                        cout<<"SRLI ";
                    else
                        cout<<"SRAI ";
                }
                cout<<"r"<<rd<<", "<<"r"<<rs1<<", "<<str_to_int(shamt);
            }
            //ADD...
            else if(i>=27 && i<=37){
                if(!strcmp(funct3,"000")){
                    if(funct7 == "0000000")
                        cout<<"ADD ";
                    else
                        cout<<"SUB ";
                }
                else if(!strcmp(funct3,"101")){
                    if(funct7 == "0000000")
                        cout<<"SRL ";
                    else
                        cout<<"SRA ";
                }
                else if(!strcmp(funct3,ins[i].funct3)){
                    for(int k = 0; k < strlen(ins[i].opstring); i++)
                        cout<<ins[i].opstring[k];
                    printf(" ");
                    cout<<funct3;
                }

            }
            //MUL...
            else if(i>=41 && i<=48 && !strcmp(funct3,ins[i].funct3)){
                cout<<ins[i].opstring<<" r"<<rd<<", r"<<rs1<<", r"<<rs2;
            }
            else if(i>=49 && i<=59){
                if(i == 49)
                    cout<<"LR.W r"<<rd<<", r"<<rs1;
                else{
                    if(!strcmp(funct5,"00011"))
                        cout<<"SC.W";
                    else if(!strcmp(funct5,"00001"))
                        cout<<"AMOSWAP.W";
                    else if(!strcmp(funct5,"00000"))
                        cout<<"AMOADD.W";
                    else if(!strcmp(funct5,"00100"))
                        cout<<"AMOXOR.W";
                    else if(!strcmp(funct5,"01100"))
                        cout<<"AMOAND.W";
                    else if(!strcmp(funct5,"01000"))
                        cout<<"AMDOR.W";
                    else if(!strcmp(funct5,"10000"))
                        cout<<"ADMMIN.W";
                    else if(!strcmp(funct5,"10100"))
                        cout<<"AMOMAX.W";
                    else if(!strcmp(funct5,"11000"))
                        cout<<"AMOMINU.W";
                    else if(!strcmp(funct5,"11100"))
                        cout<<"AMOMAXU.W";
                }
            }
            else if(i>=60 && i<=65){

            }
            else{
                string immi_31_12_hex(immi_31_12);
                cout<<ins[i].opstring<<" r"<<rd<<",0x"<<immi_31_12_hex;
            }
        }
    }
}

void initial()
{
	for(int i = 0; i < instruction_count - 1; i++){
		ins[i].opcode = (char*)malloc(10);
		ins[i].opstring = (char*)malloc(10);
		ins[i].funct3 = (char*)malloc(10);
		ins[i].funct7 = (char*)malloc(10);
	}
    strcpy(ins[0].opcode,"0110111");
    strcpy(ins[0].opstring,"LUI");

    strcpy(ins[1].opcode,"0010111");
    strcpy(ins[1].opstring,"AUIPC");

    strcpy(ins[2].opcode,"1101111");
    strcpy(ins[2].opstring,"JAL");

    strcpy(ins[3].opcode,"1100111");
    strcpy(ins[3].opstring,"JALR");
    strcpy(ins[3].funct3,"000");

    strcpy( ins[4].opcode,"1100011");
    strcpy(ins[4].opstring,"BEQ");
    strcpy(ins[4].funct3,"000");

    strcpy( ins[5].opcode,"1100011");
    strcpy(ins[5].opstring,"BNE");
    strcpy(ins[5].funct3,"001");

    strcpy( ins[6].opcode,"1100011");
    strcpy(ins[6].opstring,"BLT");
    strcpy(ins[6].funct3,"100");

    strcpy( ins[7].opcode,"1100011");
    strcpy(ins[7].opstring,"BGE");
    strcpy(ins[7].funct3,"101");

    strcpy( ins[8].opcode,"1100011");
    strcpy(ins[8].opstring,"BLTU");
    strcpy(ins[8].funct3,"110");

    strcpy( ins[9].opcode,"1100011");
    strcpy(ins[9].opstring,"BGEU");
    strcpy(ins[9].funct3,"111");

    strcpy(ins[10].opcode,"0000011");
    strcpy(ins[10].opstring,"LB");
    strcpy(ins[10].funct3,"000");

    strcpy(ins[11].opcode,"0000011");
    strcpy(ins[11].opstring,"LH");
    strcpy(ins[11].funct3,"001");

    strcpy(ins[12].opcode,"0000011");
    strcpy(ins[12].opstring,"LW");
    strcpy(ins[12].funct3,"010");

    strcpy(ins[13].opcode,"0000011");
    strcpy(ins[13].opstring,"LBU");
    strcpy(ins[13].funct3,"100");

    strcpy(ins[14].opcode,"0000011");
    strcpy(ins[14].opstring,"LHU");
    strcpy(ins[14].funct3,"101");

    strcpy(ins[15].opcode,"0100011");
    strcpy(ins[15].opstring,"SB");
    strcpy(ins[15].funct3,"000");

    strcpy(ins[16].opcode,"0100011");
    strcpy(ins[16].opstring,"SH");
    strcpy(ins[16].funct3,"001");

    strcpy(ins[17].opcode,"0100011");
    strcpy(ins[17].opstring,"SW");
    strcpy(ins[17].funct3,"010");

    strcpy(ins[18].opcode,"0010011");
    strcpy(ins[18].opstring,"ADDI");
    strcpy(ins[18].funct3,"000");

    strcpy(ins[19].opcode,"0010011");
    strcpy(ins[19].opstring,"SLTI");
    strcpy(ins[19].funct3,"010");

    strcpy(ins[20].opcode,"0010011");
    strcpy(ins[20].opstring,"SLTIU");
    strcpy(ins[20].funct3,"011");
        
    strcpy(ins[21].opcode,"0010011");
    strcpy(ins[21].opstring,"XORI");
    strcpy(ins[21].funct3,"100");

    strcpy(ins[22].opcode,"0010011");
    strcpy(ins[22].opstring,"ORI");
    strcpy(ins[22].funct3,"110");

    strcpy(ins[23].opcode,"0010011");
    strcpy(ins[23].opstring,"ANDI");
    strcpy(ins[23].funct3,"111");

    strcpy(ins[24].opcode,"0010011");
    strcpy(ins[24].opstring,"SLLI");
    strcpy(ins[24].funct3,"001");
    strcpy(ins[24].funct7,"0000000");

    strcpy(ins[25].opcode,"0010011");
    strcpy(ins[25].opstring,"SRLI");
    strcpy(ins[25].funct3,"101");
    strcpy(ins[25].funct7,"0000000");

    strcpy(ins[26].opcode,"0010011");
    strcpy(ins[26].opstring,"SRAI");
    strcpy(ins[26].funct3,"101");
    strcpy(ins[26].funct7,"0100000");

    strcpy(ins[27].opcode,"0110011");
    strcpy(ins[27].opstring,"ADD");
    strcpy(ins[27].funct3,"000");
    strcpy(ins[27].funct7,"0000000");

    strcpy(ins[28].opcode,"0110011");
    strcpy(ins[28].opstring,"SUB");
    strcpy(ins[28].funct3,"000");    
    strcpy(ins[28].funct7,"0100000");

    strcpy(ins[29].opcode,"0110011");
    strcpy(ins[29].opstring,"SLL");
    strcpy(ins[29].funct3,"001");
    strcpy(ins[29].funct7,"0000000");

    strcpy(ins[30].opcode,"0110011");
    strcpy(ins[30].opstring,"SLT");
    strcpy(ins[30].funct3,"010");
    strcpy(ins[30].funct7,"0000000");

    strcpy(ins[31].opcode,"0110011");
    strcpy(ins[31].opstring,"SLTU");
    strcpy(ins[31].funct3,"011");
    strcpy(ins[31].funct7,"0000000");

    strcpy(ins[32].opcode,"0110011");
    strcpy(ins[32].opstring,"XOR");
    strcpy(ins[32].funct3,"100");
    strcpy(ins[32].funct7,"0000000");

    strcpy(ins[33].opcode,"0110011");
    strcpy(ins[33].opstring,"SRL");
    strcpy(ins[33].funct3,"101");
    strcpy(ins[33].funct7,"0000000");

    strcpy(ins[34].opcode,"0110011");
    strcpy(ins[34].opstring,"SRA");
    strcpy(ins[34].funct3,"101");
    strcpy(ins[34].funct7,"0100000");

    strcpy(ins[35].opcode,"0110011");
    strcpy(ins[35].opstring,"OR");
    strcpy(ins[35].funct3,"110");
    strcpy(ins[35].funct7,"0000000");

    strcpy(ins[37].opcode,"0110011");
    strcpy(ins[37].opstring,"AND");
    strcpy(ins[37].funct3,"111");
    strcpy(ins[37].funct7,"0000000");

    strcpy(ins[38].opcode,"0001111");
    strcpy(ins[38].opstring,"FENCE");
    strcpy(ins[38].funct3,"000");

    strcpy(ins[39].opcode,"1110011");
    strcpy(ins[39].opstring,"ECALL");

    strcpy(ins[40].opcode,"0110011");
    strcpy(ins[40].opstring,"EBREAK");

    strcpy(ins[41].opcode,"0110011");
    strcpy(ins[41].opstring,"MUL");
    strcpy(ins[41].funct3,"000");
    strcpy(ins[41].funct7,"0000001");

    strcpy(ins[42].opcode,"0110011");
    strcpy(ins[42].opstring,"MULH");
    strcpy(ins[42].funct3,"001");
    strcpy(ins[42].funct7,"0000001");

    strcpy(ins[43].opcode,"0110011");
    strcpy(ins[43].opstring,"MULHSU");
    strcpy(ins[43].funct3,"010");
    strcpy(ins[43].funct7,"0000001");

    strcpy(ins[44].opcode,"0110011");
    strcpy(ins[44].opstring,"MULHU");
    strcpy(ins[44].funct3,"011");
    strcpy(ins[44].funct7,"0000001");

    strcpy(ins[45].opcode,"0110011");
    strcpy(ins[45].opstring,"DIV");
    strcpy(ins[45].funct3,"100");
    strcpy(ins[45].funct7,"0000001");

    strcpy(ins[46].opcode,"0110011");
    strcpy(ins[46].opstring,"DIVU");
    strcpy(ins[46].funct3,"101");
    strcpy(ins[46].funct7,"0000001");

    strcpy(ins[47].opcode,"0110011");
    strcpy(ins[47].opstring,"REM");
    strcpy(ins[47].funct3,"110");
    strcpy(ins[47].funct7,"0000001");

    strcpy(ins[48].opcode,"0110011");
    strcpy(ins[48].opstring,"REMU");
    strcpy(ins[48].funct3,"111");
    strcpy(ins[48].funct7,"0000001");

    strcpy(ins[49].opcode,"0101111");
    strcpy(ins[49].opstring,"LR.W");
    strcpy(ins[49].funct3,"010");
    strcpy(ins[49].funct7,"00010");

    strcpy(ins[50].opcode,"0101111");
    strcpy(ins[50].opstring,"SC.W");
    strcpy(ins[50].funct3,"010");
    strcpy(ins[50].funct7,"00011");

    strcpy(ins[51].opcode,"0101111");
    strcpy(ins[51].opstring,"AMOSWAP.W");
    strcpy(ins[51].funct3,"010");
    strcpy(ins[51].funct7,"00001");

    strcpy(ins[52].opcode,"0101111");
    strcpy(ins[52].opstring,"AMOADD.W");
    strcpy(ins[52].funct3,"010");
    strcpy(ins[52].funct7,"00000");

    strcpy(ins[53].opcode,"0101111");
    strcpy(ins[53].opstring,"AMOXOR.W");
    strcpy(ins[53].funct3,"010");
    strcpy(ins[53].funct7,"00100");

    strcpy(ins[54].opcode,"0101111");
    strcpy(ins[54].opstring,"AMOAND.W");
    strcpy(ins[54].funct3,"010");
    strcpy(ins[54].funct7,"01100");

    strcpy(ins[55].opcode,"0101111");
    strcpy(ins[55].opstring,"AMOOR.W");
    strcpy(ins[55].funct3,"010");
    strcpy(ins[55].funct7,"01000");

    strcpy(ins[56].opcode,"0101111");
    strcpy(ins[56].opstring,"AMOMIN.W");
    strcpy(ins[56].funct3,"010");
    strcpy(ins[56].funct7,"10000");

    strcpy(ins[57].opcode,"0101111");
    strcpy(ins[57].opstring,"AMOMAX.W");
    strcpy(ins[57].funct3,"010");
    strcpy(ins[57].funct7,"10100");

    strcpy(ins[58].opcode,"0101111");
    strcpy(ins[58].opstring,"AMOMINU.W");
    strcpy(ins[58].funct3,"010");
    strcpy(ins[58].funct7,"11000");

    strcpy(ins[59].opcode,"0101111");
    strcpy(ins[59].opstring,"AMOMAXU.W");
    strcpy(ins[59].funct3,"010");
    strcpy(ins[59].funct7,"11100");

    strcpy(ins[60].opcode,"1110011");
    strcpy(ins[60].opstring,"CSRRW");
    strcpy(ins[60].funct3,"001");

    strcpy(ins[61].opcode,"1110011");
    strcpy(ins[61].opstring,"CSRRS");
    strcpy(ins[61].funct3,"010");

    strcpy(ins[62].opcode,"1110011");
    strcpy(ins[62].opstring,"CSRRC");
    strcpy(ins[62].funct3,"011");

    strcpy(ins[63].opcode,"1110011");
    strcpy(ins[63].opstring,"CSRRWI");
    strcpy(ins[63].funct3,"101");

    strcpy(ins[64].opcode,"1110011");
    strcpy(ins[64].opstring,"CSRRSI");
    strcpy(ins[64].funct3,"110");

    strcpy(ins[65].opcode,"1110011");
    strcpy(ins[65].opstring,"CSRRCI");
    strcpy(ins[65].funct3,"111");
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

char* str_traverse(char* str)
{
    char* tem = (char*)malloc(35);
    for(int i = 0; i < strlen(str); i++)
        tem[strlen(str)-i-1] = str[i];
    return tem;
}

char* str_to_hex(char* str)
{
    char* tem = (char*)malloc(20); 
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