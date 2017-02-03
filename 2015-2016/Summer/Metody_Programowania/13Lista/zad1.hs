import qualified Data.List as List
import Control.Monad
--Zadanie 1

generate :: Int -> [[Int]]
generate n = do
	x <- List.permutations [0..n-1]
	guard (check (+) x == n && check (-) x == n) -- niech ten warunek to px)
	return x	

-- () -to unit, 
{-
guard :: MonadPlus m => Bool -> m() -- m = []
guard True 	= return () -- =[()]
guard False	= mzero		-- =[]
-}
--Przepisz generate bez notacji do
generate1 n = List.permutations [0..n-1] >>= (\x -> guard (p x) >>= (\_ ->return x))

generate2 n = concatMap (\x -> concatMap(\_ -> [x])(guard(p x))) (List.permutations [0..n-1])
































