/* CS100 Fall 2026 - HW2 Problem 5: CPU emulator
 *
 * Emulate a toy CPU with registers x0..x5 (16-bit signed, x0 always 0)
 * executing add/sub/mul/div/let/print instructions read as hex words.
 * Do not use <math.h>. Do not rename this file.
 */
#include <stdio.h>

#define NUM_REGS 6

/* Wrap an int into the range of a 16-bit signed integer (two's complement),
 * without relying on implementation-defined conversions. */
static int wrap16(int value)
{
    int v = value & 0xFFFF;
    if (v >= 0x8000)
        v -= 0x10000;
    return v;
}

int main(void)
{
    int regs[NUM_REGS] = {0};
    int n;

    if (scanf("%d", &n) != 1)
        return 0;

    for (int line = 0; line < n; ++line) {
        unsigned int code;
        if (scanf("%x", &code) != 1)  /* %x accepts the "0x" prefix */
            break;

        /* Layout: [15:13] opcode | [12:10] r1 | [9:7] r2 | [6:0] imm */
        unsigned int opcode = (code >> 13) & 0x7;
        unsigned int r1 = (code >> 10) & 0x7;
        unsigned int r2 = (code >> 7) & 0x7;
        int imm = (int)(code & 0x7F);

        int a = r1 < NUM_REGS ? regs[r1] : 0;
        int b = r2 < NUM_REGS ? regs[r2] : 0;
        int result = a;
        int writes = 1;

        switch (opcode) {
        case 0: result = a + b; break;        /* add */
        case 1: result = a - b; break;        /* sub */
        case 2: result = a * b; break;        /* mul */
        case 3: result = a / b; break;        /* div, C truncates toward zero */
        case 4: result = imm; break;          /* let */
        case 5:                               /* print */
            printf("x%u = %d\n", r1, a);
            writes = 0;
            break;
        default:
            writes = 0;
            break;
        }

        if (writes && r1 != 0 && r1 < NUM_REGS)
            regs[r1] = wrap16(result);
    }
    return 0;
}
