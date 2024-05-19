module DetElimination
    ( eliminate,
      Matrix
    ) where

type Matrix = [[Double]]

-- Row operations

swapRows :: Int -> Int -> Matrix -> Matrix
swapRows i j mat = take i mat ++ [mat !! j] ++ (drop (i+1) . take j $ mat) ++ [mat !! i] ++ drop (j+1) mat

scaleRow :: Int -> Double -> Matrix -> Matrix
scaleRow i k mat = take i mat ++ [map (* k) (mat !! i)] ++ drop (i+1) mat

addRows :: Int -> Int -> Double -> Matrix -> Matrix
addRows i j k mat = take i mat ++ [zipWith (+) (mat !! i) (map (* k) (mat !! j))] ++ drop (i+1) mat

-- Gaussian elimination

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

-- Matrix operations

identityMatrix :: Int -> Matrix
identityMatrix n = [[fromIntegral (fromEnum (i == j)) | j <- [1..n]] | i <- [1..n]]

-- create sub matrix n x n from matrix mat
subMatrix :: [[Double]] -> Int -> [[Double]]
subMatrix mat n = take n (map (take n) mat)
