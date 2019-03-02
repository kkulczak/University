type 'a list_mutable = LMnil | LMcons of 'a * 'a list_mutable ref


 let rec concat_copy xs ys =
 	match xs with
 	| LMnil	->  ys 
 	|  LMcons(x,zs) -> LMcons(x, ref(concat_copy (!zs) ys) );;


let rec concat_share xs ys =
	let rec insert_at_end xs thing = match !xs with
	| LMnil -> xs := thing 
	| LMcons(_,zs) -> insert_at_end zs thing in
match xs with
| LMnil -> ys
| LMcons(x,zs)-> 
		insert_at_end zs ys;
		xs

let xs = LMcons(1,ref(LMcons(2,ref LMnil)))
let ys = LMcons(3,ref(LMnil)) 

let t1 = concat_copy xs ys

let xs3 = LMcons(1,ref(LMcons(2,ref LMnil)))
let ys3 = LMcons(3,ref(LMnil))

let t2 = concat_share xs3 ys3 
