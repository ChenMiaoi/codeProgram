import Debug.Trace
romeNotation :: [String]
romeNotation = ["M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I"]

romeAmount :: [Int]
romeAmount = [1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1]

pair :: [(Int, String)]
pair = zip romeAmount romeNotation

subtrahend :: Int -> (Int, String)
subtrahend n = head $ dropWhile (\(a, _) -> a > n) pair

convert :: Int -> String
convert 0 = ""
convert n =
    let (rome, m) = subtrahend n in m ++ convert (n - rome)

--     convert 17
-- ->  IX ++ convert (17 - 10)
-- ->  IX ++ V ++ convert (7 - 5)
-- ->  IX ++ V ++ I ++ convert (2 - 1)
-- ->  IX ++ V ++ I ++ I ++ ""

reSubtrahend :: String -> (Int, String)
reSubtrahend str = trace ("str: " ++ show str ++ "\t") $ head $ dropWhile (\(_, a) -> a /= str) pair

reConvert :: String -> Int
reConvert "" = 0
reConvert str =
    let (rome, m) = reSubtrahend [head str] in trace ("rome: " ++ show rome ++ "\n") $ rome + reConvert (tail str)

i2s :: Int -> String
i2s = show

to2convert' :: Int -> String
to2convert' 0 = ""
to2convert' n = i2s (n `mod` 2) ++ to2convert' (n `div` 2)

to2convert :: Int -> String
to2convert n = reverse $ to2convert' n

binarySearch :: Ord a => a -> [a] -> Bool
binarySearch _ [] = False
binarySearch a xs
    | m < a = binarySearch a behind
    | m > a = binarySearch a front
    | otherwise = True
    where
        (front, m : behind) = splitAt (length xs `div` 2) xs

binarySearch' :: Ord a => a -> [a] -> [a]
binarySearch' _ [] = []
binarySearch' target xs = binarySearch'' target xs 0 (length xs - 1)
    where
        binarySearch'' :: Ord a => a -> [a] -> Int -> Int -> [a]
        binarySearch'' target xs left right
            | left > right = []
            | midVal == target = midVal : binarySearch'' target xs left (mid - 1) ++ binarySearch'' target xs (mid + 1) right
            | midVal < target = binarySearch'' target xs (mid + 1) right
            | otherwise = binarySearch'' target xs left (mid - 1)
                where 
                    mid = (left + right) `div` 2
                    midVal = xs !! mid