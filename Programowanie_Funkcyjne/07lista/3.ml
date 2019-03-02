type ('k, 'v) table =  'k * 'v list

let empty = [];;

let rec find key  table = match table with 
	|   [] -> None
	| x::xs ->
		let (k,v) = x in
		if k = key
		then Some v
		else find key xs 
let add el table =
	el::table;;

let rec fib n= match n with
| 0 -> 0
| 1->1
|_ -> (fib (n-1)) + (fib (n-2));;


let fib_memo n =
let rec aux n tab =
	let a = find n tab in
	match a with
	  | None -> 
	  	let a2 = find (n-1) tab in
	  	match a2 with
	  	| None ->
	  		let (ntab,v1) = aux  (n-1) tab in
	  		let Some v2 = find (n-2) ntab in
	  		( (add (n,v1+v2) ntab), v1+v2)	  		
	  	| Some v1 -> 
	  		let Some v2 = find (n-2) tab in
		(add (n,v1+v2) tab , v1+v2 )
	  |  Some b-> (tab, b)  in
snd  @@ aux n   [(1,1);(0,0)]


let time f x =
  let start = Sys.time ()
  in let res = f x
  in let stop = Sys.time ()
  in let () = Printf.printf "Execution time: %fs\n%!" (stop -. start)
  in
res;;

time fib 10;;
time fib_memo 10;;
time fib 35;;
time fib_memo 35;;



