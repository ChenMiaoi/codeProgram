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