import Debug.Trace
insert :: Ord a => a -> [a] -> [a]
insert x [] = [x]
insert x (y:ys)
    | x < y = x : y : ys
    | otherwise = y : insert x ys

insertionSort :: Ord a => [a] -> [a]
insertionSort (x:xs) = insertionSort' [] (x:xs)
    where
        insertionSort' :: Ord a => [a] -> [a] -> [a]
        insertionSort' xs [] = xs
        insertionSort' xs (y:ys) = y `insert` xs `insertionSort'` ys

--     insertionSort [] [7, 5, 12, 10]
-- ->  insertionSort (insert 7 []) [5, 12, 10]
-- ->  insertionSort (insert 5 [7]) [12, 10]
-- ->  insertionSort (insert 12 [5, 7]) [10]
-- ->  insertionSort (insert 10 [5, 7, 12]) []
-- ->  insertionSort [5, 7, 10, 12] []

insertionSort' :: Ord a => [a] -> [a]
-- insertionSort' [] = []
-- insertionSort' (x:xs) = x `insert` insertionSort' xs
insertionSort' (x:xs) = foldr insert [x] xs

--     insertionSort' [7, 5, 12, 10]
-- ->  7 `insert` insertionSort' [5, 12, 10]
-- ->  7 `insert` (5 `insert` insertionSort' [12, 10])
-- ->  7 `insert` (5 `insert` (12 `insert` insertionSort' [10]))
-- ->  7 `insert` (5 `insert` (12 `insert` (10 `insert` [])))

swaps :: Ord a => [a] -> [a]
swaps [] = []
swaps [x] = [x]
swaps (x1:x2:xs)
    | x1 > x2 = x2 : swaps (x1 : xs)
    | otherwise = x1 : swaps (x2 : xs)

--     swaps [7, 12, 3, 5, 10]
-- ->  7 : swaps [12, 3, 5, 10]
-- ->  7 : (3 : swaps [12, 5, 10])
-- ->  7 : (3 : 5 : swaps [12, 10])
-- ->  7 : (3 : (5 : (10 : swaps [12])))

fix :: Eq a => ([a] -> [a]) -> [a] -> [a]
fix f x
    | x == x' = x
    | otherwise = fix f x'
    where
        x' = f x

bubbleSort :: Ord a => [a] -> [a]
bubbleSort = fix swaps

bubbleSort' :: Ord a => [a] -> [a]
bubbleSort' xs
    | swaps xs == xs = xs
    | otherwise = bubbleSort' $ swaps xs

-- bubbleSort'' :: Ord a => [a] -> [a]
-- bubbleSort'' [] = []
-- bubbleSort'' xs = bubbleSort'' initialElements ++ [lastElement]
--     where
--         swappedxs       = swaps xs
--         initialElements = init swappedxs
--         lastElement     = last swappedxs

delete :: Eq a => a -> [a] -> [a]
delete _ [] = []
delete x (l:ls)
    | x == l = ls
    | otherwise = l:delete x ls

selectionSort :: (Eq a, Ord a) => [a] -> [a]
selectionSort [] = []
selectionSort xs = mini : selectionSort xs'
    where
        mini = minimum xs
        xs'  = delete mini xs

--     selectionSort [7, 12, 3, 5, 10]
-- ->  3 : selectionSort [7, 12, 5, 10]
-- ->  3 : 5 : selectionSort [7, 12, 10]
-- ->  3 : 5 : 7 : selectionSort [12, 10]
-- ->  3 : 5 : 7 : 10 : selectionSort [12]

quickSort :: Ord a => [a] -> [a]
quickSort [] = []
quickSort (x:xs) = quickSort mini ++ [x] ++ quickSort maxi
    where
        mini = filter (<x) xs
        maxi = filter (>=x) xs

--     quickSort [7, 12, 3, 13, 5, 10, 1]
-- ->  quickSort [3, 5, 1] ++ [7] ++ quickSort [12, 13, 10]
-- ->  (quickSort [1] ++ [3] ++ quickSort [5]) ++ [7] ++ 
--     (quickSort [] ++ [12] ++ quickSort [13, 10])

filterSplit :: (a -> Bool) -> [a] -> ([a], [a])
filterSplit _ [] = ([], [])
filterSplit f (x:xs)
    | f x = (x:l, r)
    | otherwise = (l, x:r)
    where
        (l, r) = filterSplit f xs

quickSort' :: Ord a => [a] -> [a]
quickSort' [] = []
quickSort' [x] = [x]
quickSort' (x:xs) = quickSort' l ++ [x] ++ quickSort' r
    where (l, r) = filterSplit (<x) xs

merge :: Ord a => [a] -> [a] -> [a]
merge xs [] = xs
merge [] ys = ys
merge (x:xs) (y:ys)
    | x > y = y : merge (x:xs) ys
    | otherwise = x : merge xs (y:ys)

mergeSort :: (Ord a, Show a) => [a] -> [a]
mergeSort [x] = [x]
mergeSort xs = trace ("xs: " ++ show xs ++ "x1: " ++ show x1 ++ "\nx2: " ++ show x2)
    merge (mergeSort x1) (mergeSort x2)
    where
        (x1, x2) = halve xs
        halve    = splitAt l
        l        = length xs `div` 2

--     mergeSort [4, 1, 7, 2]
-- ->  merge (mergeSort [4, 1]) (mergeSort [7, 2])
-- ->  merge (merge (mergeSort [4]) mergeSort [1]) (merge (mergeSort [7]) (mergeSort [2]))
-- -> 

