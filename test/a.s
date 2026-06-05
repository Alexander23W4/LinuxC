	.file	"a.c"
	.option pic
	.text
	.align	2
	.globl	f
	.type	f, @function
f:
	addi	sp,sp,-32
	sw	s0,28(sp)
	addi	s0,sp,32
	sw	a0,-20(s0)
	lw	a5,-20(s0)
	addi	a5,a5,2
	mv	a0,a5
	lw	s0,28(sp)
	addi	sp,sp,32
	jr	ra
	.size	f, .-f
	.globl	a
	.section	.rodata
	.align	2
	.type	a, @object
	.size	a, 4
a:
	.zero	4
	.local	b
	.comm	b,4,4
	.globl	c
	.data
	.align	2
	.type	c, @object
	.size	c, 4
c:
	.word	10
	.text
	.align	2
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-32
	sw	s0,28(sp)
	addi	s0,sp,32
	sw	a0,-20(s0)
	sw	a1,-24(s0)
	lla	a5,b
	lw	a5,0(a5)
	addi	a4,a5,1
	lla	a5,b
	sw	a4,0(a5)
	li	a5,0
	mv	a0,a5
	lw	s0,28(sp)
	addi	sp,sp,32
	jr	ra
	.size	main, .-main
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0"
	.section	.note.GNU-stack,"",@progbits
