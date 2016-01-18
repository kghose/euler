{-
Let d(n) be defined as the sum of proper divisors of n (numbers less than n which divide evenly into n).
If d(a) = b and d(b) = a, where a ≠ b, then a and b are an amicable pair and each of a and b are called amicable numbers.

For example, the proper divisors of 220 are 1, 2, 4, 5, 10, 11, 20, 22, 44, 55 and 110; therefore d(220) = 284. The proper divisors of 284 are 1, 2, 4, 71 and 142; so d(284) = 220.

Evaluate the sum of all the amicable numbers under 10000.
-}

is_amicable :: Int -> Bool
is_amicable n = (n == d(d(n))) && (n /= d(n))

proper_divisors :: Int -> [Int]
proper_divisors n = [x | x <- [1 .. (div n 2)], (mod n x) == 0]

-- sum of proper divisors of n
d :: Int -> Int
d = (map _d [0 ..] !!)
  where _d n = sum (proper_divisors n)

main = do
    print(sum ([x | x <- [1 .. 9999], is_amicable x]))