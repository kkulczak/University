type 'a btree = 
	| Leaf of 'a
	| Node of 'a btree * 'a * 'a btree
	| Empty
type 'a array = Arr of 'a btree * int

let node_val tree = match tree with 
	| Leaf (x) -> x
	| Node (_,x,_) -> x
	| Empty -> failwith "Val of Empty";;   

let aempty  = Arr (Empty,0)

let asub arr n =
	let rec asub_aux tree  n = 
		if n=1
		then node_val tree
		else	
			let Node(left,_,right) = tree in
			if n mod 2 = 0
			then 	asub_aux left (n/2)
			else	asub_aux right (n/2) in
let Arr(tree,max_n) = arr in
if n > max_n
then failwith "Arr to big index" 
else asub_aux tree n;;


let aupdate arr n x  =
	let rec aupdate_aux tree n x =
		if n=1
		then match tree with
			| Leaf _ -> Leaf x
			| Node (l,_,r) -> Node (l,x,r)
			| Empty -> failwith "Empty Tree"
		else 		
			let   ( Node (left, el ,right )) = tree in
			if n mod 2 = 0
			then Node( aupdate_aux left (n/2) x, el , right)
			else Node(left, el ,aupdate_aux right (n/2) x) in
let Arr(tree,max_n) = arr in
if n > max_n
then failwith "Arr to big index" 
else Arr (aupdate_aux tree n x,max_n);;

let ahiext x arr =
	let rec ahiext_aux tree n x =
		if n/2 = 1 
		then 
			match tree with
			| Leaf el -> Node(Leaf x, el, Empty)
			| Node (left,el,Empty) -> Node(left,el,Leaf x)
			| Node (_,_,_) -> failwith "alg bug1"
			| Empty -> failwith "alg bug2	"
		else
			let   ( Node (left, el ,right )) = tree in
			if n mod 2 = 0
			then Node( ahiext_aux left (n/2) x, el , right)
			else Node(left, el ,ahiext_aux right (n/2) x) in
let Arr(tree,max_n) = arr in
match max_n with
| 0 -> Arr (Leaf x , 1)
| 1 ->  let Leaf m = tree in Arr ( Node(Leaf x, m, Empty) , 2)
| _ -> Arr (ahiext_aux tree (max_n +1 ) x , max_n+1);;


let ahirem arr =
	let rec ahirem_aux tree n =
		if n/2 = 1 
		then 
			match tree with
			| Node (left,el,Empty) -> Leaf el
			| Node (right,el,Leaf _) -> Node (right,el, Empty)
			| Leaf _ -> failwith "alg bug3" 
			|Empty -> failwith "alg bug4"
		else
			let   ( Node (left, el ,right )) = tree in
			if n mod 2 = 0
			then Node( ahirem_aux left (n/2) , el , right)
			else Node(left, el ,ahirem_aux right (n/2) ) in
let Arr(tree,max_n) = arr in
match max_n with
| 0 -> failwith "List already empty"
| 1 ->   aempty
| _ -> Arr (ahirem_aux tree (max_n ) , max_n-1);;


let t1 = Node(Node(Leaf 'a', 'b', Leaf 'c'), 'd', Leaf 'e')
let tab = Arr (t1,5)
let test1 = asub tab 4
let t2 = aupdate tab 3 'z'
let m2 = ahiext 2 @@ ahiext 1 aempty
let m3 = ahiext 3 m2
let m4 = ahiext 4 m3
let m5 = ahiext 5 m4
let m6 = ahiext 6 m5
let m7 = ahiext 7 m6
let m8 = ahiext 8 m7
let ma7 = ahirem m7
let ma6 = ahirem ma7
let ma5 = ahirem ma6























