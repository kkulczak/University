let square ys = 
	let n = List.length ys 
	in List.for_all (fun x -> List.length x = n) ys


let rec col n mat = List.rev @@ List.fold_left (fun acc x -> ( (List.nth x n)::acc)) [] mat



let rec build_row n = function
	[] -> []
|	x::xs -> List.nth x (n-1) :: build_row n xs

let transposition (ys : 'a list list) = mapi (fun it _ -> col it ys) ys


let rec zip a b = 
	match a,b with
		[],_ -> []
	|	_,[] -> []
	|	x::xs,y::ys -> (x,y) :: zip xs ys

let rec zipf f xs ys  = 
	match (xs,ys) with
		[],_ -> []
	|	_,[] -> []
	|	z::zs,b::bs -> f z b :: zipf f zs bs  
	
let rec mult_vec ys v = List.map (List.fold_left (+) 0) @@ List.map (zipf ( * ) v ) (transposition ys) 


let rec mul a (b : int list list) = 
	match a with
		[] -> []
	|	x::xs -> mult_vec b x :: mul xs b



let m1 = [[1;5;2];[3;2;2];[2;3;9]]
let t1 = square [[1;5];[3;2]]

let t2 = square [[1;5];[3;2];[2;3]]
let t3 = col 2 m1 
let t4 = transposition m1
let t5 = zip [1;2;3] [4;5;6]
let t6 = zipf (+) [1;2;3] [4;5;6]
let t7 = mult_vec  [[2;0];[4;5]] [1;2]
let t8 = mul [[1;2];[3;4]] [[0;1];[0;0]]

