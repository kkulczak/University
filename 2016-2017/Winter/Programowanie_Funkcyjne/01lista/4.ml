
let m = 10
let f x = m + x
let m = 100
(* zadanie 5 *)

(* let x = 4 div 0 in 2 *)   

(* zadanie 6*)
let plus = fun x y -> x+y
let plus' = fun x-> fun y -> x + y 
let plus'' x = fun y -> x+y
let plus_3 = fun x -> plus x 3 

(* zdanie 7*)

let id = fun x -> (x :int)
let zlozenie f g = fun x -> f (g x)
let dziwna x = failwith "undefined argument"


(* zadanie 8*)

(* zlozenie wyzej*)

let rec iteration_temp i f acc = 
	if i = 0 then acc 
	else iteration_temp (i-1) f (zlozenie acc f)
let iteration i f = iteration_temp i f (fun x->x)

let zwieksz x = x+1
let mnozenie x y = iteration x ((+) y) 0 

let (^^) x p = iteration p (mnozenie x) 1

(* zdanie 9 *)



let hd (s : int -> 'a) = s 0
let tail (s : int -> 'a) = fun x -> s (x+1) 
let add (s : int -> 'a) c = fun x-> (s x) + c
let map  (s:int -> 'a) (f : 'a -> 'b) = fun x -> f (s x)
let map2 (s1: int ->'a) (s2: int -> 'b) (f:'a -> 'b -> 'c ) =
	fun x -> f (s1 x) (s2 x)

let replace (s: int -> 'a) n (a: 'a) = fun x-> if x mod n = 0 
	then a 
	else s x

let take (s: int -> 'a) n = fun x -> s (n * x)

let rec fold_temp (s: int -> 'b) (f: 'a -> 'b -> 'a) (a: 'a) it lim =
	if  it = lim +1
		then a
		else	fold_temp s f (f a (s it)) (it+1) lim
let fold (s: int -> 'b) (f: 'a -> 'b -> 'a) (a: 'a) =
	fun x ->  fold_temp s f a 0 x
(*
let rec tabulate_temp (s: int -> 'a) first last=
	if first = last
		then (s first)::[]
		else (s first) :: (tabulate s first+1 last )
*)
let rec tabulate  (s: int -> 'a)  ?(first=0) last =
	if first = last
		then [(s first)]
		else (s first)::(tabulate s ~first:(first+1) last )



let ten x = (x*10) 
let test1 = hd ten
let test2 = (tail ten) 1
let test3 = (add ten 2) 1
let test4 = (map ten (function x-> -x)) 1
let test5 = (map2 id ten (+)) 1
let test6 = (replace ten 2 (-100)) 4
let test7 = (replace ten 2 (-100)) 5
let test8 = (take ten 2) 1
let test9 = (fold ten (+) 1) 0
let test10 = (fold ten (+) 1) 2
let test11 = (tabulate ten 10)
let test12 = (tabulate ten ~first:20 25)



