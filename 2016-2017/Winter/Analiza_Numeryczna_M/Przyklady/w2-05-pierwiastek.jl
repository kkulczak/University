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
a = 1.0
b = 9999999.0
c = 1.0e4

f(x) = a*x^2+b*x+c

Δ=b^2-4.0*a*c

x1 = (-b - sqrt(Δ)) / (2.0*a)
x2 = (-b + sqrt(Δ)) / (2.0*a)

@show f(x1)
@show f(x2)


x2prime = c/(a*x1)
f(x2prime)

@printf("x2 =%.16f\n", x2);
@printf("x2'=%.16f\n", x2prime);
