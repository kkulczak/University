let rec map f xs =
	match xs with
		[] -> []
		|(h::t) -> (f h):: (map f t)

let rec sufiks xs =
	if xs = []
	then []
	else let (_::t) = xs in xs:: (sufiks t)
	
let rec prefix xs =
	match xs with
	[] -> []
	|(h::t) -> [h]:: (map (fun ys -> h::ys) (prefix t) ) 
