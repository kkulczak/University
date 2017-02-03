import Control.Monad

--newtype StateComput s a = SC (s -> (a,s))
{-
instance Monad (StateComput s) where		-- class Monad m where
	return x = SC (\s -> (x,s))			-- return :: a -> ma
	(SC c) >>= g = SC (\s ->				-- (>>=) :: ma -> (a -> mb) -> mb 
		let 	(x, s') = c s 
				SC c' = g	x
		in c' s')	
-}												
newtype StateComput s a = SC {runSC :: s -> (a,s)} 
--runSC :: StateComput s a -> (s -> (a,s))
--runSC (SC c) = c

instance Monad (StateComput s) where
	return x = SC (\s -> (x,s))
	m >>= g = SC (\s -> 
		let (x, s') = runSC m s
		in runSC (g x) s' )
		
		
--zadanie 3		
newtype SStateComput a = SSC(String->(a,String))

instance Monad (SStateComput s) where
	return x = SSC (\s -> (x,s))
	(SSC c)>>= g = SSC (\s -> 
		let (x, s') = c s
			SSC c' = g x
		in c' s'
		
		
runSSC :: SSC a-> String -> a
runSSC (SSC c ) s = let (r,_) = c s in r

getc :: SSC Char 
--getc SSC c = SSC 
getc= SSC(\(x:xs)->(x,xs))

ungetc:: Char-> SSC()
ungetc c = SSC(\s->((),c:s))


isEOS:: SSC Bool
isEOS = SSC(\s->(null s,s))
























