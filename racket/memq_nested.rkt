  (define (find-elem l e)
    (cond [(empty? l) #f]
          [(equal? (first l) e) #t]
          [(list? (first l)) (or (find-elem (first l) e) (find-elem (rest l)e))]
          [else (find-elem (rest l) e)]))