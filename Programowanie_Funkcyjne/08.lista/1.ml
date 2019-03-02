module type PQUEUE =
sig
  type priority
  type 'a t
    
  exception EmptyPQueue
  
  val empty : 'a t
  val insert : 'a t -> priority -> 'a -> 'a t
  val remove : 'a t -> priority * 'a * 'a t
end	








