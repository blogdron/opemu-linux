/******************************************************************************
* Copyright © 2012-2023 SINETEK    <philmb3487@proton.me>
* Copyright © 2012-2023 ANV        <>
* Copyright © 2012-2023 BRONZIVKA  <>
*
* Permission is hereby granted, free of charge, to any person obtaining
* a copy of this software and associated documentation files (the
* "Software"), to deal in the Software without restriction, including
* without limitation the rights to use, copy, modify, merge, publish,
* distribute, sublicense, and/or sell copies of the Software, and to
* permit persons to whom the Software is furnished to do so, subject to
* the following conditions:
*
* The above copyright notice and this permission notice shall be
* included in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
******************************************************************************/

#pragma once

#include <linux/ftrace.h>
#include <linux/kallsyms.h>
#include <linux/kernel.h>
#include <linux/linkage.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/version.h>
#include "../libudis86/extern.h"

static inline int
is_saved_state64(struct pt_regs *regs)
{
    uint16_t REG_CS = regs->cs;
    if ((REG_CS & 0x10) == 0x10)
        return 1;
    else
        return 0;
}


struct op {
    // one of either. order here matters.
    union {
        struct pt_regs *state64;
        struct pt_regs *state32;
    };

    enum {
        SAVEDSTATE_64,
        SAVEDSTATE_32,
    } state_flavor;

    // just another version of the above
    struct pt_regs *state;

    // disassembly object
    ud_t        *ud_obj;

    uint8_t    dst64;
    uint8_t    dst32;

    uint64_t    res64;
    uint32_t    res32;
    // boolean flag
    uint8_t        ring0;
};
typedef struct op op_t;

/**
 * Trap handlers, analogous to a program's entry point
 * @param state: xnu's trap.c saved thread state
 */
int opemu_utrap(struct pt_regs *regs);


/**
 * Forward declarations of private xnu functions

extern void mach_call_munger(x86_saved_state_t *state);
extern void unix_syscall(x86_saved_state_t *);
extern void mach_call_munger64(x86_saved_state_t *state);
extern void unix_syscall64(x86_saved_state_t *);
*/
int retrieve_reg(/*const*/ struct pt_regs *regs, const ud_type_t, uint8_t *, uint64_t *);
int store_reg(/*const*/ struct pt_regs *regs, const ud_type_t, uint64_t);

/**
 * Entry points for the "plugins"
 */
extern int op_sse3x_run(op_t*);
extern int op_sse3_run(const op_t*);

