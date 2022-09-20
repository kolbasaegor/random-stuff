#lang racket

; Exercise 1.1
(define (operation? x)
  (if (member x '(+ - * /)) #t #f))

(define (variable? expr)
  (cond
    [(list? expr)
     (if (= 1 (length expr))
         (if (and (symbol? (first expr)) (not (operation? (first expr)))) #t #f)
         #f)]
    [else (if (and (symbol? expr) (not (operation? expr))) #t #f)]))

(define (term? x)
  (or (list? x) (number? x) (variable? x)))

(define (sum? expr)
  (if (list? expr)
      (cond
    [(= 3 (length expr)) (cond
        [(term? (second expr)) (cond
            [(term? (third expr)) (if (equal? '+ (first expr)) #t #f)]
            [else #f])]
        [else #f])]
    [else #f])
      (error "sum? : input is not expression" expr)))

(define (summand-1 expr)
  (if (sum? expr) (second expr)
      (error "summand-1 : expression is not sum " expr)))

(define (summand-2 expr)
  (if (sum? expr) (third expr)
      (error "summand-2 : expression is not sum " expr)))

(define (product? expr)
  (if (list? expr)
      (cond
    [(= 3 (length expr)) (cond
        [(term? (second expr)) (cond
            [(term? (third expr)) (if (equal? '* (first expr)) #t #f)]
            [else #f])]
        [else #f])]
    [else #f])
      (error "product? : input is not expression" expr))) 

(define (multiplier-1 expr)
  (if (product? expr) (second expr)
      (error "multiplier-1 : expression is not product " expr)))

(define (multiplier-2 expr)
  (if (product? expr) (third expr)
      (error "multiplier-2 : expression is not product " expr)))

; Exercise 1.2
(define (derivate-term term var)
  (if (equal? term var) 1 0))

(define (derivate-sum-to-list term1 term2)
  (cons '+ (list term1 term2)))

(define (derivate-product-to-list term1 term1-derivate term2 term2-derivate)
  (cons '+ (list (cons '* (list term1-derivate term2)) (cons '* (list term1 term2-derivate)))))

(define (derivative expr var)
  (cond
    [(or (variable? expr) (number? expr)) (derivate-term expr var)]
    [(sum? expr) (derivate-sum-to-list (derivative (summand-1 expr) var) (derivative (summand-2 expr) var))]
    [(product? expr)
     (derivate-product-to-list
      (multiplier-1 expr) (derivative (multiplier-1 expr) var)
      (multiplier-2 expr) (derivative (multiplier-2 expr) var))]))

; Exercise 1.3
(define (simplify-at-root expr)
  (if (list? expr) (cond
    [(sum? expr) (cond
                   [(and (number? (second expr)) (number? (third expr)))
                    (+ (second expr) (third expr))]
                   [(equal? 0 (second expr)) (simplify-at-root (third expr))]
                   [(equal? 0 (third expr)) (simplify-at-root (second expr))]
                   [else (cons '+ (list (simplify-at-root (second expr)) (simplify-at-root (third expr))))])]
    [(product? expr) (cond
                   [(and (number? (second expr)) (number? (third expr)))
                    (* (second expr) (third expr))]
                   [(equal? 1 (second expr)) (simplify-at-root (third expr))]
                   [(equal? 1 (third expr)) (simplify-at-root (second expr))]
                   [(equal? 0 (second expr)) 0]
                   [(equal? 0 (third expr)) 0]
                   [else (cons '* (list (simplify-at-root (second expr)) (simplify-at-root (third expr))))])]
    )
      expr))

(define (simplify expr)
  (if (equal? expr (simplify-at-root expr)) expr
      (simplify (simplify-at-root expr))))

; Exercise 1.5
(define (to-infix expr)
  (cond
    [(or (number? expr) (variable? expr)) expr]
    [(operation? (first expr))
     (list (to-infix (second expr)) (first expr) (to-infix (third expr)))]
    [else expr]))

; Exercise 1.6.1
(define (exp? expr)
  (if (list? expr)
      (cond
    [(= 3 (length expr)) (cond
        [(term? (second expr)) (cond
            [(term? (third expr)) (if (equal? 'exp (first expr)) #t #f)]
            [else #f])]
        [else #f])]
    [else #f])
      (error "exp? : input is not expression" expr)))

(define (sin? expr)
  (if (list? expr)
      (if (= 2 (length expr))
          (if (equal? 'sin (first expr))
              (if (term? (second expr))
                  #t
                  (error "sin? : invalid argument " (second expr)))
              #f)
          #f)
      (error "sin? : input is not expression" expr)))

(define (cos? expr)
  (if (list? expr)
      (if (= 2 (length expr))
          (if (equal? 'cos (first expr))
              (if (term? (second expr))
                  #t
                  (error "cos? : invalid argument " (second expr)))
              #f)
          #f)
      (error "cos? : input is not expression" expr)))

(define (tan? expr)
  (if (list? expr)
      (if (= 2 (length expr))
          (if (equal? 'tan (first expr))
              (if (term? (second expr))
                  #t
                  (error "tan? : invalid argument " (second expr)))
              #f)
          #f)
      (error "tan? : input is not expression" expr)))

(define (log? expr)
  (if (list? expr)
      (if (= 2 (length expr))
          (if (equal? 'log (first expr))
              (if (term? (second expr))
                  #t
                  (error "log? : invalid argument " (second expr)))
              #f)
          #f)
      (error "log? : input is not expression" expr)))

(define (derivate-sin term term-derivate)
  (list '* term-derivate (list 'cos term)))

(define (derivate-cos term term-derivate)
  (list '* (list '* -1 term-derivate) (list 'sin term)))

(define (derivate-tan term term-derivate)
  (list '/ term-derivate (list 'exp (list 'cos term) 2)))

(define (derivate-log term term-derivate)
  (list '/ term-derivate term))

(define (derivate-exp u v u-d v-d)
  (list '+ (list '* (list '* v (list 'exp u (list '- v 1))) u-d) (list '* (list 'exp u v) (list '* (list 'log u) v-d))))

(define (derivative-upd1 expr var)
  (cond
    [(or (variable? expr) (number? expr)) (derivate-term expr var)]
    [(sum? expr) (derivate-sum-to-list (derivative-upd1 (summand-1 expr) var) (derivative-upd1 (summand-2 expr) var))]
    [(product? expr)
     (derivate-product-to-list
      (multiplier-1 expr) (derivative-upd1 (multiplier-1 expr) var)
      (multiplier-2 expr) (derivative-upd1 (multiplier-2 expr) var))]
    [(sin? expr) (derivate-sin (second expr) (derivative-upd1 (second expr) var))]
    [(cos? expr) (derivate-cos (second expr) (derivative-upd1 (second expr) var))]
    [(tan? expr) (derivate-tan (second expr) (derivative-upd1 (second expr) var))]
    [(log? expr) (derivate-log (second expr) (derivative-upd1 (second expr) var))]
    [(exp? expr)
     (derivate-exp (second expr) (third expr)
                   (derivative-upd1 (second expr) var)
                   (derivative-upd1 (third expr) var))]))

; Exercise 1.6.2
(define (sub? expr)
  (if (list? expr)
      (cond
    [(= 3 (length expr)) (cond
        [(term? (second expr)) (cond
            [(term? (third expr)) (if (equal? '- (first expr)) #t #f)]
            [else #f])]
        [else #f])]
    [else #f])
      (error "sub? : input is not expression" expr)))

(define (div? expr)
  (if (list? expr)
      (cond
    [(= 3 (length expr)) (cond
        [(term? (second expr)) (cond
            [(term? (third expr)) (if (equal? '/ (first expr)) #t #f)]
            [else #f])]
        [else #f])]
    [else #f])
      (error "div? : input is not expression" expr)))

(define (simplify-upd1-at-root expr)
  (if (list? expr) (cond
    [(sum? expr) (cond
                   [(and (number? (second expr)) (number? (third expr)))
                    (+ (second expr) (third expr))]
                   [(equal? 0 (second expr)) (simplify-upd1-at-root (third expr))]
                   [(equal? 0 (third expr)) (simplify-upd1-at-root (second expr))]
                   [else (cons '+ (list (simplify-upd1-at-root (second expr)) (simplify-upd1-at-root (third expr))))])]
    [(sub? expr) (cond
                   [(and (number? (second expr)) (number? (third expr)))
                    (- (second expr) (third expr))]
                   [(equal? 0 (second expr)) (* -1 (simplify-upd1-at-root (third expr)))]
                   [(equal? 0 (third expr)) (simplify-upd1-at-root (second expr))]
                   [(equal? (second expr) (third expr)) 0]
                   [else (cons '- (list (simplify-upd1-at-root (second expr)) (simplify-upd1-at-root (third expr))))])]
    [(product? expr) (cond
                   [(and (number? (second expr)) (number? (third expr)))
                    (* (second expr) (third expr))]
                   [(equal? 1 (second expr)) (simplify-upd1-at-root (third expr))]
                   [(equal? 1 (third expr)) (simplify-upd1-at-root (second expr))]
                   [(equal? 0 (second expr)) 0]
                   [(equal? 0 (third expr)) 0]
                   [else (cons '* (list (simplify-upd1-at-root (second expr)) (simplify-upd1-at-root (third expr))))])]
    [(div? expr) (cond
                   [(and (number? (second expr)) (number? (third expr)))
                    (/ (second expr) (third expr))]
                   [(equal? 1 (third expr)) (simplify-upd1-at-root (second expr))]
                   [(equal? 0 (second expr)) 0]
                   [(equal? 0 (third expr))
                    (error "simplify-upd1-at-root : division by zero" expr)]
                   [(equal? (second expr) (third expr)) 1]
                   [else (cons '/ (list (simplify-upd1-at-root (second expr)) (simplify-upd1-at-root (third expr))))])]
    [(sin? expr) (cond
                   [(number? (second expr)) (sin (second expr))]
                   [(variable? (second expr)) (list 'sin (second expr))]
                   [else (list 'sin (simplify-upd1-at-root (second expr)))])]
    [(cos? expr) (cond
                   [(number? (second expr)) (cos (second expr))]
                   [(variable? (second expr)) (list 'cos (second expr))]
                   [else (list 'cos (simplify-upd1-at-root (second expr)))])]
    [(tan? expr) (cond
                   [(number? (second expr))
                    (if (= (second expr) (/ pi 2))
                        (error "simplify-upd1-at-root : invalid argument of tan " (second expr))
                        (tan (second expr)))]
                   [(variable? (second expr)) (list 'tan (second expr))]
                   [else (list 'tan (simplify-upd1-at-root (second expr)))])]
    [(log? expr) (cond
                   [(number? (second expr))
                    (if (<= (second expr) 0)
                        (error "simplify-upd1-at-root : argument of log must be > 0 but got" (second expr))
                        (log (second expr)))]
                   [(variable? (second expr)) (list 'log (second expr))]
                   [else (list 'log (simplify-upd1-at-root (second expr)))])]
    [(exp? expr) (cond
                   [(and (number? (second expr)) (number? (third expr))) (expt (second expr) (third expr))]
                   [(equal? 0 (third expr)) 1]
                   [(equal? 1 (third expr)) (second expr)]
                   [else (cons 'exp (list (simplify-upd1-at-root (second expr)) (simplify-upd1-at-root (third expr))))])]
    )
      expr))

(define (simplify-upd1 expr)
  (if (equal? expr (simplify-upd1-at-root expr)) expr
      (simplify-upd1 (simplify-upd1-at-root expr))))

; Exercise 1.7




















