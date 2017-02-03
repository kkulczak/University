for n = 1:10
	if eu / factorial(n+1) / 2^n <= 1./10.^5
		@show n
		break
	end
end