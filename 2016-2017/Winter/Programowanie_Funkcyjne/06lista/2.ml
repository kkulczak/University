type 'a btree = 
	| Leaf of 'a
	| Node of 'a btree * 'a * 'a btree
	|Empty

type  'a mtree = MNode of  'a  * 'a forest
and 'a forest = EmptyForest | Forest of 'a mtree * 'a forest

let dfs_num  tree =
	let rec dfs tree num = match tree with
		| Leaf _ -> (Leaf num, num + 1)
		| Node (left, _ , right ) ->
			let (left_tree, num2)  = dfs left (num+1) in
			let (right_tree, num3) = dfs right (num2) in
			(Node(left_tree, num, right_tree) , num3) in
	fst @@ dfs tree 1;;

let t1 = Node(Node(Leaf 'a', 'b', Leaf 'c'), 'd', Leaf 'e')
let test1 =  dfs_num t1 


type 'a kolejka = Kol of 'a list * 'a list 
let push el kol = let Kol(xs,ys) = kol in  Kol (xs, el::ys)
let push2 el1 el2 kol = let Kol(xs,ys) = kol in Kol(xs, el2::el1::ys)
let rec take = function 
| Kol([],[]) -> failwith "empty kolejka" 
| Kol([], xs) -> take  @@ Kol(List.rev xs, [])
| Kol(y::ys,xs) -> (y,  Kol(ys,xs) )
let empty kol = kol = Kol([],[])

let rec step kol  num= 
	if empty kol
then []
else
	let tree,kol1 = take kol in
	match tree with
	| Leaf _ -> (step kol1 (num+1)) :: (Leaf(num))
	| Node (l,_,r)-> 
		let kol2 = push2 l r  kol1 in
		(step kol2 (num+1))::(Node(Empty,num,Empty))
let rec make_tree xs = 
let y::ys = xs in
match y with
| Node(_,x,_) -> let y1::y2::rest = xs in make_tree (Node(y1))
| Leaf x -> 
	let z::zs = ys in
	if z = Node(_,n,_)
	then 



let bfs_num tree =
	let genNextLvl forest = List.concat @@ List.map (fun x ->
		match x with
		| Leaf _ -> []
		| Node (l,_,r)-> [l;r]
		)	forest in

	let rec genNumTree forest generatedNumTree num =
		match forest with
		| [] -> []
		|  x::xs-> 	match x with
			| Leaf y -> (Leaf num ) :: genNumTree xs generatedNumTree (num+1)   
			| Node(_,_,_)-> 	
				let l::r::rest = generatedNumTree in
				(Node (l,num,r) )::genNumTree xs rest (num+1) in

	let rec bfs_num_aux forest num =
		if forest = [] then [] 
		else
		let nextlvl = genNextLvl forest in 
		let generated = bfs_num_aux nextlvl (num + List.length forest) in
		genNumTree forest generated num in
List.hd @@ bfs_num_aux [tree] 1;;

let test2 = bfs_num t1

(*
let rec tree_to_forest tree = match tree with
| Node (l,x,r) -> MNode (x, Forest (tree_to_forest l, Forest(tree_to_forest r, EmptyForest )))
| Leaf x-> MNode(x,EmptyForest)

		
let rec numerate_forest forest n = match forest with
|Forest ( _ , rest)-> 
	let (new_rest, num) = numerate_forest rest (n+1) in
	(Forest (MNode(n,EmptyForest), new_rest ), num )
| EmptyForest -> (EmptyForest, n)

let rec list_forests_next_lvl forests= 
	let rec aux x acc= match x with
	| EmptyForest -> EmptyForest::acc
	| Forest( a, EmptyForest) -> Forest( a, EmptyForest)::acc
	| Forest(a,Forest(b,EmptyForest)) -> Forest( a, EmptyForest)::Forest( b, EmptyForest)::acc in
List.fold_right aux ]
*)

(*
let rec bfs_aux mtree n = let MNode(_,forest) = mtree in
match forest with
 | EmptyForest -> ( MNode(n, EmptyForest), n+1)
 | Forest(el_f, next_forest)-> 
 	let (num_forest , n1)= numerate_forest forest n in 
 	let rec aux forest num_forest n = match forest, num_forest with
 	| EmptyForest,EmptyForest-> EmptyForest
 	| Forest(MNode(_, next) , next_forest1), Forest(MNode(_,_), next_forest2)-> 
 		let (res, n1) = bfs_aux next n in
 		Forest(MNode(_, res), aux next_forest1 next_forest2 n1)
 	aux forest num_forest
*)












