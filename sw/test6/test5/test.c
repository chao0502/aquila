// =============================================================================
//  Program : test.c
//  Author  : Chun-Jen Tsai
//  Date    : Dec/09/2019
// -----------------------------------------------------------------------------
//  Description:
//  This is the minimal time library for aquila.
// -----------------------------------------------------------------------------
//  Revision information:
//
//  None.
// -----------------------------------------------------------------------------
//  License information:
//
//  This software is released under the BSD-3-Clause Licence,
//  see https://opensource.org/licenses/BSD-3-Clause for details.
//  In the following license statements, "software" refers to the
//  "source code" of the complete hardware/software system.
//
//  Copyright 2019,
//                    Embedded Intelligent Systems Lab (EISL)
//                    Deparment of Computer Science
//                    National Chiao Tung Uniersity
//                    Hsinchu, Taiwan.
//
//  All rights reserved.
//
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions are met:
//
//  1. Redistributions of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//
//  2. Redistributions in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//
//  3. Neither the name of the copyright holder nor the names of its contributors
//     may be used to endorse or promote products derived from this software
//     without specific prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
//  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
//  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
//  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
//  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
//  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
//  POSSIBILITY OF SUCH DAMAGE.
// =============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <mallocr2.h>
#include "uart.h"
#include "pythonHelloSeq.h"

//void malloc_test(int nwords);
//void timer_isr_test();
//void sleep(int msec);

//volatile int got_isr;




int main(void)
{
    outbyte('H');
    outbyte('e');
    outbyte('l');
    outbyte('l');
    outbyte('o');
    outbyte(' ');
    outbyte('W');
    outbyte('o');
    outbyte('r');
    outbyte('l');
    outbyte('d');
    outbyte('!');
    outbyte('\n');

    printf("Test Print\n");
    float ver = 0.9;
    printf("Hello world!\n");
    printf("Hello, Aquila %.1f!\n", ver);
    printf("The address of 'ver' is 0x%X\n\n", (unsigned) &ver);

    int i;

    int clk1 = clock();
	for(i=0;i<seq_num;i++)
	{
		if(mem_ops[i]==1){
			allocate_array[alloc_idx[i]]=mALLOc(alloc_size[i]);
		}
		else
			fREe(allocate_array[alloc_idx[i]]);
		dummy_loop();
	}
	int clk2 = clock();
	printf("Malloc Tick: %d\n",clk2-clk1);
/*
	int clk1 = clock();
    //printf("First time tick = %d\n", clk1);
    char *all = (char*)malloc(240000);
    char *all2 = (char*)malloc(240000);
    char *all3 = (char*)malloc(240000);
	int clk2 = clock();
    //printf("\nSecond time tick = %d\n", clk2);
	printf("Malloc Tick: %d\n",clk2-clk1);
	
    all = "fuck you!!";
	printf("%s\n",all);
	
	clk1 = clock();
    //printf("First time tick = %d\n", clk1);
    free(all);
    free(all2);
    free(all3);
	clk2 = clock();
    //printf("\nSecond time tick = %d\n", clk2);
	printf("Free Tick: %d\n",clk2-clk1);
*/
    /*printf("Waiting for timer ISR ...");

    got_isr = 0;
    while (! got_isr)
    {
        /* busy waiting */
    //}
    printf("Test finished.\n");
    return 0;
}
/*
void malloc_test(int nwords)
{
    int *buf, idx;

    printf("Memory allocation test of %d words:\n", nwords);
    if ((buf = (int *) malloc(nwords*4)) == NULL)
    {
        printf("Error: Out of memory.\n");
        exit(-1);
    }
    printf("The buffer address is: 0x%X\n", (unsigned) buf);
    for (idx = 0; idx < nwords; idx++) buf[idx] = idx;
    for (idx = 0; idx < 10; idx++)
    {
        printf("Addr 0x%X, buf[%d] = %d\n", (unsigned) &(buf[idx]), idx, buf[idx]);
    }
    printf("\n...\n");
    for (idx = 10; idx > 0; idx--)
    {
        printf("Addr 0x%X, buf[%d] = %d\n",(unsigned) &(buf[idx]), nwords-idx, buf[nwords-idx]);
    }
    free(buf);
    printf("Buffer freed.\n");
}*/
