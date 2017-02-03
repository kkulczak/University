import qualified Data.List as L


ssm :: [Integer] -> [Integer]
ssm xs =  reverse( foldl f [] xs) 

f :: [Integer] -> Integer -> [Integer]
f [] x = [x] 
f (y:ys) x
	|	y < x			=	(x:y:ys)
	|	otherwise =	(y:ys)


{-
	
length1 = foldr (\ _ x -> x + 1) 0 
length2 :: [a] -> Int
length2 = foldl (\ x _ -> x + 1) 0
(+++) = flip $ foldr (:)
concat1 = foldr (++) []
reverse1 = foldl (flip (:)) []
sum1 = foldl (+) 0
-}


length1 xs = foldr (\x acc -> acc + 1) 0 xs
length2 xs = foldl (\acc x -> acc + 1) 0 xs
acc = L.tails [1,2,3,4]

--	Zadanie 6 
g1 x = map -1 x	
g2 x =  map (-1) x
g3 x = [x] : [1]
g4 x = x * sin .1

ones = 1: ones
test = let f [] = 0; f (_:xs) = 2 + f xs in f ones
	
