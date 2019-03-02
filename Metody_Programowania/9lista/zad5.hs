roots :: (Double, Double, Double) -> [Double]
roots (a,b,c) = 
	if delta (a,b,c) < 0 
	then [] 
	else (
		if delta (a,b,c) == 0 
			then[(-b) / (2*a)] 
			else [(-b +  (delta (a,b,c)))/(2*a),(b + ( delta (a,b,c)))/((-2)*a)]    )

delta :: (Double, Double, Double) -> Double
delta (a,b,c) = b * b - 4 * a *c

fib:: Integer -> Integer
fib 0 = 1
fib 1 = 1
fib n = fib (n-1) + fib (n-2)


