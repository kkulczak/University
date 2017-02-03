let rec fact_cps n k = 
	if n = 0 
	then k 1 
	else fact_cps (n-1) (fun v -> k (n*v))

type 'a btree = 
	| Leaf 
	| Node of 'a btree * 'a * 'a btree
	
let prod tree = 
	let rec aux k = function
	|	Leaf -> k 1
	|	Node (left, x, right) -> 
			let left_il =	aux k left and right_il = aux k right in
			fun v -> k (x * left_il * right_il*v)
			
	
	in aux (fun x ->x) tree
	
let test1  = prod @@ Node (Node (Leaf, 2, Node (Leaf, 3, Leaf)), 1,
   Node (Leaf, 4, Node (Leaf, 5, Leaf)))

	
	
	
	


