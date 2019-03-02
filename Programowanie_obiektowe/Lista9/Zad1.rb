class Funkcja

	#konstruktor
	def initialize(funkcja = proc {|x| x})
		@funkcja = funkcja
		@N = 10000 #ilosc podzialow
		@h = 0.000001 
	end
	
	#wartosc funkcji
	def value(x)
		@funkcja.call(x)
	end
	
	def zerowe(a,b,e)
		if value(a) * value(b) > 0 
			return nil
		else
			while abs(a - b) > e
				x0 = (a+b)/2.0
				#puts x0 
				if abs(value(x0)) < e 
					return x0
				elsif value(a) * value(x0) < 0
					b = x0
				else
					a = x0
				end
			end
			
			return x0
		end
	end
	
	def pole(a,b) 
		s = 0
		dx = (a - b) / @N;
		
		for i in 1..@N 
			s = s + value(a + i * dx)
		end
		
		s = (s + (value(a) + value(b)) / 2) * dx;
		return s
	end
	
	def poch(x)
		return ( value(x+@h) - value(x-@h) ) / ( 2.0*@h )
	end
	
end

def abs(x)
	if (x < 0) 
		return -x
	else 
		return x
	end
end

pro = proc{|x| x*x*x}

puts "Przyklad uzycia dla f(x)= x^3"
funkcja1 = Funkcja.new(pro)

puts "f(5) = #{funkcja1.value(5)}"
puts "f(-5) = #{funkcja1.value(-3)}"

puts "\nMiejsce zerowe funkcji #{funkcja1.zerowe(-3,5,0.01)}"
puts "f'(5) = #{funkcja1.poch(5.0)}"
puts "f'(-1) = #{funkcja1.poch(-1.0)}"
puts "\nPole pod wykresem od 0 do 1 #{funkcja1.pole(0.0,1.0)}"
puts "\nPochodna w 1: #{funkcja1.poch(1)}"

