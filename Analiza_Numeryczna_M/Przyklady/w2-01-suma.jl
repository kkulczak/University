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

wartoscDokladna_1e5 = 1.6449240668982262698057485033127;
wartoscDokladna_1e6 = 1.6449330668487264363057484999794;
wartoscDokladna_1e7 = 1.6449339668482314364722484999793;
wartoscDokladna_1e8 = 1.6449340568482264864724149999793;
wartoscDokladna_1e9 = 1.6449340658482264369724151664793;

real = Float32

function algorytm1(n)
  suma = zero(real);
  for k = 1:1:n
    suma = suma + one(real)/convert(real, k)/convert(real,k);
  end
  return suma
end

function algorytm2(n)
  suma = zero(real);
  for k = n:-1:1
    suma = suma + one(real)/convert(real, k)/convert(real,k);
  end
  return suma
end


function doTest(x, algorytm, n)
  println(algorytm, " n=", n)
  @printf("Wynik dokładny  = %.16f\n", x);
  y = algorytm(n);
  @printf("Wynik obliczony = %.16f   błąd względny = %.3e\n", y, abs(x-y)/x);
end

doTest(wartoscDokladna_1e5, algorytm1, 1e5);
doTest(wartoscDokladna_1e5, algorytm2, 1e5);

doTest(wartoscDokladna_1e6, algorytm1, 1e6);
doTest(wartoscDokladna_1e6, algorytm2, 1e6);


@printf("Precyzja arytmetyki = %.3e\n", 0.5*eps(real));
