#lang racket

(require 2htdp/image)

(define ele_box (square 100 "outline" "green"))

(beside ele_box ele_box ele_box)
;(define arr '(1 2 3 5))

;(define (list_print lst)
  ;(if (empty? lst)
      ;'()
      ; ((overlay (text (number->string (car arr)) 40 "red") ele_box)(list_print (cdr arr)))))
;(list_print arr)