/* SPDX-License-Identifier: BSD-2-Clause */

#include <sbi/sbi_byteorder.h>

#ifdef CONFIG_FW_HEADER_LINUX

	/*
	 * Compatibility with Linux kernel image header, for fw_jump and fw_payload
	 *
	 * See: https://www.kernel.org/doc/html/v6.8/arch/riscv/boot-image-header.html
	 */

	.section .header, "a", %progbits

	/* 8 bytes at beginning reserved for code */
	j _start
	.align 3

	/* We want to be loaded at start of RAM, so text_offset is 0 */
	.dword 0					/* text_offset */
	.dword cpu_to_le64(_fw_reloc_end - _fw_start)	/* image_size */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	.dword 0					/* flags: Not big-endian */
#else
	.dword 1					/* flags: Big-endian */
#endif
	.word cpu_to_le16(0x0002)			/* version (0.2) */
	.word 0						/* res1 */
	.dword 0					/* res2 */
	.ascii "RISCV\0\0\0"				/* magic */
	.ascii "RSC\x05"				/* magic2 */
	.word 0						/* res3 */

#endif /* CONFIG_FW_HEADER_LINUX */
