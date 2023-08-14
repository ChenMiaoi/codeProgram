import Prelude hiding ((!!), takeWhile, dropWhile,
    splitAt, replicate, elem, concatMap, partition)

filter' :: [Double]
filter' = filter (\x -> x ** 2 + 7 > 30) [1..50]


(!!) :: [a] -> Int -> a
(!!) [] _ = error "This list is empty"
(!!) (x:_) 0 = x
(!!) (_:xs) n = (!!) xs (n - 1)
-- (!!) (_:xs) n = (!!) (take n xs) (n - 1)
-- (!!) (_:xs) n = (!!) (drop (n - 1) xs) 0

infixl 5 !!

takeWhile, dropWhile :: (a -> Bool) -> [a] -> [a]
takeWhile _ [] = []
takeWhile f xs = fst $ span f xs
dropWhile _ [] = []
dropWhile f xs = snd $ span f xs

splitAt :: Int -> [a] -> ([a], [a])
splitAt n xs = (take n xs, drop n xs)

replicate :: Int -> a -> [a]
replicate n a = take n (repeat a)

elem :: Eq a => a -> [a] -> Bool
-- elem a xs = not (null (filter (==a) xs))
elem a xs = not $ any (==a) xs

concatMap :: (a -> [b]) -> [a] -> [b]
concatMap f xs = concat $ map f xs

type Weekday = Int
type Year = Int
type Month = Int
type Day = Int

week :: Year -> Day -> Weekday
week y d = (y1 + div y1 4 - div y1 100 + div y1 300 + d) `mod` 7
    where
        y1 = y - 1

isLeapYear :: Int -> Bool
isLeapYear y = (mod y 4 == 0) && (mod y 100 /= 0) || (mod y 400 == 0)

montyDays :: Year -> Month -> Int
montyDays y m
    | m == 2 = if not $ isLeapYear y then 28 else 29
    | m `elem` [1, 3, 5, 7, 8, 10, 12] = 31
    | m `elem` [4, 6, 9, 11] = 30
    | otherwise = error "invalid month"

accDays :: Year -> Month -> Day -> Int
accDays y m d
    | d > montyDays y m = error "invalid days"
    | otherwise = sum (take (m - 1) (map (montyDays y) [1..12])) + d

contains6 :: [String]
contains6 = filter (elem '6') (map show [1..100])

contains6' :: [Int]
contains6' = map (\str -> read str :: Int) $ filter (elem '6') (map show [1..100])

reverseSentence :: String -> String
reverseSentence str = unwords $ reverse $ words str
-- reverseSentence = unwords $ reverse $ words

partition :: (a -> Bool) -> [a] -> ([a], [a])
partition f xs = (filter f xs, filter (\x -> not $ f x) xs)