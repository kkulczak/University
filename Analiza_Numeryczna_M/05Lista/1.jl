f(x) = 1*x*x*x+2*x*x+3*x+4
f1(x) = 3*x*x+4*x+3
f2(x)= 6*x+4 
function Horner(x,list) 
	a = pop!(list)
	b = zero(x)
	b = a + x*b
	a = pop!(list) + x*a
	c = zero(x)
	for  i = 1:length(list)
		c = 2*b + x*c
		b = a + x*b
		a = pop!(list) + x*a
	end
	return (a,b,c)
end
@show test = Horner(2,[4,3,2,1])
@show f(2)	
@show f1(2)
@show f2(2)
