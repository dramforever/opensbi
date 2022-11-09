/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2020 Western Digital Corporation or its affiliates.
 *
 * Authors:
 *   Anup Patel <anup.patel@wdc.com>
 *   Atish Patra <atish.patra@wdc.com>
 */

#include <sbi/riscv_asm.h>
#include <sbi/sbi_trap.h>
#include <sbi/sbi_error.h>
#include <sbi/sbi_ecall.h>
#include <sbi/sbi_ecall_interface.h>
#include <sbi/sbi_console.h>

static int sbi_ecall_console_handler(unsigned long extid, unsigned long funcid,
				     const struct sbi_trap_regs *regs,
				     unsigned long *out_val,
				     struct sbi_trap_info *out_trap)
{
	int ret = 0;
	switch (extid) {
	case SBI_EXT_0_1_CONSOLE_PUTCHAR:
		sbi_putc(regs->a0);
		break;
	case SBI_EXT_0_1_CONSOLE_GETCHAR:
		ret = sbi_getc();
		break;
	default:
		ret = SBI_ENOTSUPP;
	};

	return ret;
}

static int sbi_ecall_console_probe(unsigned long extid, unsigned long *outval)
{
	switch (extid) {
	case SBI_EXT_0_1_CONSOLE_PUTCHAR:
	case SBI_EXT_0_1_CONSOLE_GETCHAR:
		*outval = sbi_console_get_device() != NULL;
		break;
	default:
		*outval = 0;
	};

	return 0;
}

struct sbi_ecall_extension ecall_console = {
	.extid_start = SBI_EXT_0_1_CONSOLE_PUTCHAR,
	.extid_end   = SBI_EXT_0_1_CONSOLE_GETCHAR,
	.handle	     = sbi_ecall_console_handler,
	.probe	     = sbi_ecall_console_probe,
};
