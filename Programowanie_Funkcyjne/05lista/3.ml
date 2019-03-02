(* funckje użytkowe *)
let next_stream str =
		try  Some (Stream.next str)
		with Stream.Failure -> None
let stream_to_list stream =
	let rec aux str = match  next_stream str with
		| None -> []
		| Some a -> a::(aux str) in
	aux stream
let stream_tee stream =
    let next self other i =
      try
        if Queue.is_empty self
        then
          let value = Stream.next stream in
          Queue.add value other;
          Some value
        else
          Some (Queue.take self)
      with Stream.Failure -> None in
    let q1 = Queue.create () in
    let q2 = Queue.create () in
    (Stream.from (next q1 q2), Stream.from (next q2 q1))

let list_to_stream xs = Stream.from (fun i ->
		try
			Some(List.nth xs i)
		with Failure "nth" -> None )
(* KONIEC TYCH FUNKCJI*)
type htree =
	| Leaf of char * int
	| Node of htree * int * htree

let mkHTree = function
| [] -> failwith "Lista pusta"
| x::xs ->
	let take_int = function
			| Leaf (_,x) -> x
			| Node (_,x,_) -> x in
	let aux a b =
		Node (a, take_int a + take_int b ,b) in
	List.fold_left aux x (List.sort (fun x y ->  (take_int x) - (take_int y) ) xs )

let list_Htree_code tree =
		let rec aux code_list act_code = function
		| Leaf (c,_) -> (c,List.rev act_code)::code_list
		| Node (left,c,right) ->
			let code_list2 = aux code_list (0::act_code) left in
			aux code_list2  (1::act_code) right
		in aux [] [] tree

let encode tree stream =
	let dictionary =  list_Htree_code tree in
	let count_code a = snd (List.find (fun b -> (fst b) = a ) dictionary) in
	let next_stream str =
		try  Some (Stream.next str)
		with Stream.Failure -> None in
	let rec aux str = match  next_stream str with
		| None -> []
		| Some a -> (count_code a)@(aux str) in
	let rec to_chars = function
		| [] -> []
		| a::b::c::d::e::f::g::h::xs ->
			(Char.chr (((((((a*2+b)*2+c)*2+d)*2+e)*2+f)*2+g)*2+h))::to_chars xs
		| xs -> to_chars (xs @ [0]) in
	let out_list = to_chars (aux stream) in
	Stream.from (fun i ->
		try
			Some(List.nth out_list i)
		with Failure "nth" -> None )

let decode tree str =
	let rec chars_to_bin tree stream = match next_stream stream with
	| None -> []
	| Some a ->
		let char_to_bin_list chr =
			let rec aux num it acc =
				if it = 0
				then acc
				else aux (num/2) (it-1) ((num mod 2)::acc) in
		aux (Char.code chr) 8 [] in
	(char_to_bin_list a) @ (chars_to_bin tree stream) in
	let bin_list = chars_to_bin tree str in
	let rec make_decode_list ys tree =
		let rec aux = function
			| [],_ -> ('\n',[])
			| xs,Leaf (c,_) -> (c,xs)
			| 0::xs, Node(l,_,_) -> aux (xs,l)
			| 1::xs, Node(_,_,r) -> aux (xs,r) in
		let (x,xs) = aux (ys,tree) in
		if xs = []
		then []
		else x::(make_decode_list xs tree) in
	let out_list = make_decode_list bin_list tree in
Stream.from (fun i ->
	try
		Some(List.nth out_list i)
	with Failure "nth" -> None )

let char_frequency stream =
	let rec aux stream acc = match next_stream stream with
		| None -> acc
		| Some a ->
			if List.mem_assoc a acc
			then
				let newacc = List.map (fun (key,b) -> if key = a then (key,b+1) else (key,b)) acc in
				aux stream newacc
			else
				aux stream ((a,1)::acc) in
	aux stream []


let compress infile outfile =
	let in_channel = open_in infile in
	let stream = Stream.of_channel in_channel  in
	let dict = char_frequency stream in
	let huff_tree = mkHTree @@
			List.map (fun (a,b) -> Leaf(a,b)) dict in
	let in_channel = open_in infile in
	let stream = Stream.of_channel in_channel in
	let out_stream = encode huff_tree stream in
	let out_channel = open_out outfile in
	let rec aux str = match next_stream str with
		| None -> (close_out out_channel,huff_tree)
		| Some a-> output_char out_channel a;
			aux str in
	aux out_stream

let decompress infile outfile tree =
	let in_channel = open_in infile in
	let in_stream = Stream.of_channel in_channel in
	let decoded_stream = decode tree in_stream in
	let out_channel = open_out outfile in
	let rec aux str = match next_stream str with
		| None -> close_out out_channel
		| Some a-> output_char out_channel a;
			aux str in
	aux decoded_stream



let out_channel = open_out "out"
let casd = output_char out_channel 'a'
let casd = output_char out_channel 'b'
let x=  close_out out_channel


(*
let in_channel = open_in "in"
let text = Stream.of_channel in_channel
let in_channel2 = open_in "in"
let text2 = Stream.of_channel in_channel2
let out_channel = open_out "out"
*)

let t1 = mkHTree [Leaf ('a',3); Leaf ('b',2) ; Leaf ('c', 4)]
let t2 = list_Htree_code t1
(*let t3 =  encode t1 text *)
(* let t3show = stream_to_list t3 *)
(* let t4 = List.map Char.code t3show *)
(* let t5 = decode t1 t3 *)
let (t10,my_tree) = compress "Message" "Compressed_Message"
let t11 = decompress "Compressed_Message" "New_Message" my_tree
