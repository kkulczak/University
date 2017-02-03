type  cycle = El of int * cycle ref | Nil 

let empty =
	let temp = ref Nil in
	(temp,temp)
let is_empty (fst,lst )= !fst = Nil
	

let add el (fst,lst) =
	if !fst = Nil 
	then 
		let temp =ref Nil in
		temp := El(el, temp);
		(temp,temp)
	else
		let newlst = ref (El(el,fst)) in
		let El(a,_) = !lst in 
		lst := El(a, newlst);
		(fst,newlst);;

let take (fst,lst) =
	if !fst = Nil 
	then failwith "Cannot take from Nil"
	else
		if fst == lst 
		then  
			let El(a,_) = !fst in
			(a,(ref Nil, ref Nil))
		else
			let El(a,newfst) = !fst in 
			let El(b,_) = !lst in
			lst := El(b,newfst);
			(a, (newfst, lst));;

let shift (fst,lst) =
	if !fst = Nil
	then failwith "Cannot shift Nil"
	else
		let El(_,newfst) = !fst in
		let El(_, newlst) = !lst in
		(newfst,newlst);;

let rec build_cycle acc n cyc=
	if acc = n+1
	then cyc
	else build_cycle (acc+1) n (add acc cyc);;

let rec shift_n acc n t =
	if acc = n -1
	then t
	else shift_n (acc+1) n (shift t);;

let jozef n m =
	let c = build_cycle 1 n (empty) in
	let rec aux cyc = 
		if is_empty cyc 
		then []
		else
			let (el, cyc1 ) = take (shift_n 0 m cyc) in 
			el :: (aux cyc1)
	in
	aux c;;

let t = empty;;
let t1 = build_cycle 1 3 t;;
jozef 7 3