class Fixnum
	def prime
		if self <= 1
			return true;
		elsif self <= 3
			return true
		elsif (self % 2 == 0)
			return false
		else
			i = 5
			while i*i <= self 
				if (self % i == 0)
					return false
				end
				i+=2
			end
		return true
		end
	end
	
	def ack (y)
		if self == 0
			return y + 1
		elsif y == 0
			return (self - 1).ack(1)
		else
			return (self - 1).ack(self.ack(y-1))
		end
	end
	
	def doskonala
		sumaDzielnikow = 0
		for i in 1.. self/2
         if (self % i) == 0
				sumaDzielnikow += i
			end
		end
		
		if self == sumaDzielnikow
			return true
		else
			return false
		end
	end
	
	def slownie
		znak = ["zero","jeden","dwa","trzy","cztery","piec","szesc","siedem","osiem","dziewiec"]
		wyrazenie = ""
		selfcopy = self
		while selfcopy >= 10
			temp = selfcopy%10
			wyrazenie = znak[temp] + " " + wyrazenie
			selfcopy = selfcopy/10
		end
		return znak[selfcopy] + " " + wyrazenie
	end
end


#------------------------
for i in 2..10
	puts "Pierwszosc liczby #{i} - #{i.prime}"
end


puts "Funkcja Ackermanna (1, 1) - #{1.ack(1)}"
puts "Funkcja Ackermanna (2, 1) - #{2.ack(1)}"
puts "Funkcja Ackermanna (1, 2) - #{1.ack(2)}"
puts "Funkcja Ackermanna (2, 2) - #{2.ack(2)}"
puts "Funkcja Ackermanna (3, 5) - #{3.ack(5)}"


puts "Liczby doskonale z przedzialu 2 - 1000"
for i in 2..1000
	if i.doskonala
		puts "#{i} jest doskonala!"
	end
end



puts "#{234} = #{234.slownie}"
puts "#{313} = #{313.slownie}"
puts "#{666} = #{666.slownie}"
puts "#{979} = #{979.slownie}"
puts "#{1234} = #{1234.slownie}"
puts "#{10905} = #{10905.slownie}"
