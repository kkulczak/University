using Polynomials
set_bigfloat_precision(128)
function Baristowa(n,r,s, a,  iter )
	b = zeros(typeof(r), n+1)
	c = zeros(typeof(r), n+1)
	for j = 1:iter 
		b[n+1] = a[n+1]
		b[n-1+1] = a[n-1+1]+ r*b[n+1]
		c[n+1] = b[n+1]
		c[n-1+1]= b[n-1+1] + r*c[n+1]
		for i = n-2:-1:0
			b[i+1]= a[i+1] + r*b[i+1+1] + s*b[i+2+1]
			c[i+1] = b[i+1] + r*c[i+1+1] + s*c[i+2+1]
	end
	J = [	c[2+1]	c[3+1];
			c[1+1]	c[2+1]];
	B = [-b[1+1]; -b[0+1]]
	res = \(J,B)
	r += res[1]
	s += res[2]
	end
	return (r,s)
end

(r,s) = Baristowa(4,BigFloat(0.1),BigFloat(0.1),[BigFloat(1.):BigFloat(5.);], 10)


@printf("z^2  %.16f*z - %.16f \n",r,s)
@show ((r+sqrt(complex(r*r+BigFloat(4.)*s)))/BigFloat(2.))

roots(Poly([1.:5.;]))
