include("interps.jl")

f(x) = 1 / (25 * x * x + 1)

function myerror(w)
  N = 1000
  res = abs(f(-1.) - w(-1.))
  for i=1:N
    temp = abs(f(-1. + (2*i/N)) - w(-1. + (2*i/N)))
    if temp > res
      res = temp
    end
  end
  return res
end

function sredniokwadratowa(w)
  N = 1000
  res = abs(f(-1.) - w(-1.))
  for i=1:N
    temp = abs(f(-1. + (2*i/N)) - w(-1. + (2*i/N)))
    if temp > res
      res = temp
    end
  end
  return res
end

# Rownoodlegle 10
xss = linspace(-1,1,10)
w = interpNewton(xss, map(f,xss))
myerror(w)

#zera czebyszewa
xss = czebyszew_zeroes(10)
w = interpNewton(xss, map(f,xss))
myerror(w)

#punkty ekstyrmalne czebyszewa
xss = czebyszew_extreme(9)
w = interpNewton(xss, map(f,xss))
myerror(w)

#lagrande
w = x -> lagrandePolymonial(9,x)
w(1)
myerror(w)

#czebyszew optymalny
w = x -> czebyszewPolymonial(9,x)
w(0.15)
myerror(w)

``
