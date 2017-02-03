#lang racket

(define (mk-mobile left right) (cons left right))
(define (mk-branch length struct) (cons length struct))

(define (left-branch mobile) (car mobile))
(define (right-branch mobile) (cdr mobile))
(define (branch-length branch) (car branch))
(define (branch-struct branch) (cdr branch))

(define (weight mobile)
  (define (branch-weight branch)
    (let ([struct (branch-struct branch)])
    (if (number? struct)
        struct
        (weight struct)
       )
      ))
  (if (number? mobile)
      mobile
      (+ (branch-weight (left-branch mobile)) (branch-weight (right-branch mobile)))))