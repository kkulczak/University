	.text
	.global clz
	.type clz, @function
clz:
	cmp	$0, %rdi
	je		End
	mov	$32,	%r8
	mov	$32,	%r9
	xor	%rsi,	%rsi
	mov	$0,	%rax
Loopstart:
	shr	%r8
	mov	%rdi,	%r10
	mov	%r9b,	%cl
	shr	%cl,	%r10
	cmp	$0,	%r10
	jne	Else
	mov	$64,	%rax
	sub	%r9,	%rax
	sub	%r8,	%r9
	jmp	Loopend
Else:
	add	%r8,	%r9
Loopend:
	add	$1,	%rsi
	cmp	$7,	%rsi
	jl Loopstart
	ret
End:	
	mov $64, %rax
	ret


