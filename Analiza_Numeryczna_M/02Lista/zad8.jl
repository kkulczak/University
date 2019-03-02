
set_bigfloat_precision(128)
temp = BigFloat(0)
f(x) = exp(-x) - sin(x)
steffensen(c) = c - (f(c)*f(c))/( f(c+f(c)) - f(c) )
temp2 = BigFloat(100)

witch = big"0.588532743981861077432452045702903688531271516109030533319914299511672553307351427738524061576027409562153528176982466770293849745782742957500713135"


for i = 1:10
	temp2 = temp
	temp = steffensen(temp)
	@printf("%.4e\t%.4e\n", temp , abs(temp - witch) )
end


