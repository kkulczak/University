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
y = f(x)    # 7.709882115452e-01

@printf("f(%.1e)=%.5e\n", x,y);

# Trochę dziwny ten wynik, bo łatwo udowodnić, że f(x) <= 0.5

