f(x) = x ^4
f2(x) = 4.0 * x ^ 3.0

x0 = 1

for i = 1:40
	@printf("%.4e\n",x0)
	x0 = x0 - f(x0) / f2(x0)
end	

