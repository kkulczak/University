let pochodna = function
	[] -> []
|	y::ys -> 
				let rec aux it = function
					[] -> []
				|	(x::xs) -> (x *. it) :: (aux (it+.1.) xs)
				in aux 1.  ys


let pochodna2 xs = List.tl @@ List.mapi (fun it x -> (x *. float_of_int(it) )) xs

let t1 = pochodna [1.;0.;-1.;2.]	
let t2 = pochodna2 [1.;0.;-1.;2.]	
