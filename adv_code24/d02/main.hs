import System.IO
import Data.Ix

fileName :: Int -> String
fileName 0 = "input.txt"
fileName _ = "teste.txt"

parseInput :: String -> [[Int]]
parseInput = map (map read . words) . lines

isSafe :: [Int] -> Bool
isSafe xs = (all (safeFunc (uncurry (<))) ys) || (all (safeFunc (uncurry (>))) ys)
    where
        ys = zip xs (tail xs)
        safeFunc :: ((Int, Int) -> Bool) -> (Int, Int) -> Bool
        safeFunc f (x, y) = f (x, y) && inRange (1, 3) (abs (x - y))

matrizGen :: [Int] -> [[Int]]
matrizGen xs = xs : [take i xs ++ drop (i + 1) xs | i <- [0 .. length xs - 1]]

solve1 :: String -> IO ()
solve1 = print . length . filter isSafe . parseInput

solve2 :: String -> IO ()
solve2 = print . length . filter (any isSafe) . map matrizGen . parseInput

main :: IO ()
main = readFile (fileName 0) >>= solve1
