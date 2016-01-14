digit_sum :: Integral x => x -> x
digit_sum x | x < 10   = x
            | x >=10   = (mod x 10) + digit_sum (div x 10) 

main = do
  print (digit_sum (product [1..100]))