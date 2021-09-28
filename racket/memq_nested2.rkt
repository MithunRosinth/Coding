#lang racket
;memq simple list
(define (memq item x)
  (cond ((null? x) false)
        ((eq? item (car x)) x)
        (else (memq item (cdr x)))))

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