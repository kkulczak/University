	.text
	.global lcm_gcd
	.type lcm_gcd, @function
lcm_gcd:
	mov %rdi,	%r8
	mov %rsi,	%r9
	cmp %r9,	%r8
	je	.End
.Start:
	cmp %r8,	%r9
	jge .Else
	sub %r9,	%r8
	jmp .AfterElse
.Else:
	sub %r8,	%r9
.AfterElse:
	cmp %r9,	%r8
	jne .Start
.End:
	mov	%rsi,	%rax
	xor	%rdx,	%rdx
	div	%r8
	mul	%rdi
	mov	%r8,	%rdx
	ret
.size lcm_gcd, .-lcm_gcd


