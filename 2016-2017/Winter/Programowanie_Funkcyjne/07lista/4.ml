
let fresh  =
	let  kom = ref 1 in
	let aux  ?(value=None) str=
		let _ = match value with
		| None -> ()
		| Some a-> kom := a-1 in
		let temp = !kom in
		 kom := !kom +1 ;
		str ^ (string_of_int temp) in
	aux;;
let reset n = 
	let _= fresh ~value:(Some n) "" in ();;

	fresh "x";;
	fresh "x";;
	fresh "x";;
	fresh "x";;
	reset 10;;
	fresh "x";;
	fresh "x";;