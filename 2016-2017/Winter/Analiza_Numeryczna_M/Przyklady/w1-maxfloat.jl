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
two = Float32(2.0);

d = 32-1;
t = 23;

#
# Obliczanie największej liczby dodatniej w arytmetyce Float32
#
cmax = 2^(d-t-1)-1; # największa cecha

x1 = two^cmax * ( two - two^(-t) )
@printf("najw. dod. liczba w arytm. Float32 = %.1f =\n", x1);

# alternatywny sposób
x2 = prevfloat(typemax(Float32));
@printf("najw. dod. liczba w arytm. Float32 = %.1f\n", x2);

assert( x1==x2 )

#
# Obliczanie najmniejszej liczby dodatniej (subnormalnej) w arytmetyce Float32
#
 # największa cecha
cmin = -2^(d-t-1)+2; # niestety jedna liczba -128 i -127 są już zarezerwowane na (±Inf+NaN i Subnorm)
x1 = two^cmin * two^(-t)
@printf("najm. dod. liczba subnormalna w arytm. Float32 = %.16e\n", x1);
# alternatywny sposób
x2 = nextfloat(float32(0.0));
@printf("najm. dod. liczba subnormalna w arytm. Float32 = %.16e\n", x2);
assert( x1==x2 )
