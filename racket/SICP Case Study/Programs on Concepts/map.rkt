#lang racket
;abs function over a list without map
(define abs-all
  (lambda (ls)
    (if (null? ls)
        '()
        (cons (abs (car ls))
              (abs-all (cdr ls))))))

;abs function over a list using map
(define abs-all1
  (lambda (ls)
    (map abs ls)))

(abs-all '(1 2 -3 -4))
(abs-all1'(1 2 -3 -4))