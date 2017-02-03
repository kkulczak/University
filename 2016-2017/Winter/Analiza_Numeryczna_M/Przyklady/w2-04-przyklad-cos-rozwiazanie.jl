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

f(x) = ( 1.0 - cos(x) ) ./ x.^2

# Zadanie: obliczyć f(1.2e-8)

# Rozwiązanie
x = 1.2e-8

g(x) = 0.5*(sin(x/2.0)/(x/2.0))^2
y = g(x)    # 5.00000e-01

@printf("f(%.1e)=%.5e\n", x,y);
