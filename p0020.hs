digit_sum :: Integral x => x -> x
digit_sum 0 = 0
digit_sum x = (mod x 10) + digit_sum (div x 10) 

main = do
  print (digit_sum (product [1..100]))