let rec merge cmp l1 l2 = 
	match (l1,l2) with
	([],a) -> a
	|(a,[]) -> a
	|((h1::t1), (h2::t2)) ->
		if cmp h1 h2
		then h1::(merge cmp t1 l2)
		else h2::(merge cmp l1 t2)
