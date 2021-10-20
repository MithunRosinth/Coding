#lang racket
;memq nested list
(define (memberk needle lst)
  (define (found? haystack)
    (or (equal? needle haystack)
        (and (pair? haystack)
             (or (found? (car haystack))
                 (found? (cdr haystack))))))
  (let loop ((lst lst))
    (cond ((null? lst) #f)
          ((found? (car lst)) lst)
          (else (loop (cdr lst))))))

(memberk 5 '('(1 2) '(3 5) 5 5 '(9 5) '(4 6)))