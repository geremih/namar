(if (grt 1 2)
    true
    false)
false

(if (grt 2 1)
    true 
    false)
true

(if (grt 1 2)
    (add 1 2)
    (add 2 3))
5

(or true false)
true

(or (grt 1 2) (grt 2 3) (grt 4 5))
false

(or (grt 1 2) (grt 2 3) (grt 5 4))
true
