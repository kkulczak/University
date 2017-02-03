
let rec ciag1 n = 
	if n = 0 
	then 0 
	else 2 * (ciag1 (n-1) ) + 1 ;;

let rec ciag_temp n acc it = if it = n
	then 2 * acc +1 
	else ciag_temp n (2 * acc +1) (it +1)

let ciag2 n = ciag_temp n 0 1


let test2 = ciag2 10000000








