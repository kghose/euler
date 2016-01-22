import System.Environment
import Data.List
import Data.List.Split
import Data.Char (ord)

strip_and_sort_names f = sort (map (filter (/= '\"')) (splitOn "," f))
alpha_val s = foldl (\x y -> ord(y) - 64 + x) 0 s

main = do
    f   <- readFile "p0022_names.txt"
    let sorted_names = strip_and_sort_names f
    print(sum (zipWith (\x y -> (alpha_val x) * y) sorted_names [1..]))