#lang racket

(define (atom? a) (not (pair? a)))

(define (count-atoms xs)
  (if (atom? xs)
      1
      ( + (count-atoms (car xs)) (count-atoms (cdr xs)))))


(count-atoms (cons 1 2)) 
(count-atoms '(cons (#\c . x) "napis"))