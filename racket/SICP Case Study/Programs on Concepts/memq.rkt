#lang racket
(define (contains list x)
	(cond [(null? list) #f]
		[(equal? (car list) x) #t]
		[else (contains (cdr list) x)]))

(contains '(1 2 3 4) 4)