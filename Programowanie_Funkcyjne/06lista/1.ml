type 'a btree =  
	| Leaf of 'a 
	| Node of 'a btree *  'a btree
type from = 
	| No
	| Left
	| Both
	|Special_End_Function

let rec list_of_leafs acc = function
	| Leaf x -> x::acc
	| Node (left, right) -> 
		let xs = list_of_leafs acc right in
		list_of_leafs xs left;;  

let def_samefringe tree1 tree2 = list_of_leafs [] tree1 = list_of_leafs [] tree2

	

let check_right tree = 0;;

let t1 = Node (Node (Leaf 1,
				Leaf 2), Leaf 3)
let t2 = Node(Leaf 1, Node (Leaf 2, Leaf 3))
let test1 = list_of_leafs  [] t1
let test2 = def_samefringe t1 t2



type  'a llist = 
	|Nil
	| LCons of  'a * (unit -> 'a llist);;

let samefringe tree1 tree2 = 

	let rec next_val tree k = match tree with
	| Leaf x ->  LCons (x, k)
	| Node (l,r) -> next_val l (function () -> next_val r k) in

	let rec compare tree1 tree2 = match tree1 (), tree2 () with
	| LCons (x1,k1),LCons (x2,k2)-> 	if x1 = x2
						then compare k1 k2
						else false
	| Nil,Nil -> true 
	|  _, _ -> false in

compare (fun () -> next_val tree1 (fun () -> Nil)) 
			(fun () -> next_val tree2 (fun () -> Nil));;

let test5 = samefringe t1 t2










