let palindrom zs = 
	let rec aux2 = function
		|	xs,[] -> (xs,[],true)
		|	xs, y::ys -> 
			let (h1::cala, krotsza, bool) = aux2 (xs,ys) in
			(cala,krotsza ,bool && h1=y) 
	in
	let rec aux = function
	|	xs,[] ->  aux2 (zs, xs)
	|	xs,[_] -> aux2 (zs, List.tl xs)
	|	_::xs,_::_::ys -> aux (xs, ys)
	in  
	let (_,_,a) = (aux (zs,zs)) in a



let test1 = palindrom [1;2;3;2;1]
let test2 = palindrom [1;2;3;1;1]
let test3 = palindrom [1;2;2;1]
let test4 = palindrom [1;2;3;1]
