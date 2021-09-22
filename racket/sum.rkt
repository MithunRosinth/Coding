#lang racket
(define (ans a b c)
  (cond
    [(zero? b) c]
    [else (+ a(ans a (- b 1) c))]))

(ans 2 2 4)