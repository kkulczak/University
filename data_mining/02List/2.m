
d = 100;
N = 1000;
M = 1000;

X = rand(d, N);
Y = rand(d, M);
tic
a = sqrt(- 2 * transpose(Y) * X + sum(X .* X) + transpose(sum(Y .* Y)));
toc

d = 100;
N = 10000;
M = 1000; 


X = rand(d, N);
Y = rand(d, M);
tic
b = sqrt(- 2 * transpose(Y) * X + sum(X .* X) + transpose(sum(Y .* Y)));
toc