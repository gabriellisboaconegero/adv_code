import System.IO
import Data.List
import Data.Ix
import qualified Data.Set as Set

type V2 = (Int, Int)
type Position = V2
type Direction = V2
type State = (Position, Direction)
type Bounds = V2

fileName :: Int -> String
fileName 0 = "input.txt"
fileName x = "teste" ++ show x ++ ".txt"

-- (0, -1) -> (1, 0) -> (0, 1) -> (-1, 0)
rotate90 :: V2 -> V2
rotate90 (x, y) = (-y, x)

add :: V2 -> V2 -> V2
add (x, y) (dx, dy) = (x+dx, y+dy)

mult :: V2 -> V2 -> V2
mult (x, y) (dx, dy) = (x*dx, y*dy)

mult' :: V2 -> Int -> V2
mult' (x, y) z = (x*z, y*z)

inBound :: V2 -> Bounds -> Bool
inBound (x, y) (mX, mY) = inRange (0, mX) x && inRange (0, mY) y

computeRoute :: Bounds -> State -> Set.Set Position -> Set.Set State -> Set.Set State
computeRoute b st@(p, d) obstacles s
    | not (p `inBound` b) = s
    | Set.member st s = Set.union s (Set.singleton ((-1, -1), (-1, -1)))
    | Set.notMember p obstacles = computeRoute b ((p `add` d), d) obstacles (Set.union s (Set.singleton st))
    | otherwise = computeRoute b ((p `add` (d `mult'` (-1))) `add` (rotate90 d), rotate90 d) obstacles s

solve1 :: String -> IO ()
solve1 input = print result
    where
        l = lines input
        mX = (length $ head l) - 1
        mY = (length l) - 1
        mat = concat $ zipWith (\y linha -> zipWith (\x c -> ((x, y), c)) [0..] linha) [0..] l
        obstacles = Set.fromList $ map fst $ filter ((=='#') . snd) mat
        guard = fst $ head $ filter ((=='^') . snd) mat
        result = Set.size $ Set.map fst $ computeRoute (mX, mY) (guard, (0, -1)) obstacles Set.empty

solve2 :: String -> IO ()
solve2 input = print result
    where
        l = lines input
        mX = (length $ head l) - 1
        mY = (length l) - 1
        mat = concat $ zipWith (\y linha -> zipWith (\x c -> ((x, y), c)) [0..] linha) [0..] l
        obstacles = Set.fromList $ map fst $ filter ((=='#') . snd) mat
        guard = fst $ head $ filter ((=='^') . snd) mat

        newObstacles = Set.map fst $ computeRoute (mX, mY) (guard, (0, -1)) obstacles Set.empty
        result = Set.size $ Set.filter (\op ->
            let route = computeRoute (mX, mY) (guard, (0, -1)) (Set.insert op obstacles) Set.empty
            in Set.member ((-1, -1), (-1, -1)) route
            ) newObstacles

main :: IO ()
main = readFile (fileName 0) >>= solve2

