type 'a llist = 
	| Empty
	| Ltail of 'a * (unit -> 'a llist)

let rec lfrom k = Ltail (k, fun () -> lfrom (k+1))

let rec ciag denominator sign = 
	if sign 
	then Ltail(~-.(1./.denominator), fun () ->  ciag (denominator +. 2.0) (not sign) )
	else Ltail((1./.denominator), fun () ->  ciag (denominator +. 2.0) (not sign) )

let leibniz = ciag (1.0) false

let rec ltake lxs it = match lxs,it with
	| _,0 -> []
	| Empty,_ -> []
	| Ltail(x,lxs),num -> x:: ltake (lxs ()) (num-1) 
	
let rec lmap_3 f lxs =
	let Ltail(x, lys) = lxs in
	let Ltail(y, lzs) = lys() in
	let Ltail(z, lqs) = lzs() in
	Ltail( f x y z, fun () -> lmap_3 (f) (lys()) )
let transform_Euler x y z = z-.(y-.z)*.(y-.z)/.(x-.2.*.y+.z)
let 
tl = lfrom 1 
let temp2 = ltake (lfrom 1)  10
let temp3 = ltake (lmap_3 (fun x y z -> x+y+z) tl) 10
let pi = (List.fold_left (+.) 0. (ltake leibniz 1000) ) *. 4.
let leibniz2 = lmap_3 transform_Euler leibniz 
let pi2=(List.fold_left (+.) 0. (ltake leibniz2 1000)) *. 4.

(*LAZY TIME*)

type 'a lList =
	| Empty
	| Ltail of 'a * 'a lList Lazy.t

let rec ciagL denominator sign = 
	if sign 
	then Ltail(~-.(1./.denominator), lazy( ciagL (denominator +. 2.0) (not sign) ) )
	else Ltail((1./.denominator), lazy(  ciagL (denominator +. 2.0) (not sign) ) ) 
let rec lmap_3L f lxs =
	let Ltail(x, lazy lys) = lxs in
	let Ltail(y, lazy lzs) = lys in
	let Ltail(z, lazy lqs) = lzs in
	Ltail( f x y z, lazy (lmap_3L (f) lys ) )

let rec ltakeL lxs it = match lxs,it with
	| _,0 -> []
	| Empty,_ -> []
	| Ltail(x,lazy lys),num -> x::(ltakeL lys (num-1))
let leibnizL = ciagL 1.0 false
let pi3 = 4.*. (List.fold_left (+.) 0. (ltakeL leibnizL 1000))
let pi4=4.*. (List.fold_left (+.) 0. (ltakeL (lmap_3L transform_Euler leibnizL) 1000))
