	.file	"bubble_sort.c"
	.text
	.globl	bubbleSort
	.def	bubbleSort;	.scl	2;	.type	32;	.endef
	.seh_proc	bubbleSort
bubbleSort:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	movl	%ecx, 16(%rbp)
	movq	%rdx, 24(%rbp)
	movq	%rsp, %rax
	movq	%rax, %r8
	movl	16(%rbp), %eax
	subq	$1, %rax
	movq	%rax, -32(%rbp)
	movl	16(%rbp), %eax
	salq	$2, %rax
	addq	$15, %rax
	shrq	$4, %rax
	salq	$4, %rax
	call	___chkstk_ms
	subq	%rax, %rsp
	movq	%rsp, %rax
	addq	$3, %rax
	shrq	$2, %rax
	salq	$2, %rax
	movq	%rax, -40(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L2
.L3:
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	24(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %ecx
	movq	-40(%rbp), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	movl	%ecx, (%rax,%rdx,4)
	addl	$1, -4(%rbp)
.L2:
	movl	-4(%rbp), %eax
	cmpl	16(%rbp), %eax
	jb	.L3
	movl	$0, -8(%rbp)
	jmp	.L4
.L8:
	movl	$0, -12(%rbp)
	jmp	.L5
.L7:
	movl	-12(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	24(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %edx
	movl	-12(%rbp), %eax
	cltq
	addq	$1, %rax
	leaq	0(,%rax,4), %rcx
	movq	24(%rbp), %rax
	addq	%rcx, %rax
	movl	(%rax), %eax
	cmpl	%eax, %edx
	jle	.L6
	movl	-12(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	24(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	movl	%eax, -44(%rbp)
	movl	-12(%rbp), %eax
	cltq
	addq	$1, %rax
	leaq	0(,%rax,4), %rdx
	movq	24(%rbp), %rax
	addq	%rdx, %rax
	movl	-12(%rbp), %edx
	movslq	%edx, %rdx
	leaq	0(,%rdx,4), %rcx
	movq	24(%rbp), %rdx
	addq	%rcx, %rdx
	movl	(%rax), %eax
	movl	%eax, (%rdx)
	movl	-12(%rbp), %eax
	cltq
	addq	$1, %rax
	leaq	0(,%rax,4), %rdx
	movq	24(%rbp), %rax
	addq	%rax, %rdx
	movl	-44(%rbp), %eax
	movl	%eax, (%rdx)
.L6:
	addl	$1, -12(%rbp)
.L5:
	movl	-8(%rbp), %eax
	movl	16(%rbp), %edx
	subl	%eax, %edx
	leal	-1(%rdx), %eax
	movl	-12(%rbp), %edx
	cmpl	%eax, %edx
	jb	.L7
	addl	$1, -8(%rbp)
.L4:
	movl	16(%rbp), %eax
	subl	$1, %eax
	movl	-8(%rbp), %edx
	cmpl	%eax, %edx
	jb	.L8
	movl	$0, -16(%rbp)
	movl	$0, -20(%rbp)
	jmp	.L9
.L11:
	movq	-40(%rbp), %rax
	movl	-20(%rbp), %edx
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %edx
	movl	-20(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rcx
	movq	24(%rbp), %rax
	addq	%rcx, %rax
	movl	(%rax), %eax
	cmpl	%eax, %edx
	je	.L10
	addl	$1, -16(%rbp)
.L10:
	addl	$1, -20(%rbp)
.L9:
	movl	-20(%rbp), %eax
	cmpl	16(%rbp), %eax
	jb	.L11
	movl	-16(%rbp), %eax
	movq	%r8, %rsp
	movq	%rbp, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (Rev8, Built by MSYS2 project) 15.2.0"
