	.text
	.global fib
	.type	fib, @function
	fib:
		cmp	$1,	%rdi
		jle	End
		sub	$24,	%rsp
		mov	%rdi,8(%rsp)
		sub	$1,	%rdi
		call	fib
		mov	%rax,	16(%rsp)
		mov	8(%rsp),%rdi
		sub	$2,	%rdi
		call fib
		add	16(%rsp),%rax
		add	$24,	%rsp
		ret
		End:
		mov	$1,	%rax
		ret
	.size	fib,	.-fib

