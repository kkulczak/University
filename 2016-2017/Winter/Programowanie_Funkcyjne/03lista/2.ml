let rec wielomian x = function
	[] -> 0.
|	y::ys -> y +. x *. wielomian x ys


let wielomian2 ys x = List.fold_right (fun y acc -> acc *. x +. y)  ys 0.



let t1 = wielomian 3. [4.;4.;1.] (* (x+2)^2 *)
let t2 = wielomian2  [4.;4.;1.] 3.
