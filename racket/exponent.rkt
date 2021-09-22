#lang racket
(define (expt b n)
  (if (= n 0)
      1
      (* b (expt b (- n 1)))))

(define (expt-iter b counter product)
  (if (= counter 0)
      product
      (exp-iter b
                (- counter 1)
                (* b product))))
(define (expt1 b n)
  (exp-iter b n 1))