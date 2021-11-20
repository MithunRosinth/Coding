#lang racket

(require 2htdp/image)

(define ele_box (square 100 "outline" "green"))
;(beside ele_box ele_box)
;(above ele_box ele_box)
;(above ele_box (rotate 45 ele_box))
(define arr '(1 2 3 5))

(overlay (text (number->string (car arr)) 40 "red") ele_box)
(arr (cdr arr))
(overlay (text (number->string (car arr)) 40 "red") ele_box)
