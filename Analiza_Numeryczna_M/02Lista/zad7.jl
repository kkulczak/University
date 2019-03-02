f(x) = (x - 3.0)^2.0
f2(x) = 2.0* (x -3.0)

x0 = 1

for i = 1:40
	@printf("%i\t%.4e\n",i,3.0 - x0)
	x0 = x0 - f(x0) / f2(x0)
end	

