half = Float16(4.71);
float = Float32(4.71);
double = Float64(4.71);

w1(x) = x^3 - convert(typeof(x),6.0)*x^2 + convert(typeof(x),3.0)*x - 0.149;
w2(x) = ((x-convert(typeof(x),6.0))*x + convert(typeof(x),3.0)) * x -0.149;
w1h = ( w1(half) - -14.636489) /  -14.636489;
w1f = ( w1(float) - -14.636489) /  -14.636489;
w1d = ( w1(double) - -14.636489) /  -14.636489;
w2h = ( w1(half) - -14.636489) /  -14.636489;
w2f = ( w1(float) - -14.636489) /  -14.636489;
w2d = ( w1(double) - -14.636489) /  -14.636489;
print(w1(half)); print("\twynik half\n");

print(w1h); print("\t<-w1\n");
print(w2h); print("\n");
print(w1f); print("\t<-w1\n");
print(w2f); print("\n");
print(w1d); print("\t<-w1\n");
print(w2d); print("\n");
print("aletypv23\n");


# cwiczenia





