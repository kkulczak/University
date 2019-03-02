type 'a place =
	Place of 'a list * 'a list
	
let findNth xs n =
	let rec aux (xs,ys) num = 
		if num = n
		then (xs,ys)
		else aux ((List.hd ys)::xs , List.tl ys) (num+1)
	in 
	if n >= List.length xs
	then failwith "poza zakresem tablicy"
	else
		let (a,b) =  (aux ([],xs) 0) in
		Place (a,b)
		
let list = [1;2;3;4;5;6]
let t1 = findNth list 4

let collapse x = 
	let rec aux = function
		Place([],xs) -> xs
	|	Place(a::xs,ys) -> aux (Place(xs,a::ys))
	in
	aux x
	
let t2 = collapse t1

let add x (Place(xs,ys)) = Place(xs,x::ys)
let del (Place(xs,ys)) = 
	if ys = []
	then failwith "Poza zakresem Tablicy"
	else Place(xs, List.tl ys)
	
let t3 = collapse (add 3 (findNth [1;2;4] 2))  
let t4 = collapse (del (findNth [1;2;4] 2)) 
let t5 = del (add 10 t1)

let next (Place(xs,ys)) = 
	if ys = []
	then failwith "Poza zakresem Tablicy"
	else Place( (List.hd ys)::xs , List.tl ys )

let prev (Place(xs,ys)) =
	if xs=[]
	then failwith "Poza zakresem Tablicy"
	else 
		let z::zs = xs in 
		Place( zs, z::ys)
	
	
	
	
	
	
