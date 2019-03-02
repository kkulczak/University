let rec find_candidate (fst,snd) acc = match snd with
	[] -> (fst,snd, acc) 
|	x::xs -> 
		if List.exists (fun l -> l > acc ) fst 
		then (fst, snd, acc)
		else find_candidate (acc::fst , xs) x

let find_best_replace_and_make_order a value= 
	let rec aux (ys, zs) acc = match ys with
	[] ->  (List.sort (fun i j->j-i) (value::zs)) @ [acc]
|	x::xs ->
		if (x > value) &&  (x < acc)
		then aux (xs, acc::zs) x
		else aux (xs, x::zs) acc
	in let (x::xs) = List.sort (fun i j->j-i) a in aux (xs , [] ) x 

let next ls = 
		if List.sort (fun i j->i-j) ls = ls
		then 	List.sort (fun i j->j-i) ls
		else
			let x::xs = ls in 
			let (a,b,c) = find_candidate ([],xs) x in
			(find_best_replace_and_make_order a c) @ b

let gen a = 
	let rec aux xs fst acc = let ys = next xs in 
		if fst = ys 
		then acc
		else aux ys fst (ys::acc) 
	in List.rev @@ aux a a [a] 


	
let temp =  next [4;3;2;1]
let t4 = find_candidate ([],[4;2;1]) 3
let t6 =  List.map List.rev (gen [4;3;2;1]);;
let t7 = List.sort (fun i j->j-i) [6;4;9]
let t7 = List.sort (fun i j->j-i) [3;2;1] = [3;2;1]
 
