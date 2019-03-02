#Kacper Kulczak 279079
#Program do zadania 2.12 na pracownie z przedmiotu Analiza Numeryczna M



#iloraz roznicowy
function il_roz(xs,ys,n)
          b = copy(ys)
        for  j = 1:n
            for k = n : -1 : j 
                b[k+1] = (b[k+1]- b[k-1+1])/(xs[k+1]- xs[k-j+1])
            end
        end
        return b 
end
#Obliczenia wartosci wielomianu interpolowanego w wezlach xs
function inter_wiel(x,xs, iloraz, n)
    temp = 1
    res = iloraz[0+1]
    for i=1:n 
        temp *= (x - xs[i-1+1])
         res += iloraz[i+1] *temp
    end
    return res 
end
#Automat do interpolacji Newtona
function interpNewton(xs,ys)
        n = length(xs)-1
        iloraz = il_roz(xs,ys,n)
        return x -> inter_wiel(x,xs,iloraz,n)
end


#naturalna funkcja sklejana obliczanie macierzy
function spline_matrix(xs, ys,n)
    h = zeros(n+1)
    lambda = zeros(n+1)
    q=zeros(n+1)
    p=zeros(n+1)
    u=zeros(n+1)
    d=zeros(n+1)
    M=zeros(n+1)
    #parametry h[i]
    for k = 1:n 
        h[k+1] = xs[k+1]-xs[k-1+1]
    end
    #parametry lambda[i]
    for k = 0:(n-1) 
        lambda[k+1] = h[k+1] / (h[k+1]+h[k+1+1]) 
    end
    #parametry d[k] (ilorazy różnicowe)
    
    for k = 1 : (n-1)
        #println("it:",k)
        temp =  il_roz( [ xs[k-1+1], xs[k+1], xs[k+1+1] ],   [ ys[k-1+1], ys[k+1], ys[k+1+1]  ]   ,   2)
        d[k+1] = 6 * temp[3]      
    end
    #Wyliczanie M[k] drugiej pochodnej
    for k = 1:(n-1)
        p[k+1] = lambda[k+1] * q[k-1+1] + 2
        q[k+1] = (lambda[k+1] - 1) / p[k+1]
        u[k+1] = (d[k+1] - lambda[k+1] * u[k-1+1]) / p[k+1]
    end
        M[n-1+1]=u[n-1+1]
        for k = (n-2): -1 : 1
            M[k+1]=u[k+1] + q[k+1] *M[k+1+1]
        end
        #=
        println("h: ", h)
        println("l\: ",lambda )
        println("p: ",p)
        println("q: ",q)
        println("u: ",u)
        println("d: ",d)
        println("M: ",M)
        =#
        #@show M
        return  (h,M)
end

#wyliczanie macierzy dla funkcji sklejanych przy krzywej parametrycznej na raz dla x oraz y
function spline_matrix_2(xs,ys,ts,n)
     #  @show n
    h = zeros(n+1)
    lambda = zeros(n+1)
    q=zeros(n+1)
    p=zeros(n+1)
    ux=zeros(n+1)
    uy = zeros(n+1)
    dx=zeros(n+1)
    dy = zeros(n+1)
    Mx=zeros(n+1)
    My=zeros(n+1)
    #parametry h[i]
    for k = 1:n 
        h[k+1] = ts[k+1]-ts[k-1+1]
    end
    #parametry lambda[i]
    for k = 0:(n-1) 
        lambda[k+1] = h[k+1] / (h[k+1]+h[k+1+1]) 
    end
    #parametry dy[k] (ilorazy różnicowe)
    for k = 1 : (n-1)
        temp =  il_roz( [ ts[k-1+1], ts[k+1], ts[k+1+1] ],   [ ys[k-1+1], ys[k+1], ys[k+1+1]  ]   ,   2)
        dy[k+1] = 6 * temp[3]      
    end
    #parametry dx[k] (ilorazy różnicowe )x
    for k = 1 : (n-1)
        temp =  il_roz( [ ts[k-1+1], ts[k+1], ts[k+1+1] ],   [ xs[k-1+1], xs[k+1], xs[k+1+1]  ]   ,   2)
        dx[k+1] = 6 * temp[3]      
    end
    #Wyliczanie M
   for k = 1:(n-1)
        p[k+1] = lambda[k+1] * q[k-1+1] + 2
        q[k+1] = (lambda[k+1] - 1) / p[k+1]
        ux[k+1] = (dx[k+1] - lambda[k+1] * ux[k-1+1]) / p[k+1]
        uy[k+1] = (dy[k+1] - lambda[k+1] * uy[k-1+1]) / p[k+1]
    end
        Mx[n-1+1]=ux[n-1+1]
        My[n-1+1]=uy[n-1+1]
        for k = (n-2): -1 : 1
            Mx[k+1]=ux[k+1] + q[k+1] *Mx[k+1+1]
            My[k+1]=uy[k+1] + q[k+1] *My[k+1+1]
        end
    return  (h,Mx,My)
