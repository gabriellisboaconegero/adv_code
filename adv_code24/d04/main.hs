import System.IO
import Data.List

fileName :: Int -> String
fileName 0 = "input.txt"
fileName x = "teste" ++ show x ++ ".txt"

rotate90 :: [[a]] -> [[a]]
rotate90 = reverse . transpose

indexedGrid :: [[a]] -> [((Int, Int), a)]
indexedGrid grid = [((i, j), c) | (i, row) <- zip [0..] grid, (j, c) <- zip [0..] row]

getDiagonals :: [[a]] -> [[a]]
getDiagonals grid = groupDiags (indexedGrid grid) (+)

getAntiDiagonals :: [[a]] -> [[a]]
getAntiDiagonals grid = groupDiags (indexedGrid grid) (-)

groupDiags :: [((Int, Int), a)] -> (Int -> Int -> Int) -> [[a]]
groupDiags grid key =
    map (map snd) $ groupBy (\(k1, _) (k2, _) -> uncurry key k1 == uncurry key k2) $
    sortOn (\((i, j), _) -> key i j) grid

countSubstrings :: String -> String -> Int
countSubstrings _ "" = 0
countSubstrings sub str = (if sub `isPrefixOf` str then 1 else 0) + countSubstrings sub (tail str)

getXMAS :: [String] -> Int
getXMAS = sum . map (\str -> (countSubstrings "XMAS" str) + (countSubstrings "SAMX" str))

solve1 :: String -> IO ()
solve1 input = do
    let grid = lines input
    print $ getXMAS grid + getXMAS (rotate90 grid) + getXMAS (getDiagonals grid) + getXMAS (getAntiDiagonals grid)

getGridPos :: [String] -> Int -> Int -> Char
getGridPos grid i j = (grid !! i) !! j

getCharVal :: Char -> Int
getCharVal 'S' = 1
getCharVal 'M' = -1
getCharVal _ = 10

getVal :: [String] -> Int -> Int -> Int
getVal grid i j = getCharVal $ getGridPos grid i j

getI :: Int -> Int -> Int
getI len id = (id `div` (len - 2)) + 1 

getJ :: Int -> Int -> Int
getJ len id = (id `mod` (len - 2)) + 1

-- countMAS :: [String] -> Int -> Int
-- countMAS grid id
--     | id >= (length grid - 2)*(length (head grid) - 2) = 0
--     | getGridPos grid i j == 'A' = (if getVal grid (i - 1) (j - 1) +
--                                    getVal grid (i - 1) (j + 1) +
--                                    getVal grid (i + 1) (j - 1) +
--                                    getVal grid (i + 1) (j + 1) == 0 then 1 else 0) +
--                                    countMAS grid (id+1)
--     | otherwise = countMAS grid (id+1)
--     where
--         i = (id `div` (length grid - 2)) + 1
--         j = (id `mod` (length (head grid) - 2)) + 1
countMAS :: [String] -> Int -> Int
countMAS grid id
    | id >= (length grid - 2)*(length (head grid) - 2) = 0
    | getGridPos grid i j == 'A' = (if sum sum_ == 0 && s then 1 else 0) +
                                   countMAS grid (id+1)
    | otherwise = countMAS grid (id+1)
    where
        i = getI (length grid) id
        j = getJ (length (head grid)) id
        sum_ = getVal grid (i - 1) (j - 1) :
              getVal grid (i - 1) (j + 1) :
              getVal grid (i + 1) (j - 1) :
              getVal grid (i + 1) (j + 1) : []
        s = (sum_ !! 0) == (sum_ !! 1) || (sum_ !! 0) == (sum_ !! 2)

solve2 :: String -> IO ()
solve2 input = do
    let grid = lines input
        -- a = [((id `div` (length grid - 2)) + 1, (id `mod` (length (head grid) - 2)) + 1) | id <- [0 .. (length grid - 2)*(length (head grid) - 2) - 1]]
    -- print a
    -- let t = [(getI (length grid) id, getJ (length (head grid)) id, sum_) | (id, sum_) <- countMAS grid 0]

    -- print t
    -- print (length t)
    print $ countMAS grid 0

main :: IO ()
main = readFile (fileName 0) >>= solve2
