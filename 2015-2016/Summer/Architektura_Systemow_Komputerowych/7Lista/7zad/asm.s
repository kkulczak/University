	.comm tab, 4048, 32
	
	.global main
	.type main, @function
	.text
main:
	movq $0, %rdi				
	movq %rdi, %rax	
	movl $tab, %esi
	movq $4048, %rdx
	syscall
	cmpq $0, %rax
	jne char
	retq 
char:
	movq %rax, %rdx				
	movl $tab, %edi
	movl $0x81, %eax	
	movb (%rdi), %cl 		
	cmpb $0, %cl 			
	je write 
start:
	cmpb	$'a',	%cl
	jge	mala
	cmpb	$'Z',	%cl
	jle	wielka
	jmp next
mala:
	cmpb	$'z',	%cl
	jg		next
	sub	$32,	%cl
	jmp	next
wielka:
	cmp	$'A',	%cl
	jl		next
	add	$32,	%cl
	jmp	next
next:
	movb %cl, (%rdi)		
	incq %rdi 				
	movb (%rdi), %cl 		
	cmpb $0, %cl 			
	jne start
	jmp write
write:
	movq $1, %rax
	movq %rax, %rdi
	movl $tab, %esi
	syscall	
	retq

