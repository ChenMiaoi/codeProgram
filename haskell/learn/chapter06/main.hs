import Data.List (group)
map' :: (t -> a) -> [t] -> [a]
map' f xs = [f x | x <- xs]

filter' :: (a -> Bool) -> [a] -> [a]
filter' f xs = [x | x <- xs, f x]

length' xs = sum [1 | _ <- xs]

series :: Int -> [Double]
series n = [1 / (2 * fromIntegral k + 1) * (-1) ^ k | k <- [0..n]]

series2 :: Int -> [Double]
series2 n = [((1 / 2) ^ (2 * fromIntegral k + 1)) * (1 / (2 * fromIntegral k + 1) * (-1) ^ k) | k <- [0..n]]

series3 :: Int -> [Double]
series3 n = [((1 / 3) ^ (2 * fromIntegral k + 1)) * (1 / (2 * fromIntegral k + 1) * (-1) ^ k) | k <- [0..n]]

factors :: Integral a => a -> [a]
factors n = [x | x <- [1..n], mod n x == 0]

isPrime :: Integral a => a -> Bool
isPrime n = factors n == [1, n]

primes :: Integral a => a -> [a]
primes n = [x | x <- [1..n], isPrime x]

isPrime' :: Integral a => a -> Bool
isPrime' 2 = True
isPrime' p = 
    p > 1 && all (\n -> p `mod` n /= 0) (takeWhile (\n -> n * n <= p) [3, 5 ..])

nextPrime :: Integer -> Integer
nextPrime a 
    | odd a = if isPrime' a then a else nextPrime (a + 2)
    | otherwise = nextPrime (a + 1)

sieve :: (Integral a) => [a] -> [a]
sieve (p:xs) = p : sieve [x | x <- xs, x `mod` p /= 0]

primes' :: [Integer]
primes' = sieve [2..]

primeFactors :: Integral b => b -> [(Int, b)]
primeFactors n = convertTo $ factors n 2
    where 
        factors 1 _ = []
        factors num divisor 
            | isPrime' divisor && num `mod` divisor == 0 = divisor : factors (num `div` divisor) divisor
            | otherwise = factors num (divisor + 1)

        convertTo xs = [(length gp, head gp) | gp <- group xs]