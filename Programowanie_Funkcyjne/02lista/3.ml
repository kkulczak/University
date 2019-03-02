let reverse xs=
	let rec temp list acc = 
		match list with
			[] -> acc
			|(h::t) -> temp t (h::acc)
	in temp xs []

let length xs=
	let rec temp xs n =
		match xs with
			[] -> n
			|(h::t) -> temp t (n+1)
	in temp xs 0

let split xs n =
	let rec temp xs acc n =
		if n == 0
		then ( (reverse acc) , xs)
		else let (h::t) =xs in temp t (h::acc) (n-1)
	in temp xs [] n 
		
let cycle xs n = 
	let (x,y) = split xs ((length xs) - n) in y@x

