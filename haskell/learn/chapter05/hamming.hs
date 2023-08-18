mergeUni :: Ord a => [a] -> [a] -> [a]
mergeUni xs [] = xs
mergeUni [] ys = ys
mergeUni (x:xs) (y:ys)
    | x > y = y : mergeUni (x:xs) ys
    | x < y = x : mergeUni xs (y:ys)
    | otherwise = x : mergeUni (x `delete` xs) (x `delete` ys)
    where
        delete :: Eq a => a -> [a] -> [a]
        delete _ [] = []
        delete n (l:ls)
            | n == l = delete n ls
            | otherwise = l : delete n ls

ham :: (Ord a, Num a) => [a]
ham = 1 : mergeUni (map (*2) ham) (mergeUni (map (*3) ham) (map (*5) ham))