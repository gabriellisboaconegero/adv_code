import System.IO
import Data.List.Split
import Data.Graph

fileName :: Int -> String
fileName 0 = "input.txt"
fileName x = "teste" ++ show x ++ ".txt"

type Rules = [(Int, Int)]
type PageOrdening = [Int]
type PagesProduced = [PageOrdening]

parse :: String -> (PagesProduced, Rules)
parse input = ((aux2 $ drop 1 $ dropWhile (not . null) l), (aux1 $ takeWhile (not . null) l))
    where
        l = lines input

        aux1 :: [String] -> Rules
        aux1 [] = []
        aux1 (h:t) = [(read (take 2 h), read (drop 3 h))] ++ aux1 t

        aux2 :: [String] -> PagesProduced
        aux2 [] = []
        aux2 (h:t) = [map (\x -> read x :: Int) $ splitOn "," h] ++ aux2 t

buildGraph :: PageOrdening -> Rules -> Graph
buildGraph po r = buildG (0, maximum (concatMap (\(x, y) -> [x, y]) v)) v
    where
        v = r ++ (zipWith (\x y -> (x, y)) po (tail po))

isCorrectOrder :: Graph -> Bool
isCorrectOrder g = (length $ vertices g) == (length $ scc g)

-- Ideia: Pegr as regras que contem os vlores dentro da ordem e fazer um DAG.
-- Adiciona arestas ao DAG com base na ordem passda.
-- Verifica se virou um DAG, se sim pega o livro do meio
solve1 :: String -> IO ()
solve1 input = print result
    where
        (pp, r) = parse input
        mask = map (\z -> isCorrectOrder $ buildGraph z $ filter (\(x, y) -> (x `elem` z) && (y `elem` z)) r) pp
        correctOrders = map snd $ filter fst $ zip mask pp
        result = sum $ map (\x -> head $ drop ((length x) `div` 2) x) correctOrders

-- Ideia: Pegr as regras que contem os vlores dentro da ordem e fazer um DAG.
-- Adiciona arestas ao DAG com base na ordem passda.
-- Verifica se virou um DAG, se não então faz a ordenação topologica do DAG com apenas as regras
-- Somao livros do meio da ordenação
solve2 :: String -> IO ()
solve2 input = print result
    where
        (pp, r) = parse input
        mask = map (\z -> isCorrectOrder $ buildGraph z $ filter (\(x, y) -> (x `elem` z) && (y `elem` z)) r) pp
        incorrectOrders = map snd $ filter (not . fst) $ zip mask pp
        result = sum $ map (\z -> head $ drop ((length z) `div` 2) $ filter (`elem` z) $ topSort $ buildGraph [] $ filter (\(x, y) -> (x `elem` z) && (y `elem` z)) r) incorrectOrders

main :: IO ()
main = readFile (fileName 0) >>= solve2
