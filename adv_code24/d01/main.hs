import System.IO
import Data.List
import qualified Data.Map as Map

fileName :: Int -> String
fileName 0 = "input.txt"
fileName _ = "teste.txt"


type T1 = ([Int], [Int])
type T2 = ([Int], Map.Map Int Int)

getLists :: String -> T1
getLists = processar . lines
    where
        processar :: [String] -> T1
        processar [] = ([], [])
        processar (linha:resto) = (num1:o1, num2:o2)
            where
                [num1, num2] = map read (words linha) :: [Int]
                (o1, o2) = processar resto


sortLists :: T1 -> T1
sortLists (l1, l2) = (sort l1, sort l2)

interpolate :: T1 -> Int
interpolate ([], []) = 0
interpolate (l1, l2) = abs((head l1) - (head l2)) + (interpolate (tail l1, tail l2))

solve1 :: String -> IO ()
solve1 = print . interpolate . sortLists . getLists

getFreqs :: T1 -> T2
getFreqs (l1, l2) = (l1, Map.fromList $ map (\x -> (head x, length x)) $ groupBy (==) l2)

interpolate2 :: T2 -> Int
interpolate2 ([], _) = 0
interpolate2 (val:resto, freqs) = val * (Map.findWithDefault 0 val freqs) + (interpolate2 (resto, freqs))

solve2 :: String -> IO ()
solve2 = print . interpolate2 . getFreqs . sortLists . getLists

main :: IO ()
main = readFile (fileName 0) >>= solve1