end
 
 #Wzór naturalnej funkcji sklejanej
function spline_equation(x,xs,ys,h,M,n)
    if x < xs[1] || x >xs[end]
        error("funkcja sklejana nie zdefiniowana dla tego argumentu")
    end
    k=1
    for i=1:n
        if x <= xs[i+1]
            k = i
            break
        end
    end 
    res =  (M[k-1+1] * (xs[k+1]-x)^3 + M[k+1]*((x-xs[k-1+1])^3))/6
    res += (ys[k-1+1]-M[k-1+1]*(h[k+1]^2)/6)*(xs[k+1]-x) 
    res += (ys[k+1]   -M[k+1    ]*(h[k+1]^2)/6)*(x-xs[k-1+1])
    res *= (1 / h[k+1]) 
    return res
end
#Automat do budowania funkcji interpolacyjnej
function interpspline(xs,ys) 
    n =length(xs)-1
    h,m = spline_matrix(xs,ys,n)
    return x-> spline_equation(x,xs,ys,h,m,n)
end
#Oszczedne tworzenie naturalnej funkcji sklejanej dla x i y na raz przy krzywej parametrcznej
function interpSplineParam(xs,ys,ts)
    n = length(xs) - 1
    h,mx,my = spline_matrix_2(xs,ys,ts,n)
return (x->spline_equation(x,ts,xs,h,mx,n), x->spline_equation(x, ts, ys, h, my, n)  )
end

#Automat do interpolacji krzywej parametrycznej
function interpparametric(xs,ys)
    n = length(xs)-1
    ns = [1:(n+1);]
    Xfun = interpspline(ns,xs)
    Yfun = interpspline(ns,ys)
    points =  linspace(1, n+1, 1000)
    return (map(Xfun,points),map(Yfun,points))
end

#Automat do tworzenia wykresow krzywej parametrycznej interpolowanej sklejana funckja naturalna.
#Wyswietla wykres, oraz wykres bledow, i norme 
function make_param_curve(fx,fy,ts,xss, mytitle)
    xs = map(fx,ts)
    ys = map(fy,ts)
    Splinex,Spliney = interpSplineParam(xs,ys,ts)
   #Krzywa parametryczna
    trace1= scatter(;x = map(Splinex, xss) , y =map(Spliney, xss), mode = "lines", name = "Skejana")
    trace2 = scatter(;x = map(fx,xss), y=map(fy,xss), mode= "lines", name="Krzywa Parametryczna" )
    layout1 = Layout(;title=mytitle)
    #Funkcje błedow i ich wykres
    trace3 = scatter(;x = xss , y =map(t-> abs(Splinex(t) - fx(t)), xss), mode = "lines", name = "|Sx(t) - fx(t)|")
    trace4 = scatter(;x = xss , y =map( t-> abs(Spliney(t) - fy(t)), xss), mode = "lines", name = "|Sy(t) - fy(t)|")
    layout2 = Layout(;title="Funkcje błędu")
    #norma w liczbie
    norm =  max(map(t-> sqrt((fx(t)-Splinex(t))^2+(fy(t)-Spliney(t))^2), xss   ) ) 
    return (plot([trace2, trace1],layout1),    plot([trace3,trace4],layout2)      , norm)
end
