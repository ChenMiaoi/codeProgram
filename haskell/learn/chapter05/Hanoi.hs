-- h (n) = 1 (n = 1)
-- h (n) = 2h (n - 1) + 1 (n > 1)

move :: (Int, Int, Int, Int) -> [(Int, Int)]
move (1, from, to, via) = [(from, to)]
move (n, from, to, via) = move (n - 1, from, via, to) 
                          ++ [(from, to)] ++ 
                          move (n - 1, via, to, from)

hanoi :: Int -> [(Int, Int)]
hanoi n = move (n, 1, 2, 3)