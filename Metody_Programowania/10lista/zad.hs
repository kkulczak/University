{-# LANGUAGE FlexibleInstances #-}
-- 		Zadanie 1
nat2 :: [(Integer,Integer)]
nat2 = [(x,n-x)|  n <- [0..],x <- [0..n] ]

nat3 :: [(Integer,Integer)]
nat3 = concatMap (\x -> concatMap(\a -> [ (a,x-a) ]) [0..x] ) [0..] 

--			Zadanie 2

merge :: Ord a => ([a],[a])->[a]
merge	([], x) = x
merge (x, []) = x
merge ( (x:xs), (y:ys) )
	| x < y = (x: merge (xs,(y:ys))  )
	| otherwise = (y: merge ((x:xs),ys) )

halve :: [a] -> ([a],[a])
halve x = (take (temp x) x, drop (temp x) x)
	where temp m = div (length m) 2

msort [] = []
msort [x] = [x]
msort xs =
	merge . cross (msort,msort) . halve $ xs

cross :: (a->c, b->d)->(a,b)->(c,d)
cross (f,g) = pair (f . fst, g . snd)
pair :: (a->b, a->c)->a->(b,c)
pair (f,g) x = (f x, g x)
--		Zadanie 3
merge_unique :: Ord a => [a]->[a]->[a]
merge_unique	[] x = x
merge_unique x [] = x
merge_unique  (x:xs) (y:ys) 
	| x < y = (x: merge_unique xs (y:ys)  )
	| x == y = merge_unique xs (y:ys) 
	| otherwise = (y: merge_unique (x:xs) ys )

d235 :: [Integer]
d235 = (1:merge_unique (merge_unique (map (*2) d235) (map (*3) d235)) (map(*5) d235)  )

--		Zadanie 4

msortn :: Ord a => [a] -> Int -> [a]

msortn _ 0 = []
msortn x 1 = [head x]
msortn xs n = merge (msortn xs front, msortn  (drop front xs) back)
	where (front,back) = (n `div` 2, n - front)

msort2 x = msortn x $ length x

--		Zadanie 5

class Monoid a where
	(***)::a->a->a
	e :: a
	infixl 6 ***
	infixr 7 ^^^
	(^^^)::Monoid a => a -> Integer ->a
	(^^^) a 0 = e
	(^^^) a n
		| n < 0 				= error "No"
		| n `mod` 2 == 0 	= half *** half
		| otherwise 		= a *** half *** half
			where half = a ^^^ (n `div` 2) 

instance Monoid Integer where
	(***) n m = (n * m) `mod` 9876543210
	e = 1

--		Zadanie 6

data Mtx2x2 a = Mtx2x2 a a a a deriving Show

instance Monoid (Mtx2x2 Integer) where
	(***) (Mtx2x2 a1 b1 c1 d1) ( Mtx2x2 a2 b2 c2 d2) = Mtx2x2(a1*a2 + b1 * c2) (a1*b2+ b1*d2) (c1*a2+d1*c2) (c1*b2+d1*d2)
	e = Mtx2x2 1 0 0 1

fib :: Integer -> Integer
fib n = temp $ Mtx2x2 0 1 1 1 ^^^ n

temp :: Mtx2x2 Integer -> Integer
temp (Mtx2x2 _ a _ _) = a
















