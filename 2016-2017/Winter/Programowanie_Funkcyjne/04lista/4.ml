type 'a zdanie = Var of 'a | Neg of 'a zdanie | And of 'a zdanie * 'a zdanie | Or of 'a zdanie * 'a zdanie

(* podpunkt 1 *)

let  zmienne zd = 
	let rec aux acc = function
		Neg x -> aux acc x
	|	And (x,y) -> aux (aux acc x) y 
	|	Or (x,y) -> aux (aux acc x) y
	|	Var x -> if List.exists ((=) x) acc
					then acc
					else x::acc
	in aux [] zd
	
let stworz_wartosciowanie varlist =
	let rec aux acc x = match acc with
		[] -> [ [(x,true)]; [(x,false)] ]
	|	xss -> (List.map (fun xs -> (x,true)::xs) xss) @ (List.map (fun xs -> (x,false)::xs ) xss)
	in List.fold_left aux [] varlist
	
let rec sigma wartosciowanie = function
	Var x -> snd @@ List.find (fun z -> x = (fst z) ) wartosciowanie 
|	Neg x -> not ( sigma wartosciowanie x)
|	And (x,y) ->  (sigma wartosciowanie x) && (sigma wartosciowanie y)
|	Or (x,y)-> (sigma wartosciowanie x) || (sigma wartosciowanie y)

let tautologia zd1 =
	let zm1 = zmienne zd1 in
	let wartosciowania = stworz_wartosciowanie zm1 in
	List.fold_left (&&) true (List.map (fun x -> sigma x zd1) wartosciowania)



let temp1 = And (Var 'a', Var 'b' )
let temp2 = And (Var 'b', Var 'a' )
let temp3 = Or (Var 'a', Neg (Var 'a') )
let t1 = sigma [('a',true); ('b',false)] temp1
let t2 = zmienne temp1
let t3 = stworz_wartosciowanie (t2)
let t4 = tautologia temp1 
let t5 = tautologia temp3

(* Podpunkt 2*)

let neg_norm zd = 
	let rec aux acc = function
		Var x -> 
					if acc = true
					then Neg (Var x)
					else Var x
	|	Neg x -> 
					if acc = true
					then aux false x
					else aux true x
	|	And (x,y)->
					if acc = true
					then Or (aux true x, aux true y) 
					else And (aux false x, aux false y)
	| Or (x,y) ->
					if acc = true
					then And (aux true x, aux true y)
					else Or (aux false x, aux false y)
	in aux false zd
	
let temp4 = Neg (And (Or (Neg (Var 'a'), Var 'a'),Var 'a'))
let t6 = neg_norm temp4

(*Podpunkt 3*)
let rec allOrGroups expr' groups = match expr' with
      And (left, right) -> 
      let newGroups = allOrGroups left groups in
      allOrGroups right newGroups
| _ -> expr'::groups 


















