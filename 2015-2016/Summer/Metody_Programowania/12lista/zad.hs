--	Zadanie 1
--a)
perma [] = [[]]
perma (x:xs) = concatMap (inserta x) (perma xs)

inserta x [] = [x]
inserta x l@(y:ys) = [x:l] ++ (map (y) (inserta ys))

--b)
permb [] = [[]]
permb (x:xs) = [zs| ys <- permb xs, zs <- insertb x ys]

insertb 




