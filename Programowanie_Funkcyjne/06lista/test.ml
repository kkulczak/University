let f a b = a + b
let g a =match a with
	| 1 -> lazy (f 2 3)
	| _  -> failwith "tata" 