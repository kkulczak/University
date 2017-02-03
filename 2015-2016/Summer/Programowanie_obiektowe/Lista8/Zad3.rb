
class Jawna
	def initialize(wiadomosc)
		@wiadomosc = wiadomosc
	end
	
	def zaszyfruj(klucz)
	    szyfrogram = ""
		for i in 0...@wiadomosc.length
			znakszyf = @wiadomosc[i].ord + klucz
				znakszyf = (znakszyf % 256) unless znakszyf < 256
			szyfrogram[i] = znakszyf.chr
		end
		return  Zaszyfrowane.new(szyfrogram)
	end
	def to_s
		 @wiadomosc.to_s
	end
end

class Zaszyfrowane
	def initialize(szyfrogram)
		@szyfrogram = szyfrogram
	end
	def odszyfruj(klucz)
		deszyfr = ""
		for i in 0...@szyfrogram.length
			znakszyf = @szyfrogram[i].ord - klucz
					znakszyf += 256 unless znakszyf > 0
		  deszyfr[i] = znakszyf.chr
		end
		return Jawna.new(deszyfr)
	end
	def to_s
		@szyfrogram.to_s
	end
end	
#-----------------
puts "Podaj wiadomosc"
wiadomosc = gets.chomp

puts "Podaj przesuniecie"
k = gets.chomp.to_i


inf = Jawna.new(wiadomosc)
szyfrinf = inf.zaszyfruj(k)

puts "Podana wiadomosc #{inf}"
puts "Zaszyfrowana wiadomosc #{szyfrinf} "
puts "Odszyfrowana wiadomosc #{szyfrinf.odszyfruj(k)} "

