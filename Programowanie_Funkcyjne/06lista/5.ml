(* prolog.ml *)

(* An atom is either a propositional variable or an alternative of two goals. *)
type atom = 
  | Atom of string 
  | Or of goal * goal
(* A goal is a list of atoms. *)
and goal = atom list
(* A clause consists of a head (a propositional variable) and a body (a goal). *)
type clause = string * goal
(* A Prolog program is a list of clauses. *)
type program = clause list

(* Search a program for a clause with a given head. *)    
let rec lookup x pgm =
  match pgm with
    | [] ->
      None
    | (y, g) :: p ->
      if x = y then Some g else lookup x p

(* 
A propositional Prolog interpreter written in CPS with two layers of continuations: 
a success and a failure continuation. The failure continuation is parameterless and 
it specifies what should happen next in case of a failure in the current goal. The 
success continuation takes a failure continuation as an argument and it specifies 
what should happen next in case the current goal is satisfied. 
*)
	
(*      eval_atom : atom -> program -> ((unit -> 'a) -> 'a) -> (unit -> 'a) -> 'a *)
let rec eval_atom a p sc fc acc=
  match a with
    | Atom x ->
      (match (lookup x p) with
	| None -> 
	  fc acc
	| Some g -> 
	  eval_goal g p sc fc acc)
    | Or (g1, g2) ->
      eval_goal g1 p sc (fun someAcc -> eval_goal g2 p sc fc someAcc) acc

(*  eval_goal : goal -> program -> ((unit -> 'a) -> 'a) -> (unit -> 'a) -> 'a  *)
and eval_goal g p sc fc =
  match g with
    | [] -> 
      sc fc acc
    | a :: g -> 
      eval_atom a p (fun fc'  someAcc -> eval_goal g p sc fc' someAcc) fc acc

(*  run : goal ->  program -> bool  *)
let run g p = eval_goal g p (fun fc-> 1+fc ) (fun () -> false)
(*let run g p = eval_goal g p (fun fc acc -> fc (acc+1)) (fun acc -> acc) 0;;*)
(* Przed poprawieniem na rekursje ogonowa: *)
(* let run g p = eval_goal g p (fun fc -> 1 + fc ()) (fun () -> 0) *)

(* tests *)
  
let p1 = [("a", [Atom "b"; Atom "c"]);
	  ("b", [])]
  
let p2 = [("a", [Atom "b"; Or ([Atom "c"], [Atom "d"]); Atom "e"]);
	  ("b", [Atom "d"]);
	  ("d", []);
	  ("e", [Atom "d"])]
  
let p3 = [("a", [Atom "b"; Or ([Atom "c"], [Atom "d"]); Atom "e"]);
	  ("b", [Atom "d"]);
	  ("c", []);
	  ("d", []);
	  ("e", [Atom "d"])]
  
let g1 = [Atom "a"] 

let v1_1 = run g1 p1
let v1_2 = run g1 p2
let v1_3 = run g1 p3  

(* eof *)
