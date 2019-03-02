x = rand(100, 1);
y = rand(100, 1);
w = rand(100, 1);
% 1
z21 = sqrt(sum(x .* x));
% 2
z22 = sum(x .* w) / sum(w);
% 3
z23 = sqrt(transpose(x - y) * (x - y));
% 4
z24 = transpose(x) * y;

% b1)
N = 1000;
d = 100;
X = rand(d, N);
y = rand(d,1);
w = rand(d,1);
zwb1 = sqrt(sum(X .* X));
zwb2 = sum(X .* d) / sum(d);
zwb3 = sqrt(sum((X - d ) .* (X - d)));
zwb4 = (transpose(d) * X);
