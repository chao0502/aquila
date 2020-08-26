/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//#include "platform.h"
//#include "xil_printf.h"
//#include "sequence_file\lsRecursiveSeq.h"
//#include "sequence_file\wgetSeq.h"
//#include "javahelloSeq.h"
#include "pythonHelloSeq.h"
//#include "sequence_file\xsdkSeq.h"
//#define XPAR_MEM_ALLOC_CTRL_IP_0_S00_AXI_BASEADDR 0x43C0000
#define XPAR_MEM_ALLOC_CTRL_IP_0_S00_AXI_BASEADDR 0xC1000000
//#define memory_size 0x00010000
#define memory_size 0x2000000

volatile int *allocate_request     = (int *) (XPAR_MEM_ALLOC_CTRL_IP_0_S00_AXI_BASEADDR +  0); /*1:allocate, 2:reallocate*/
volatile int *allocate_size        = (int *) (XPAR_MEM_ALLOC_CTRL_IP_0_S00_AXI_BASEADDR +  4);
volatile int *allocate_finish      = (int *) (XPAR_MEM_ALLOC_CTRL_IP_0_S00_AXI_BASEADDR +  8); /*1:allocate finish, 2: reallocate finish* 4: fail*/
volatile int *allocate_address	   = (int *) (XPAR_MEM_ALLOC_CTRL_IP_0_S00_AXI_BASEADDR + 12);
volatile int *free_request         = (int *) (XPAR_MEM_ALLOC_CTRL_IP_0_S00_AXI_BASEADDR + 16);
volatile int *free_address 	       = (int *) (XPAR_MEM_ALLOC_CTRL_IP_0_S00_AXI_BASEADDR + 20);
volatile int *free_finish 	       = (int *) (XPAR_MEM_ALLOC_CTRL_IP_0_S00_AXI_BASEADDR + 28);
volatile int *heap_start_address   = (int *) (XPAR_MEM_ALLOC_CTRL_IP_0_S00_AXI_BASEADDR + 32); /*allocator heap start address*/
volatile int *free_counter         = (int *) (XPAR_MEM_ALLOC_CTRL_IP_0_S00_AXI_BASEADDR + 36); /*counter for free clock cycle*/
volatile int *allocate_counter     = (int *) (XPAR_MEM_ALLOC_CTRL_IP_0_S00_AXI_BASEADDR + 40); /*counter for allocate clock cycle*/


int HW_allocate(int size){
  *allocate_size = size;
  // printf("5.1:%d\n",*allocate_finish);
  *allocate_finish = 0;
  // printf("5.2:%d\n",*allocate_finish);
  *allocate_request = 1;
  // printf("5.3:%d\n",*allocate_finish);
  while(*allocate_finish == 0){}
  // printf("5.4:%d\n",*allocate_finish);
  if(*allocate_finish == 4){
	  printf("allocate fail!!\n");
	  return -1;
  }
  *allocate_finish = 0;
 // printf("5.5:%x\n",*allocate_address);
  return *allocate_address;

}

void HW_free(int addr){
	//printf("8\n");
    *free_address = addr;
    *free_finish = 0;
    *free_request = 1;
	//printf("9\n");
    while(*free_finish != 1){}
	//printf("10\n");
	*free_finish = 0;
}


int HW_realloc(int addr, int size){
	*free_address = addr;
	*allocate_size = size;
	*allocate_request = 2;
	allocate_finish = 0;
	while(*allocate_finish == 0){}

	if(*allocate_finish == 2){
	  *allocate_finish = 0;
	  return *allocate_address;
	}
	else if(*allocate_finish == 4){
	  *allocate_finish = 0;
	  printf("allocate fail!!\n");
	  return -1;
	}

}


int main( int argc, char *argv[] )
{
	int i;
	unsigned char ptr[memory_size];//32MB
	memset(ptr,memory_size,0);
	*heap_start_address = &ptr[0];

	int clk1 = clock();
	for(i=0;i<seq_num;i++)
	{
		if(mem_ops[i]==1){
			allocate_array[alloc_idx[i]]=HW_allocate(alloc_size[i]);
		}
		else
			HW_free(allocate_array[alloc_idx[i]]);
		//dummy_loop();
	}
	int clk2 = clock();
	printf("Malloc Tick: %d\n",clk2-clk1);
	/*
	int clk1 = clock();
    //printf("First time tick = %d\n", clk1);
    char *all = (char*)HW_allocate(240000);
	char *all2 = (char*)HW_allocate(240000);
	char *all3 = (char*)HW_allocate(240000);
	int clk2 = clock();
    //printf("\nSecond time tick = %d\n", clk2);
	printf("Malloc Tick: %d\n",clk2-clk1);
	
	all = "fuck you!!";
	printf("%s\n",all);

	clk1 = clock();
    //printf("First time tick = %d\n", clk1);
    HW_free(all);
	HW_free(all2);
	HW_free(all3);
	clk2 = clock();
    //printf("\nSecond time tick = %d\n", clk2);
	printf("Free Tick: %d\n",clk2-clk1);
*/
	printf("%s: \n",SeqName);
  	printf("allocate done in %d clock cycle\n",*allocate_counter);
  	printf("free done in %d clock cycle\n ",*free_counter);

	return 0;
}
