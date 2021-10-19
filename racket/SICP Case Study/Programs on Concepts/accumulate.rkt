#lang racket
(define accumulate
  (lambda (op base func ls)
    (if (null? ls)
        base
        (op (func (car ls))
            (accumulate op base func (cdr ls))))))

(accumulate + 0 sqr '(1 2 3))
(accumulate * 1 sqr '(1 2 3))