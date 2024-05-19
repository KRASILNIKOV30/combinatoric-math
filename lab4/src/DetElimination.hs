module DetElimination
    ( eliminate,
      Matrix
    ) where

type Matrix = [[Double]]

scaleRow :: Int -> Double -> Matrix -> Matrix
scaleRow i k mat = take i mat ++ [map (* k) (mat !! i)] ++ drop (i+1) mat

addRows :: Int -> Int -> Double -> Matrix -> Matrix
addRows i j k mat = take i mat ++ [zipWith (+) (mat !! i) (map (* k) (mat !! j))] ++ drop (i+1) mat

eliminate :: Matrix -> Double
eliminate mat = snd $ foldl eliminateRow (mat, 1.0) [0..length mat-1]
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
