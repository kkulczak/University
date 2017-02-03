 type 'a btree = Leaf | Node of 'a btree * 'a * 'a btree
 
 let balance tree = 
 	let rec aux  = function
 		(Leaf, b) -> 0,b   
 	|	(Node (left,_,right),b) -> 
 										let (num_l, bl) =  aux (left,b) and (num_r,br) = aux (right,b) in
 										if abs (num_l - num_r) <= 1
 										then (num_l + num_r + 1, bl && br)
 										else (num_l + num_r, false)  
 	in let _,boool = aux (tree,true) in boool
 	
 	
 
 	
 	
 	
 	let temp = 	balance @@		Node( Node(Leaf,1,Leaf)   , 1 , Node(Node(Leaf,1,Leaf),1,Node(Leaf,1,Leaf) ))
 	let temp2 = 	balance @@		Node( Node(Node(Leaf,1,Leaf),1,Node(Leaf,1,Leaf))  , 1 , Node(Node(Leaf,1,Leaf),1,Node(Leaf,1,Leaf))  )
 	let temp3 = 	balance @@		Node( Node(Node(Leaf,1,Leaf),1,Leaf)  , 1 , Node(Node(Leaf,1,Leaf),1,Node(Leaf,1,Leaf))  )
 	
	let rec half = function
	|	xs,[] ->  xs 
	|	xs,[_] -> xs
	|	_::xs,_::_::ys -> half (xs, ys)

let treefromlist xs =
	let rec aux num xs = 
		if num = 1
		then Leaf
		else 
			let y::ys = xs in
			let ts = (half (ys,ys)) in
			let lNum = num - (List.length ys)
			let left_tree, right_tree = (aux (lNum) ys, aux (num - lNum) ts)in
			Node (left_tree, y , right_tree)
	in  aux (List.length xs)  xs
	
let test = half ([1;2;3;4],[1;2;3;4])
let test1 = treefromlist [1;2;3;4;5]
let test2 = balance @@ treefromlist [1;2;3;4;5;6;7;8;9;10;11;12;13;14;15;16;17;18;19;20]











