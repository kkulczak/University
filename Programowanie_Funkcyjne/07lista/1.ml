let rec fix f = f (fix f)  

let silnia = fix (fun f -> fun n -> if n = 0 then 1 else n * (f (n-1)))