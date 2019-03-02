let wielomian l n =
	let rec aux acc = function
		[] -> acc
	|	x::xs -> aux (acc *. n +. x) xs
	in aux 0. l

let wielomian2 ys x = List.fold_left (fun acc y -> acc *. x +. y) 0. ys

let t = wielomian [1.;4.;4.] 3. (* (x+2)^2 *)
let t2 =  wielomian2 [1.;4.;4.] 3.












