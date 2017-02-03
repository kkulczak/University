
set_bigfloat_precision(128)
function c(x) 
	if x == 2  
		return BigFloat(0.0)
	else 
		return sqrt( (BigFloat(1.0) + c(x-1)) / BigFloat(2.0 ) ) 
	end
end

function s(x) 
	if x == 2  
		return BigFloat(1.0)
	else
		return sqrt( (BigFloat(1.0) - c(x-1)) / BigFloat(2.0 )) 
	end
end

P(x) = BigFloat( 2.0) ^ (x - BigFloat(1.0)) * s(x)

data = 2
for i = 2:2*128
	@printf("%i: %1e\n",i,P(data))
	data = data +1
end

