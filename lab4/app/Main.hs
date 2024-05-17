module Main (main) where
import Lib (someFunc)
import DetElimination (eliminate)

main :: IO ()
main = do
  let submat = [[1, 2], [3, 4]]  -- 3x3 invertible matrix

  --contenm_headMulScal <- readFile "det_matrix(800 x 800).txt"
  --let mat = map (map read . words) (lines contenm_headMulScal) :: [[Double]]

  --let piece_dim = 600
  --let submat = subMatrix mat piece_dim

  let (refMat, determinant, rank) = eliminate submat  -- Calculate the ref matrix, determinant, and rank
  --putStrLn "Original Matrix:"
  --printMatrix submat
  putStrLn "\nDeterminant:"
  print determinant
  putStrLn "\nRank:"
  print rank

--main = someFunc

--printMatrix :: Matrix -> IO ()
--printMatrix mat = mapM_ (putStrLn . unwords . map show) mat
