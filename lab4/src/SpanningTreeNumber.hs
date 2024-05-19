module SpanningTreeNumber
    ( determinant,
      Matrix,
      kirchhoffMatrix,
      spanningTreeNumber
    ) where
import GHC.Float (int2Double)

type Matrix = [[Double]]

scaleRow :: Int -> Double -> Matrix -> Matrix
scaleRow i k mat = take i mat ++ [map (* k) (mat !! i)] ++ drop (i+1) mat

addRows :: Int -> Int -> Double -> Matrix -> Matrix
addRows i j k mat = take i mat ++ [zipWith (+) (mat !! i) (map (* k) (mat !! j))] ++ drop (i+1) mat

determinant :: Matrix -> Double
determinant mat = snd $ foldl eliminateRow (mat, 1.0) [0..length mat-1]
  where
    eliminateRow (mat, detAccum) row = foldr eliminateEntry (mat, detAccum) [0..length mat-1]
      where
        eliminateEntry col (mat, detAccum)
          | row == col = (scaleRow row (1 / pivot) mat, detAccum * pivot)
          | mat !! col !! row /= 0 = (addRows col row (-ratio) mat, detAccum)
          | otherwise = (mat, detAccum)
          where
            pivot = mat !! row !! row
            ratio = (mat !! col !! row) / pivot

degree :: Int -> Matrix -> Int
degree i mat = length $ filter (/= 0) (mat !! i)

mapInd :: (a -> Int -> b) -> [a] -> [b]
mapInd f l = zipWith f l [0..]

subMat :: Matrix -> Matrix
subMat mat = take n (map (take n) mat)
  where n = length mat - 1

kirchhoffMatrix :: Matrix -> Matrix
kirchhoffMatrix mat = mapInd kirchhoffRow mat
  where
    kirchhoffRow row i = mapInd kirchhoffElement row
      where
        kirchhoffElement v j
           | i == j = int2Double $ degree i mat
           | v /= 0 = -1
           | otherwise = 0

spanningTreeNumber :: Matrix -> Int
spanningTreeNumber mat = round $ determinant (subMat $ kirchhoffMatrix mat)