a = 5 :: Int

add, sub :: Int -> Int -> Int
add a b = a + b
sub a b = a - b

-- f(x) = 4x + 1
f :: Num a => a -> a
f x = 4 * x + 1

-- area(r) = Πr^2
area :: Floating a => a -> a
area r = pi * r ^ 2

-- f1(x, y) = 4x + 5y + 1
f1 :: Num a => (a, a) -> a
f1 (x, y) = 4 * x + 5 * y + 1
-- curring
f' :: Num a => a -> a -> a
f' x y = 4 * x + 5 * y + 1

f1' :: Num a => a -> a -> a
-- f1' = \x -> \y -> 4 * x + 5 * y + 1
f1' = \x y -> 4 * x + 5 * y + 1

g :: Integer -> Integer -> Integer
-- g = \y -> \x -> (+) x y
g = (+)

s :: Double -> Double -> Double -> Double
s a b c = let p = (a + b + c) / 2 in sqrt (p * (p - a) * (p - b) * (p - c))

s' :: Double -> Double -> Double -> Double
s' a b c = sqrt (p * (p - a) * (p - b) * (p - c))
            where
                p = (a + b + c) / 2

isTwo :: Int -> Bool
isTwo n = if n == 2 then True else False

month :: Int -> Int
month n = case n of 
    1 -> 31
    2 -> 28
    9 -> 30
    _ -> error "invalid month"

abs' :: (Num a, Ord a) => a -> a
abs' n
    | n > 0 = n
    | otherwise = -n

fib :: (Ord t, Num t, Num a) => t -> a
fib n 
    | n < 0 = 0
    | n == 1 = 1
    | otherwise = fib (n - 1) + fib (n - 2)

head' :: [a] -> a
head' [] = error "empty list"
head' (x:_) = x

infixr 5 <->, <+>

(<->), (<+>) :: Int -> Int -> Int
(<->) x y = x - y
(<+>) x y = x + y
