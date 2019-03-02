##########################################################
# Rafał Nowak
#
# Instytut Informatyki
# Uniwersytet Wrocławski
#
#
# Pomocniczne materiały do wykładu z analizy numerycznej
#
##########################################################

# Arytmetyka pojedynczej precyzji
# Float32  (float w języku C)
x = 1.0f0
y = 0.5f-8
typeof(x)
typeof(y)

# Domyślnie używana jest arytmetyka podwójnej precyzji,
# Float64  (double w języku C)
x = 1.0;
y = 2.0e-7;
typeof(x)
typeof(y)

# Konwersja to wybranego typu
x = Float32( 1.0 )
y = Float64( 1.0 )
typeof(x)
typeof(y)

function test(x, n = 10^9)
  y = zero(typeof(x)); # funkcja zero( .. ) zwraca zero w odpowiedniej arytmetyce
  for i=1:n
    y = y+x;
  end
  y
end

tic()
x=test( Int32(1) , 10^8); # ok. 6 sekund
toc()
tic()
x=test( Int64(1) , 10^8); # ok. 6 microsekund
toc()
tic()
x=test( 1.0f-5 , 10^9 );  # ok. 1 sek.
toc()
tic()
x=test( 1.0e-5 , 10^9 );  # ok. 1 sek., ale zupełnie inny wynik
toc()


# Reprezentacja zmiennopozycyjna
(s,c,m) = ( 1.0,
           -5,
           1.0 + 2.0^(-3) + 2.0^(-5) ) # s-znak, c-cecha, m-mantysa

x = s*2.0^c*m;
typeof(x)

repr = bits(x); # bits zwraca reprezentację binarną
rs = repr[1];
rc = repr[2:2+11-1];
rm = repr[2+11:end]
@printf("Reprezentacja liczby x = %f  to\n%c|%s|%s\n", x, rs,rc,rm);

tmp = bits( c+1023 );
@printf("  %s  - reprezentacja binarna liczby całkowitej c+1023  (c=%d)\n", tmp[end-10:end], c);

#####
# (s,c,m) = (1.0, 1024, 1.5)  =>  NaN, np. x = 1.0 / 0.0
# (s,c,m) = (1.0, 1024, 1.0)  =>  Inf
# println(bits(NaN))
# println(bits(Inf))
# println(bits(e64))
##########################################################
x = Float16(1.3); # Half precision (16 bits)
@printf("Wartość 1.3 w arytmetyce 16 bitowej = %c.8f  = %.8f\n",  '%', x);  # 1.29980469
@printf("Wartość 1.3 w arytmetyce 16 bitowej = %c.16f = %.16f\n", '%', x);  # 1.2998046875000000
##########################################################
# Obliczanie *precyzji arytmetyki*
# one - wartość 1.0 w danej arytmetyce
# Przykład:  myeps( float16 )
function myeps(ftype = float64)
  one = ftype(1.0);
  two = ftype(2.0);
  x   = one;
  while x+one>one
    x=x/two;
  end;
  return x;
end

e16 = myeps( Float16 );
e32 = myeps( Float32 );
e64 = myeps( Float64 );

@printf("Precyzja arytmetyki float16 = %.4e\n", e16);
@printf("Precyzja arytmetyki float32 = %.4e\n", e32);
@printf("Precyzja arytmetyki float64 = %.4e\n", e64);

# Julia ma wbudowaną funkcję eps(...)
# help("Base.eps");
# Wniosek:  2*myeps = eps
2.0*e32 == eps(Float32(1.0))

t = 10; # +1 oznacza jeden dodatkowy bit mantysy w standardzie IEEE 754
e16 == 0.5 * 2.0^(-t)

for (ftype,t) in [ (Float16,10), (Float32,23), (Float64,52) ]
  assert( myeps(ftype) == 0.5 * 2.0 ^ (-t) );
end;
