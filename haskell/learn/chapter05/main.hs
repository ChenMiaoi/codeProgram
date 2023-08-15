factorial :: Integer -> Integer
-- factorial n = 
--     if n < 0 then error "n is less than 0"
--     else if n == 0 then 1
--     else n * factorial (n - 1)

factorial n
    | n < 0 = error "n is less than 0"
    | n == 0 = 1
    | otherwise = n * factorial (n - 1)

mygcd :: Int -> Int -> Int
mygcd x y
    | y == 0 = x
    | otherwise = mygcd y (mod x y)

power :: Int -> Int -> Int
power _ 0 = 1
-- power x n = x * power x (n - 1)
power x n
    | odd n = let p = power x ((n - 1) `div` 2) in x * p * p
    | otherwise = let p = power x (n `div` 2) in p * p
    -- | odd n = x * p * p
    -- | otherwise = p1 * p1
    -- where 
    --     p = power x ((n - 1) `div` 2) 
    --     p1 = power x (n `div` 2)

product' :: [Int] -> Int
product' [] = 1
product' (x:xs) = x * product' xs
-- product' (x:xs) = foldr (*) 1 xs

snoc :: a -> [a] -> [a]
-- snoc x [] = [x]
-- snoc x (y:ys) = y : snoc x ys
snoc x (y:ys) = foldr (:) [x] ys

last' :: [a] -> a
last' [] = error "empty list"
last' [x] = x
last' (_:xs) = last' xs

take' :: (Ord t, Num t) => t -> [a] -> [a]
take' n _ | n <= 0 = []
take' _ [] = []
take' n (x:xs) = x : take' (n - 1) xs

elem' :: Eq a => a -> [a] -> Bool
elem' _ [] = False
elem' a (x:xs) 
    | a == x = True
    | otherwise = elem' a xs

delete' :: Eq a => a -> [a] -> [a]
delete' _ [] = []
delete' a (x:xs) 
    | a == x = delete' a xs
    | otherwise = x : delete' a xs

--     delete' 2 [4, 2, 1, 2]
-- = 4 : delete' 2 [2, 1, 2]
-- = 4 : delete' 2 [1, 2]
-- = 4 : 1 : delete' 2 [2]
-- = 4 : 1 : []

drop' :: Int -> [Int] -> [Int]
drop' _ [] = []
drop' 0 xs = xs
drop' n (_:xs) = drop' (n - 1) xs
-- drop' n (x:xs)
--     | n < 0 = x : drop' (n - 1) xs
--     | otherwise = drop' (n - 1) xs

total :: Num a => [a] -> a
-- total [] = 0
-- total (x:xs) = x + total xs
-- total (x:xs) = foldr (+) 0 xs

total' :: Num a => [a] -> a -> a
total' [] n = n
total' (x:xs) n = total' xs $! (n + x)

total xs = total' xs 0

mc :: Int -> Int
mc n 
    | n > 100 = n - 10
    | otherwise = mc (mc (n + 11))

fibonacci :: (Num a, Eq a) => a -> a
fibonacci 0 = 0
fibonacci 1 = 1
fibonacci n = fibonacci (n - 1) + fibonacci (n - 2)

fibs :: (Num b, Eq b, Enum b) => b -> [b]
-- fibs n = map fibonacci [0..n]

fibStep :: Num a => (a, a) -> (a, a)
fibStep (u, v) = (v, u + v)

fibPair :: (Eq a, Num a) => a -> (a, a)
fibPair 0 = (0, 1)
fibPair n = fibStep (fibPair (n - 1))

fastFib :: (Eq b, Num b) => b -> b
fastFib n = fst (fibPair n)

fibs n = map fastFib [1..n]

fibs' :: Num b => Int -> [b]
fibs' n = take n (map fst (iterate fibStep (0, 1)))