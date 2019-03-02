let rec prependWith x a b =
  match a with
    [] -> b
  |hd::tl -> (x::hd) :: prependWith x tl b

let rec podciagi x =
  match x with
    [] -> [[]]
  |h::t -> let temp = podciagi t in
    prependWith h temp temp

podciagi [1;2;3;4]
