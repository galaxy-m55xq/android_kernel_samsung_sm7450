/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _ASM_X86_LINKAGE_H
#define _ASM_X86_LINKAGE_H

#include <linux/stringify.h>

#undef notrace
#define notrace __attribute__((no_instrument_function))

#ifdef CONFIG_X86_32
#define asmlinkage CPP_ASMLINKAGE __attribute__((regparm(0)))
#endif /* CONFIG_X86_32 */

#ifdef __ASSEMBLY__

#if defined(CONFIG_X86_64) || defined(CONFIG_X86_ALIGNMENT_16)
#define __ALIGN		.p2align 4, 0x90
#define __ALIGN_STR	__stringify(__ALIGN)
#endif

#if defined(CONFIG_RETHUNK) && !defined(__DISABLE_EXPORTS) && !defined(BUILD_VDSO)
#define RET	jmp __x86_return_thunk
#else /* CONFIG_RETPOLINE */
#ifdef CONFIG_SLS
#define RET	ret; int3
#else
#define RET	ret
#endif
#endif /* CONFIG_RETPOLINE */

#else /* __ASSEMBLY__ */

#if defined(CONFIG_RETHUNK) && !defined(__DISABLE_EXPORTS) && !defined(BUILD_VDSO)
#define ASM_RET	"jmp __x86_return_thunk\n\t"
#else /* CONFIG_RETPOLINE */
#ifdef CONFIG_SLS
#define ASM_RET	"ret; int3\n\t"
#else
#define ASM_RET	"ret\n\t"
#endif
#endif /* CONFIG_RETPOLINE */

#endif /* __ASSEMBLY__ */

#define __CFI_TYPE(name)					\
	SYM_START(__cfi_##name, SYM_L_LOCAL, SYM_A_NONE)	\
	.fill 11, 1, 0x90 ASM_NL				\
	.byte 0xb8 ASM_NL					\
	.long __kcfi_typeid_##name ASM_NL			\
	SYM_FUNC_END(__cfi_##name)

/* SYM_TYPED_FUNC_START -- use for indirectly called globals, w/ CFI type */
#define SYM_TYPED_FUNC_START(name)				\
	SYM_TYPED_START(name, SYM_L_GLOBAL, SYM_A_ALIGN)

#endif /* _ASM_X86_LINKAGE_H */

