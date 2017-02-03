Sign =    0x80000000
Exp =     0x7F800000
Mantysa = 0x007FFFFF
RevMantys=0xFF800000
.text
	.global	mulf
	.type	mulf,	@function
mulf:
	xor	%eax,	%eax
	mov	%edi,	%r8d	#Mantysa
	mov	%esi,	%r9d
	and	$Mantysa,%r8d
	and	$Mantysa,%r9d
	mov	%r8d,	%eax
	mul	%r9d
	xor	%r10d,	%r10d
Start:
	mov 	%eax,	%r9d
	and	$RevMantys,%r9d
	je		End
	shr	$1,	%eax
	add	$1,	%r10d
	jmp	Start
End:
	mov	%edi,	%r8d	#Exp
	mov	%esi,	%r9d
	and	$Exp,	%r8d
	and	$Exp,	%r9d
	add	%r8d,	%r9d
	add	%r10d,%r9d
	and	$Exp,	%r9d
	or		%r9d,	%eax
	mov	%edi,	%r8d	#Sign
	mov	%esi,	%r9d
	andl	$Sign,%r8d
	andl	$Sign,%r9d
	add	%r8d,	%r9d
	or		%r9d,	%eax
	ret
	.size	mulf,	.-mulf
