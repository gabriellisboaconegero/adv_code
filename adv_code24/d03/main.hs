import System.IO
import Text.Regex.Posix

fileName :: Int -> String
fileName 0 = "input.txt"
fileName 2 = "teste2.txt"
fileName _ = "teste.txt"

solve1 :: String -> IO ()
solve1 f = do
  let matches = f =~ padrao :: [[String]]
  let resultados = map (map read . drop 1) matches :: [[Int]]
  let r = sum $ map (foldr (*) 1) resultados
  print r
  where
    padrao = "mul\\(([0-9]+),([0-9]+)\\)"

solve2 :: String -> IO ()
solve2 f = do
  let matches = f =~ padrao :: [[String]]
  let inter_repre = map parse matches
  print $ run inter_repre "d"
  where
    padrao = "mul\\(([0-9]+),([0-9]+)\\)|do\\(\\)|don't\\(\\)"
    parse :: [String] -> (String, Int)
    parse (t:v1:v2:rest)
        | t == "do()" = ("d", 0)
        | t == "don't()" = ("t", 0)
        | otherwise = ("m", (read v1 :: Int) * (read v2 :: Int))
    run :: [(String, Int)] -> String -> Int
    run [] _ = 0
    run ((str, num):t) state = (if state /= "d" then 0 else num) + run t (if str /= "m" then str else state)

main :: IO ()
main = readFile (fileName 0) >>= solve2
