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
# Wyganae pakiety:
# sudo apt-get install python python-matplotlib python3-matplotlib
##############################

Pkg.add("PyPlot")
using PyPlot

f(x) = ( 1.0 - cos(x) ) ./ x.^2

x = linspace(0,2*pi,1000);
y = f(x);
PyPlot.plot(x, y, color="red", linewidth=2.0, linestyle="--")
PyPlot.show()

for x = [ 4.0 3.0 2.0 1.50 1.30 1.15 1.10 1.05 1.01 1.00 ]*1e-8
  y = f(x);
  @printf("f(%.2e) = %.2e\n", x, y);
end




