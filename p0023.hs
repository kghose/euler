{-

-}


proper_divisors :: Int -> [Int]
proper_divisors n = [x | x <- [1 .. (div n 2)], (mod n x) == 0]

is_abundant :: Int -> Bool
is_abundant = (map _d [0 ..] !!)
  where _d n = sum (proper_divisors n) > n

-- List of all abundant numbers up to n
abundant_numbers :: Int -> [Int]
abundant_numbers n = filter is_abundant [1 .. n]

are_abundant :: Int -> Int -> Bool
are_abundant a b = (is_abundant a) && (is_abundant b)

-- A summable number is a number that can be expressed as the sum of two abundant numbers
-- a is the list of abundant numbers upto div n 2
summable :: Int -> [Int] -> Bool
summable n a = any (\x -> (are_abundant x (n - x))) (filter (< (div n 2)) a)

main = do
--    print (sum (filter (\x -> not (summable x)) [1 .. 28123]))
    let a = abundant_numbers 14062
    print (sum (filter (\x -> not (summable x a)) [1 .. 1000]))    