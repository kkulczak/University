




let (++) f g = fun x  -> f (g x)

(* inr :(string -> a) -> string -> (int ->a) *)
let inr k str n = k (str ^ (string_of_int n)) 
(*eol: (string->a) -> string -> a *)
let eol k str = k (str ^ "\n")

let flt k str fl = k (str ^ (string_of_float fl) )

let str k str1 str2 = k (str1 ^ str2)
let lit str k s = k( s ^ str)
let sprintf format = format (fun x->x) ""

let test = (sprintf (lit "Ala ma " ++ inr ++ lit " kot" ++ str ++ lit ".") 5 "ow");;