#lang racket
(define (append-test lhs rhs)
  (if (empty? lhs)
      rhs
      (cons (car lhs) (append-test (cdr lhs) rhs))))

(append-test '(1 2) '(3 4))

(list '(1 2) '(3 4))