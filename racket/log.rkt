#lang racket
(define (lg n ans)
   (if (= n 1) 
      ans 
   (lg (floor (/ n 2)) (+ ans 1))))

(lg 16 0)