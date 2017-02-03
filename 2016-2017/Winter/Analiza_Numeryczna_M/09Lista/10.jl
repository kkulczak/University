using Plotly;
include("../interps.jl")
f(x) = 2016x^7 + 12x^5 +x^4 + x^3 + x^2 + x + 1


xs = linspace(-1,1, 6)
Newton = interpNewton(xs,map(f,xs))

xss = linspace(-1,1, 10000)
trace1 = scatter(;x=xss, y= map(Newton,xss), name="Newton")
trace2 = scatter(;x=xss, y=  map(f        ,xss), name="f")
plot([trace1, trace2])

#zera czebyszewa
k = 6
xs = []
for i = 0:(k-1)
push!(xs, cos(pi*(2*i+1)/(2*k) ))
end
xs = sort(xs)
@show xs

Newton = interpNewton(xs,map(f,xs))

xss = linspace(-1,1, 10000)
trace1 = scatter(;x=xss, y= map(Newton,xss), name="Newton")
trace2 = scatter(;x=xss, y=  map(f        ,xss), name="f")
plot([trace1, trace2])
