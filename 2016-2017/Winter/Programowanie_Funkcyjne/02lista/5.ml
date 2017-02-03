let rec map f xs =
	match xs with
		[] -> []
		|(h::t) -> (f h):: (map f t)

let reverse xs=
	let rec temp list acc = 
		match list with
			[] -> acc
			|(h::t) -> temp t (h::acc)
	in temp xs []



