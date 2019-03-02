#lang racket


(define (count-change change coins)
  (cond ((null? coins) 0)
        ((zero? change) 1)
        ((negative? change) 0)
        (else
          (+ (count-change change (cdr coins))
             (count-change (- change (car coins)) coins)))))


(count-change 100 '(1 5 10 25 50))
(count-change 10 '(1 5 123))