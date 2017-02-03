.text
	.global insert_sort
	.type	insert_sort, @function
insert_sort:
		push %r12
		mov %rdi,	%r11
		Loop:
		add	$8,	%r11
		mov	%r11,	%r12
		SecLoop:
		Debug:
		mov	(%r12),	%r8
		mov	%r12,		%r9
		sub	$8,		%r9
		mov	(%r9),	%r10
		cmp	%r8,	%r10
		jl	Else
		mov	%r10,	(%r12)
		mov	%r8,	(%r9)
		Else:
		sub	$8,	%r12
		cmp	%rdi,	%r12
		jg	SecLoop
		cmp	%r11,	%rsi
		jg	Loop
		pop %r12
		ret
	.size insert_sort, .-insert_sort


