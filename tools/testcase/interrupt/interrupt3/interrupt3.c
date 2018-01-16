/*
 * interrupt 3: Breakpoint
 *
 * (C) 2018.01 BiscuitOS <buddy.zhang@aliyun.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/kernel.h>
#include <test/debug.h>

/*
 * Test Interrupt 3 - int3 
 * Breakpoint Interrupt If you have used a debugger, which you should
 * have by now, you already know the usefulness of inserting breakpoints
 * while debugging a program. The type 3 interrupt is dedicated to the 
 * breakpoint processing. This type of interrupt can be generated by 
 * using the special single-byte form of 'int3' (opcode CCH). Using the
 * 'int3' instruction automatically causes the assembler to encode the 
 * instruction into the single-byte version. Note that the standard encoding
 * for the 'int' instruction is two bytes long.
 * Inserting a breakpoint in a program involves replacing the program 
 * code byte by CCH while saving the program byte for later restoration
 * to remove the breakpoint. The standard 2-byte version of 'int3' can 
 * cause problems in certain situations, as there are instructions that 
 * require only a single byte to encode.
 */
void common_interrupt3(void)
{
    trigger_interrupt3();
}