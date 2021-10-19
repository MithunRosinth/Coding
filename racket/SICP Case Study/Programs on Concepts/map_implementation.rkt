#lang racket
(define (map func lst)
  (if (empty? lst)
    '()
    (cons (func (car lst)) (map func (cdr lst)))))

(map even? '(2 4 5 6))