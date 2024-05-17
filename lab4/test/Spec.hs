import Test.HUnit
import DetElimination (eliminate, Matrix)

approxN :: Int
approxN = 7

approx :: Double -> Double
approx x = fromInteger (round $ x * (10^approxN)) / (10.0^^approxN)

-- assert approximate equality
assertApproxEqual :: String -> Double -> Double -> Assertion
assertApproxEqual prefix x1 x2 =
  assertEqual prefix (approx x1) (approx x2)

getThird :: (a, b, c) -> b
getThird (_, b,_) = b

getDet :: Matrix -> Double
getDet = getThird . eliminate

test1 :: Test
test1 = TestCase $ assertApproxEqual "quadratic matrix"
    (getDet [
        [1, 2],
        [3, 4]
    ])
    (-2)

test2 :: Test
test2 = TestCase $ assertApproxEqual "simple matrix"
    (getDet [[0]]) 0

test3 :: Test
test3 = TestCase $ assertApproxEqual "3x3 matrix"
    (getDet [
        [2, 3, 10],
        [100, 5.5, 0],
        [91, 7, 3.33]
    ])
    1032.63

test4 :: Test
test4 = TestCase $ assertApproxEqual "100x100 matrix"
    (getDet [
        [97,8,72,82,41,37,14,88,15,19,67,84,23,81,38,50,25,34,43,82,90,4,58,70,67,98,33,90,15,46,70,42,8,90,88,81,62,2,12,91,41,41,6,31,68,41,77,63,89,5,90,87,49,43,56,18,85,84,92,26,87,6,20,11,95,23,82,27,77,51,87,73,91,99,31,65,81,59,34,97,58,73,37,43,30,7,67,81,81,75,86,90,1,65,18,3,91,43,91,46],
        [60,55,51,17,12,27,2,69,69,89,15,21,56,4,68,10,48,2,43,50,50,85,69,92,34,35,33,25,26,29,77,96,34,84,12,39,76,83,13,76,36,51,93,79,24,97,1,62,1,71,56,61,89,27,0,28,15,26,67,81,23,93,75,65,98,89,55,11,20,27,25,66,86,76,87,49,12,53,14,15,50,9,26,30,63,89,65,10,83,0,23,74,68,75,89,14,98,72,70,62],
        [85,67,21,29,63,5,35,38,25,9,81,62,36,67,95,40,36,7,58,61,72,58,71,37,52,68,14,63,46,4,10,4,52,86,93,78,5,67,14,74,34,55,17,98,5,40,44,48,26,80,18,71,92,24,68,57,20,38,20,67,34,1,40,21,63,82,86,29,66,12,1,60,20,91,68,73,73,12,4,23,0,57,73,26,75,70,70,36,97,37,80,76,37,41,95,98,59,33,59,17],
        [49,84,43,93,66,16,54,83,31,72,98,49,36,55,53,69,61,66,29,49,24,41,4,80,33,53,3,22,85,31,88,57,78,22,85,18,76,99,47,8,65,4,63,71,96,85,93,11,98,65,82,99,54,92,18,65,46,48,41,57,9,87,14,29,34,16,13,13,39,54,43,11,92,70,1,55,27,3,13,32,14,68,44,63,56,83,10,44,16,54,75,56,96,85,13,58,58,17,99,47],
        [55,46,19,85,25,57,33,49,54,71,28,12,92,80,21,26,37,55,4,12,12,10,55,62,30,9,73,65,66,44,60,78,70,17,57,53,85,9,41,18,58,26,33,11,80,88,74,4,65,60,31,24,56,47,37,86,31,24,66,32,59,37,25,92,7,40,66,29,75,44,36,1,71,67,8,85,14,71,73,95,49,32,82,17,25,93,66,50,96,81,25,69,37,97,83,28,59,52,46,51],
        [78,65,12,32,23,22,41,45,73,25,69,77,10,92,7,45,52,28,81,95,77,80,95,40,36,64,55,28,1,70,56,74,75,46,38,62,41,80,35,56,70,71,45,55,68,35,85,32,65,13,67,59,73,39,54,86,65,57,55,54,2,1,93,10,54,9,14,31,70,26,0,53,90,50,70,29,19,40,7,87,39,88,83,3,1,29,13,18,35,19,95,8,4,27,20,85,1,76,93,35],
        [37,49,40,84,40,16,59,98,42,99,59,8,46,98,73,5,88,4,39,35,69,80,52,78,99,43,31,29,38,49,8,32,20,28,30,40,96,3,80,44,72,13,59,6,16,95,9,10,76,92,81,39,19,47,84,47,69,78,83,27,46,99,2,93,33,66,56,62,56,36,50,59,45,25,35,22,72,25,52,31,20,45,45,74,27,41,68,62,77,94,25,56,56,61,3,74,9,56,87,42],
        [78,10,16,36,37,93,36,32,32,71,71,10,32,39,37,76,39,84,41,72,56,85,62,46,13,64,31,71,92,30,91,98,83,8,36,15,26,23,47,94,70,63,86,37,20,21,90,94,2,16,44,78,45,77,11,39,56,4,55,15,52,7,8,91,36,25,0,20,29,3,68,5,88,78,29,55,46,79,90,71,70,68,11,3,36,79,62,54,57,46,14,80,86,26,11,47,73,63,66,9],
        [4,9,82,6,37,68,78,25,50,55,20,46,24,44,41,52,16,69,37,29,61,72,21,13,58,71,30,33,56,70,2,82,4,42,83,87,20,2,1,5,73,85,14,29,16,67,57,48,30,37,32,62,86,72,18,33,73,89,61,54,81,36,93,66,14,39,81,12,57,1,84,17,79,34,98,38,37,79,79,41,8,95,21,11,29,46,67,11,46,67,38,75,5,28,65,26,44,32,37,55],
        [16,57,27,23,90,97,59,67,7,2,61,92,43,72,12,37,83,27,17,97,76,69,69,85,21,92,43,26,67,85,53,30,35,6,57,65,48,40,90,57,18,39,35,23,50,12,93,55,43,85,77,73,14,3,26,45,62,90,80,93,17,10,48,54,5,75,3,32,80,66,59,62,16,63,78,26,37,7,81,69,65,78,80,19,67,18,2,56,2,16,38,13,96,33,67,13,13,92,5,75],
        [20,87,52,33,23,73,66,30,6,26,77,70,25,37,81,54,39,69,84,93,86,37,81,73,66,66,51,45,29,52,48,71,41,46,56,77,42,21,23,97,45,22,95,70,16,22,22,82,65,15,31,56,81,79,35,36,6,65,41,38,93,39,36,28,70,92,99,43,78,71,98,72,34,12,27,81,54,29,21,19,77,72,33,39,25,78,4,22,77,50,85,11,44,92,34,81,57,79,35,37],
        [6,67,64,85,77,64,82,4,77,12,21,88,37,42,92,30,12,77,9,75,24,13,58,88,49,24,79,31,53,56,0,23,65,18,73,30,98,78,99,60,32,22,90,20,16,24,8,30,45,27,16,9,62,77,64,91,94,91,70,76,30,95,60,32,94,44,77,12,20,7,83,0,73,64,74,12,56,47,21,15,71,16,87,20,79,32,56,93,75,19,9,84,76,69,50,84,55,18,70,74],
        [54,16,83,8,86,42,27,71,55,95,66,59,25,24,24,23,70,60,43,63,7,52,33,1,17,47,15,18,48,66,29,73,74,2,95,9,79,17,38,93,40,18,26,56,38,42,95,22,66,30,30,88,56,58,0,7,61,60,52,50,29,48,53,50,16,77,20,77,26,10,81,43,2,34,13,1,40,55,33,93,38,29,90,93,94,23,44,91,35,33,6,33,59,43,97,44,28,5,46,41],
        [95,34,6,39,71,7,12,56,43,88,59,65,85,74,7,71,89,62,96,29,83,81,72,86,61,80,23,22,9,5,26,21,61,86,15,45,28,88,98,58,86,30,76,4,60,80,96,77,60,46,98,7,56,68,26,94,98,63,37,76,81,45,86,29,62,6,20,73,54,88,44,98,77,61,79,17,55,47,92,26,69,44,14,3,77,82,64,24,6,78,63,33,3,13,15,14,57,87,98,58],
        [92,19,28,12,24,75,84,38,9,22,27,63,62,82,40,69,95,79,38,96,45,72,43,80,70,62,34,31,3,97,38,64,86,31,25,44,4,42,88,88,27,12,72,16,83,99,91,54,13,55,20,54,72,90,88,78,64,29,37,89,22,91,8,96,7,0,95,29,54,36,66,91,88,73,91,75,42,98,54,31,51,39,79,74,24,28,62,33,93,48,10,20,52,27,97,42,14,31,89,95],
        [29,2,85,20,90,8,98,15,70,20,41,2,27,38,16,81,93,95,75,26,29,82,32,2,18,96,8,42,83,52,11,56,52,49,98,57,43,57,48,97,20,92,1,26,63,21,64,70,97,57,39,29,81,86,48,84,2,30,12,79,89,22,17,41,15,12,88,80,49,95,74,1,61,75,59,67,7,63,73,17,76,31,70,83,24,52,19,92,33,6,79,58,20,60,15,21,38,84,44,33],
        [92,94,27,63,38,25,66,93,11,56,93,55,0,31,58,59,63,96,69,81,84,21,5,19,35,54,42,4,77,40,42,1,6,31,46,9,22,36,67,71,65,9,26,8,11,51,65,55,12,4,87,4,54,56,53,23,15,97,62,40,29,97,41,7,69,46,17,74,8,37,56,84,34,37,73,66,43,68,1,55,80,49,52,25,32,96,21,72,41,31,37,52,90,73,21,35,3,24,31,23],
        [8,6,70,17,74,45,62,97,57,8,16,79,23,9,87,55,41,46,44,50,18,3,26,17,33,77,14,92,54,16,59,82,26,22,10,11,7,94,85,40,31,14,9,96,22,72,89,42,87,24,73,67,9,59,50,53,48,90,79,24,42,45,27,8,24,64,66,96,34,59,78,11,2,10,37,34,3,12,20,25,18,28,83,43,91,94,93,1,8,55,77,52,44,48,49,74,10,41,67,13],
        [65,8,9,92,6,19,14,26,15,39,13,21,74,2,5,59,19,32,1,40,98,96,24,86,75,33,45,6,5,73,67,42,44,50,81,23,72,63,79,36,18,44,74,70,92,24,18,54,11,26,30,42,92,41,58,38,64,49,56,4,59,57,10,86,80,83,70,41,94,92,25,12,50,80,70,43,41,11,14,51,42,2,71,60,49,95,61,63,81,79,71,67,53,21,65,79,2,35,76,23],
        [9,31,26,70,17,38,53,5,90,20,75,71,23,98,33,53,23,73,2,22,8,17,80,69,67,20,86,21,48,57,32,84,21,30,49,4,98,53,42,60,83,38,88,52,13,10,19,5,37,57,64,85,10,3,64,2,89,26,15,20,89,91,6,15,44,22,24,37,70,35,55,54,73,74,73,57,39,27,10,45,45,64,68,71,34,37,29,35,84,94,72,8,75,18,72,17,16,42,66,45],
        [0,56,12,35,59,22,78,16,74,74,34,51,16,70,60,77,82,43,76,40,90,97,81,38,85,38,53,28,66,24,68,6,26,43,71,23,27,38,22,47,15,89,12,21,99,18,85,12,46,66,21,61,62,23,49,77,98,5,30,6,10,46,20,29,24,75,2,1,26,14,97,53,21,30,68,88,63,24,17,5,40,43,46,23,3,89,18,23,79,65,57,3,31,85,83,83,89,92,28,95],
        [39,28,86,42,68,48,17,49,31,37,84,81,70,35,28,71,41,89,8,19,91,92,97,35,1,50,58,19,67,61,85,19,48,8,67,17,18,33,79,66,94,4,81,49,30,14,77,71,45,81,70,66,58,51,75,94,85,66,52,10,56,49,42,31,15,37,63,65,14,60,67,25,10,8,29,42,82,56,61,87,10,1,99,74,83,24,4,76,16,55,7,36,70,2,96,44,55,44,8,26],
        [45,74,70,69,91,96,8,67,42,46,56,59,10,35,71,36,27,63,90,57,87,96,73,91,94,47,64,72,90,68,26,92,45,82,70,45,56,74,77,97,46,67,8,93,98,23,23,12,20,5,64,45,97,92,26,96,31,90,10,80,15,79,31,33,64,94,22,56,44,80,74,30,32,15,71,58,36,22,52,19,16,71,19,44,35,74,29,90,76,93,35,78,55,44,94,36,37,7,56,60],
        [12,10,34,21,2,47,64,10,44,48,58,60,12,39,32,19,15,48,55,8,41,13,77,98,72,50,61,2,43,82,76,89,32,65,28,91,98,37,87,32,70,45,12,3,62,0,24,23,69,26,81,91,18,56,28,89,84,87,37,60,86,76,25,4,4,13,8,21,77,22,22,38,75,48,71,41,11,54,61,38,91,49,54,10,29,94,55,45,94,36,97,89,5,30,75,50,79,57,38,28],
        [74,92,22,91,2,80,55,28,38,59,26,90,63,41,18,50,74,84,27,87,32,10,73,2,80,22,8,70,41,49,75,83,98,91,88,43,43,88,83,39,76,55,18,85,64,9,20,9,2,43,9,80,75,3,36,91,41,19,84,87,29,78,47,73,9,19,74,26,76,26,75,10,31,1,49,31,55,41,19,16,41,17,42,17,13,93,77,14,49,29,83,33,31,67,89,60,91,81,8,12],
        [1,61,76,54,4,4,45,64,91,56,19,83,75,12,99,46,79,81,20,27,38,12,3,97,58,87,74,67,5,29,11,95,77,4,15,56,55,70,57,82,44,30,56,77,13,11,53,4,60,62,6,94,56,85,33,23,58,32,19,58,94,81,61,81,29,76,43,73,84,7,22,85,96,92,39,74,93,28,30,1,42,64,22,62,92,4,39,58,24,91,42,22,94,93,54,93,81,95,16,89],
        [7,29,22,1,69,82,90,8,25,34,24,17,14,72,63,32,19,41,89,62,43,3,77,22,53,76,2,50,31,26,99,39,78,18,94,55,74,13,37,97,82,67,45,74,77,89,26,71,86,96,5,95,38,96,4,20,81,99,1,29,65,30,94,48,89,45,81,36,43,45,36,4,55,37,91,57,99,69,89,59,13,65,30,44,41,70,17,34,75,28,90,39,58,70,25,17,52,93,88,96],
        [26,61,91,65,2,14,10,36,12,18,82,30,92,88,85,84,60,92,2,1,40,34,27,57,93,35,9,82,31,88,12,70,18,68,2,72,23,70,22,79,32,98,13,71,59,81,5,48,79,7,77,61,60,56,39,11,9,33,57,87,92,19,52,31,87,9,93,89,18,34,92,45,66,82,30,5,56,81,52,57,50,27,6,53,6,88,51,59,79,62,20,86,48,71,8,77,98,48,88,89],
        [41,50,24,28,16,8,35,21,89,48,83,96,78,30,30,87,89,31,17,80,77,2,79,12,29,75,49,29,74,75,76,7,1,34,71,63,66,7,40,38,28,29,51,45,48,36,87,14,54,23,28,97,52,25,90,60,67,67,61,9,52,73,4,64,2,4,36,69,25,32,63,32,50,60,76,45,55,1,29,21,36,27,35,29,93,18,11,31,63,57,89,24,20,40,87,14,10,74,72,3],
        [95,40,71,54,1,72,59,42,93,49,74,57,70,12,22,49,64,20,10,14,30,15,33,85,21,86,71,88,24,19,29,20,61,93,87,94,21,90,36,35,51,66,37,94,92,90,82,40,91,5,92,1,68,61,35,61,4,76,83,49,15,34,1,78,22,53,73,66,84,11,93,58,31,14,58,42,44,21,53,88,39,29,27,1,53,44,27,10,26,75,42,60,27,88,81,59,54,55,1,54],
        [69,87,9,87,46,38,11,15,88,69,22,45,22,83,34,85,63,46,69,20,97,96,95,72,87,90,45,27,63,93,41,25,83,22,51,16,91,39,76,83,24,78,68,47,3,86,99,21,3,64,38,3,37,26,36,88,50,67,96,98,12,28,97,56,80,26,11,32,91,76,23,47,0,72,78,95,85,16,49,61,80,28,18,20,63,16,40,97,10,80,30,66,98,60,58,12,34,20,86,74],
        [34,58,67,24,30,89,93,39,7,46,55,71,10,95,74,56,38,29,8,12,86,31,6,13,91,9,16,34,96,53,94,6,12,82,62,77,55,96,39,19,19,16,68,57,59,85,59,36,93,58,24,12,64,37,33,55,42,13,52,25,78,7,80,10,14,33,76,11,61,55,1,27,65,5,27,76,52,92,25,88,53,3,19,66,64,87,17,65,60,81,93,37,20,28,98,37,3,44,96,56],
        [34,9,5,66,5,29,82,39,90,99,10,10,45,46,86,22,93,73,26,49,16,92,19,47,88,90,97,7,67,65,99,43,69,17,48,78,61,91,61,85,64,44,77,2,2,1,0,96,30,43,18,23,74,16,74,98,47,34,92,12,28,77,97,74,60,44,12,32,47,99,62,54,50,42,29,45,4,25,93,63,68,68,2,15,7,35,2,2,33,81,70,13,48,59,84,75,8,30,68,31],
        [96,94,55,53,16,6,6,63,50,3,96,54,48,87,56,55,34,15,62,60,48,96,69,57,54,21,86,91,93,67,82,5,80,78,77,43,14,77,89,82,5,67,31,5,97,73,68,83,88,3,69,95,56,51,0,61,72,42,61,87,43,43,52,23,6,12,79,34,72,47,73,65,46,78,93,55,55,27,3,48,17,19,53,56,68,6,29,32,52,20,20,83,41,49,1,34,92,46,71,36],
        [80,26,22,74,95,93,46,89,94,84,56,78,77,11,29,2,38,68,97,13,70,15,17,59,56,4,59,60,67,84,83,80,55,33,80,34,65,9,46,98,93,77,54,96,88,57,17,37,9,91,54,66,71,56,43,27,80,80,19,27,29,78,93,4,55,91,18,12,30,87,41,77,29,35,96,77,41,54,76,68,4,89,44,86,35,20,44,67,97,55,38,91,13,76,15,17,44,80,46,83],
        [9,25,82,37,63,93,60,58,8,21,26,11,15,62,89,34,81,14,35,26,20,91,50,75,36,28,68,20,17,54,42,84,81,92,81,86,1,84,52,86,85,52,38,33,63,41,68,43,41,86,29,83,91,33,37,22,43,61,64,76,5,18,11,75,18,69,69,42,3,90,65,14,36,38,26,78,75,44,26,84,65,41,9,43,3,44,93,78,22,96,7,38,56,88,96,23,88,11,3,64],
        [65,73,43,33,88,61,22,65,9,38,29,6,71,22,64,97,33,96,65,77,85,31,62,92,22,26,1,71,11,65,88,40,65,37,6,13,70,93,8,80,15,36,45,13,93,29,91,26,72,61,71,89,62,6,45,18,14,93,8,4,14,97,72,51,47,39,6,1,25,29,31,62,38,38,77,57,24,88,5,90,32,92,87,97,3,86,74,89,18,25,93,64,93,91,8,90,41,25,83,50],
        [25,93,48,97,17,98,35,44,75,77,74,62,14,58,46,51,10,54,53,70,45,29,92,53,97,52,84,10,92,62,50,88,94,56,8,38,73,61,19,79,46,74,87,79,86,85,85,56,66,7,76,76,24,45,41,75,14,80,41,55,42,63,20,88,92,25,9,44,72,57,87,17,88,95,68,13,5,16,8,70,55,69,76,99,67,87,44,2,4,33,11,60,24,82,25,34,67,46,6,88],
        [42,27,47,61,25,73,22,34,82,12,57,20,61,90,51,15,87,18,88,47,87,39,16,48,79,61,91,78,43,21,79,23,8,72,83,48,19,5,70,28,75,41,39,73,70,2,74,59,23,73,1,94,28,41,71,81,36,31,17,30,69,67,6,38,54,61,74,36,9,62,15,39,18,97,69,33,16,66,56,83,55,19,88,3,20,0,31,45,50,95,88,51,9,26,24,24,26,29,36,81],
        [15,65,26,86,43,81,43,61,50,40,52,65,21,47,32,20,28,58,75,87,58,29,76,11,73,25,77,13,36,1,7,86,69,58,2,33,95,45,37,90,32,54,25,86,56,46,70,25,45,45,75,7,32,67,50,78,51,76,13,65,15,23,40,72,17,28,10,9,36,64,6,9,73,64,19,84,43,54,42,81,34,58,38,26,6,15,22,30,93,37,85,46,28,58,25,14,40,63,92,44],
        [54,49,42,88,85,30,8,11,82,20,23,1,77,51,29,68,52,44,64,39,45,12,65,59,9,10,5,21,29,87,80,44,68,11,97,61,8,58,43,67,82,40,49,36,78,85,92,43,41,43,70,45,66,41,77,15,64,82,86,23,16,89,5,40,11,59,69,14,7,26,21,59,40,16,92,27,4,41,82,93,75,63,72,51,15,43,58,61,36,48,11,76,48,19,11,44,94,54,20,83],
        [63,93,8,10,20,22,8,24,10,54,48,30,64,16,46,6,77,77,70,16,91,76,67,4,1,16,46,69,30,17,68,74,14,24,77,20,23,13,27,50,18,91,6,2,29,6,98,23,82,50,90,11,94,63,25,76,48,43,40,64,70,65,21,90,94,32,79,29,39,78,64,46,72,73,80,19,2,17,24,59,47,17,40,65,23,57,53,53,73,59,95,33,98,48,24,38,91,44,48,77],
        [96,93,87,0,46,93,1,34,85,51,99,87,50,51,87,46,77,63,80,90,7,9,52,29,53,15,70,1,48,49,72,80,92,95,78,22,53,83,40,67,69,63,49,66,57,65,63,61,75,9,56,45,15,10,55,45,86,1,42,63,65,36,32,93,73,32,2,60,74,65,81,54,13,54,50,62,81,65,36,75,18,68,20,60,73,95,79,80,67,8,85,97,33,19,48,65,78,25,2,36],
        [63,17,70,24,33,28,98,71,31,8,76,0,69,14,5,8,66,82,45,75,60,48,93,34,71,83,10,2,54,76,97,3,77,73,79,61,51,93,15,94,36,77,67,61,90,76,21,14,27,42,48,39,92,48,26,2,22,40,17,86,30,84,62,73,99,66,86,84,5,44,62,52,42,57,86,73,52,45,93,48,36,77,81,79,45,69,66,49,90,72,36,80,91,27,72,81,89,7,21,13],
        [17,2,22,91,47,56,93,68,51,16,93,51,16,38,23,86,74,52,91,84,82,71,0,52,44,10,71,56,82,55,16,88,37,86,73,5,65,73,38,47,12,91,41,18,0,42,24,5,90,17,61,98,70,18,24,81,45,7,23,14,12,32,66,59,83,81,82,20,30,4,1,29,21,13,62,20,79,40,51,51,5,22,53,60,44,48,36,26,86,24,0,24,61,21,45,2,29,16,81,36],
        [17,69,25,29,77,10,15,2,99,34,17,0,13,93,48,87,88,24,15,51,7,48,89,32,76,41,12,39,44,64,51,8,40,48,98,42,12,66,89,1,89,76,53,39,36,63,69,79,65,25,87,27,8,29,29,22,1,56,98,73,89,61,6,53,48,90,43,52,56,19,32,44,34,75,37,13,20,38,80,5,51,52,79,19,5,28,46,48,3,8,26,74,96,97,69,86,37,8,43,79],
        [52,2,31,50,7,93,19,24,67,81,85,57,20,19,6,83,75,76,50,1,35,7,19,95,30,48,0,29,29,65,62,51,25,29,92,15,29,51,41,69,78,51,46,64,76,31,3,11,35,59,70,13,47,2,36,89,60,14,31,89,80,41,44,24,62,87,81,35,85,45,66,25,45,89,63,7,63,14,43,31,52,59,1,28,98,37,3,72,83,60,72,19,98,21,73,97,45,98,6,92],
        [8,10,94,10,25,54,26,83,18,51,65,81,33,68,96,88,34,0,38,73,92,18,38,31,85,76,28,49,3,22,76,56,31,45,88,78,87,49,29,18,23,55,79,60,11,61,85,33,12,14,92,44,75,1,68,58,1,79,85,56,47,54,14,24,90,85,73,75,89,28,4,82,56,85,1,14,16,89,89,24,8,51,77,80,64,0,20,46,2,67,74,89,18,62,71,10,21,98,88,13],
        [45,58,1,62,77,22,98,26,4,77,1,47,64,75,54,68,25,44,21,81,23,81,6,92,96,19,9,57,36,49,62,80,10,83,36,31,69,76,44,63,95,86,46,34,94,27,27,23,53,17,66,58,3,61,3,77,60,48,70,55,38,97,38,80,73,90,9,50,12,58,97,66,71,49,16,31,25,47,12,43,51,13,98,17,36,69,72,51,74,68,77,44,86,37,49,17,45,80,89,28],
        [16,47,94,23,64,54,53,57,92,43,85,59,81,88,5,95,83,28,17,10,69,63,7,17,14,55,13,96,20,83,95,71,82,92,75,87,61,30,3,30,62,6,33,73,51,97,27,40,86,38,79,66,4,7,79,62,11,99,56,56,55,84,16,64,52,29,77,97,90,50,91,52,46,67,44,59,88,51,23,15,40,39,69,7,77,54,13,22,88,16,54,83,40,70,55,5,62,17,1,2],
        [45,75,32,97,36,53,15,2,55,54,33,69,88,18,7,28,84,92,24,2,52,86,16,21,16,25,11,79,64,15,8,2,65,77,59,92,10,48,88,8,60,70,15,61,55,71,38,94,49,33,90,54,6,12,71,45,24,64,57,83,72,57,81,56,90,6,48,60,83,20,5,35,19,90,76,35,72,68,2,1,39,26,9,90,22,79,57,96,50,43,70,37,76,75,21,13,71,59,79,1],
        [8,88,72,13,58,83,48,33,44,45,65,44,9,91,31,57,44,94,52,90,23,51,96,6,85,43,13,49,76,69,58,7,73,45,47,17,19,69,47,45,93,15,85,91,57,80,12,5,73,30,88,29,11,66,76,85,20,66,6,44,39,79,61,28,19,42,37,15,81,45,60,57,87,90,42,50,21,98,98,2,49,31,25,73,8,34,84,76,24,83,80,9,87,57,44,45,2,65,71,71],
        [52,85,37,81,9,60,21,6,47,83,95,2,25,6,85,85,62,12,66,6,76,98,73,12,68,71,87,37,12,88,43,29,33,85,92,42,69,72,32,52,37,44,77,66,55,8,77,19,99,45,81,93,63,13,70,48,38,32,80,92,23,60,61,73,13,81,61,47,77,63,74,56,78,76,47,24,31,64,54,17,93,73,27,24,36,1,3,15,8,99,72,41,27,72,96,45,62,83,59,49],
        [23,82,29,27,93,20,80,23,76,16,55,18,72,82,82,15,0,95,43,83,84,15,62,84,79,98,20,6,12,52,62,11,35,41,7,43,34,60,67,27,22,50,53,82,80,62,96,62,35,20,71,18,79,38,26,79,33,44,4,87,24,24,2,44,95,11,43,29,4,88,81,61,26,66,67,58,46,28,65,21,82,8,23,43,81,34,22,98,82,5,44,27,82,33,64,6,25,83,66,25],
        [63,24,31,14,52,85,91,66,56,64,68,20,10,6,32,43,20,53,44,14,6,59,74,75,66,13,79,78,87,46,60,47,75,17,40,34,7,86,17,57,25,81,23,72,56,61,10,89,80,42,82,49,33,79,26,34,10,69,40,42,14,49,44,11,65,95,6,75,19,88,42,69,5,68,67,76,82,63,95,2,23,88,96,28,62,28,96,97,11,20,2,38,65,35,96,78,74,98,33,84],
        [64,34,3,71,49,57,88,72,63,52,65,98,97,57,61,61,29,35,55,90,44,55,21,56,70,47,86,27,56,68,67,23,91,75,66,86,9,10,59,6,51,89,21,73,54,42,75,14,97,28,24,20,50,89,77,43,66,68,80,34,78,68,46,43,52,86,97,68,9,74,41,8,47,7,48,56,96,51,22,0,78,64,23,3,79,3,21,4,71,17,75,34,74,19,1,88,57,73,29,8],
        [12,6,88,87,19,70,82,72,9,97,8,76,83,67,14,73,52,76,46,9,29,26,61,78,23,70,28,64,57,7,41,34,57,78,54,45,38,98,19,30,73,20,68,59,88,33,19,20,92,84,69,28,80,21,10,86,96,83,61,65,89,37,59,94,71,25,12,65,21,29,3,3,27,16,33,35,30,69,35,16,71,88,68,50,41,61,10,40,34,63,68,85,22,20,40,18,11,6,26,86],
        [21,0,19,29,12,23,88,11,82,40,57,80,58,57,26,9,13,33,92,52,84,51,32,79,42,81,12,93,28,42,38,98,1,68,30,86,23,85,9,14,41,50,99,11,34,49,24,84,31,70,15,50,38,11,60,39,71,15,87,69,90,58,0,72,93,89,8,44,55,66,89,24,3,66,64,13,46,19,64,52,56,86,60,34,13,97,26,51,86,53,78,16,35,59,87,94,9,82,21,24],
        [62,12,30,68,70,9,32,85,84,37,20,37,0,70,28,74,24,2,45,20,36,13,18,60,74,49,73,28,59,90,19,13,21,63,11,42,98,57,79,48,20,19,33,22,92,68,60,43,57,60,87,83,82,62,68,44,7,50,28,70,75,54,59,17,24,21,86,80,8,46,8,50,82,5,25,98,22,35,7,30,26,93,35,12,66,11,71,51,15,29,21,64,65,39,35,34,90,60,76,22],
        [55,80,84,17,88,68,36,27,50,68,13,72,86,29,59,48,60,10,98,40,66,44,4,12,12,73,60,62,33,91,10,57,51,40,4,83,64,34,78,72,51,21,62,70,25,82,7,20,16,92,64,24,69,82,81,83,3,53,58,57,86,97,5,85,7,56,68,87,81,71,70,8,62,87,65,51,3,92,16,35,37,44,27,53,55,69,35,53,39,39,96,73,22,87,8,64,88,92,56,17],
        [12,68,71,64,97,82,52,93,35,75,65,74,52,31,51,64,49,8,39,50,94,67,86,65,25,49,69,71,1,71,73,57,54,44,46,15,36,66,70,11,60,77,45,51,44,43,98,92,20,55,72,2,64,90,96,85,15,68,15,56,36,39,68,79,45,12,44,44,63,98,44,29,57,72,52,39,44,1,65,81,45,99,91,61,47,0,14,37,45,63,28,29,25,93,15,41,37,1,7,52],
        [62,87,32,16,5,19,11,67,77,22,56,53,23,20,75,96,37,36,2,8,52,38,10,27,57,5,32,76,90,96,27,87,36,24,65,57,9,77,99,78,57,76,77,2,26,34,3,19,71,39,6,27,11,26,45,90,69,32,94,79,64,57,21,64,91,53,27,64,91,59,91,78,31,9,75,60,25,90,75,59,77,1,81,57,97,96,25,48,41,74,15,11,79,15,84,41,5,90,78,19],
        [56,50,44,16,60,78,59,21,69,38,4,14,96,39,75,37,56,67,21,32,86,25,44,50,99,63,1,54,71,68,60,25,28,22,85,35,80,83,90,36,96,26,29,14,24,86,61,75,92,42,40,75,64,37,43,87,35,68,23,82,23,69,44,66,48,30,34,51,28,25,66,90,66,13,39,97,49,81,87,37,79,94,71,34,53,78,52,25,60,78,21,16,11,96,84,35,93,66,4,6],
        [53,85,51,70,58,20,88,8,63,7,80,79,42,62,66,75,38,67,71,53,99,29,95,22,66,40,7,97,73,99,88,92,57,90,47,41,43,9,38,21,19,20,6,65,54,62,68,41,87,42,35,5,29,15,79,79,88,34,0,66,16,11,23,35,46,83,29,10,10,78,88,77,77,79,85,16,66,56,69,21,45,45,99,41,96,78,6,26,7,95,23,32,74,75,58,33,56,50,26,92],
        [19,49,18,24,72,36,21,44,29,64,5,82,73,52,40,80,73,31,44,61,51,18,37,59,37,44,4,60,44,10,15,97,25,56,88,40,83,69,55,78,84,19,46,94,73,19,65,74,21,98,48,87,30,54,87,97,40,43,63,10,1,67,53,68,53,93,13,25,3,74,52,44,15,64,67,83,45,1,3,1,58,30,97,36,5,76,21,8,54,40,25,64,13,55,84,23,75,4,12,34],
        [0,44,89,2,73,47,54,4,76,98,8,74,85,54,68,71,93,21,69,2,44,26,73,96,26,43,97,88,80,55,11,53,83,43,35,15,67,95,69,94,60,65,76,16,12,7,75,3,89,47,73,51,56,18,24,18,92,4,94,65,49,12,72,97,47,98,18,18,13,93,39,44,28,33,32,89,31,12,71,88,12,60,88,58,52,19,86,95,57,54,39,86,54,27,32,29,4,91,67,65],
        [91,14,85,3,95,70,84,24,82,25,19,47,44,31,76,2,11,65,67,47,65,28,83,11,88,51,99,94,8,14,17,19,50,12,68,74,51,89,45,77,25,98,53,65,95,18,79,58,92,50,95,29,19,61,17,52,9,45,27,61,95,61,94,94,68,24,12,38,42,20,92,21,23,74,70,55,75,3,99,29,19,94,57,65,89,10,66,29,87,54,49,66,32,69,67,24,9,48,30,67],
        [71,76,62,24,75,91,67,7,21,63,87,75,95,63,57,64,67,35,49,90,53,18,64,13,18,23,68,79,72,4,50,60,82,43,5,87,66,46,9,66,63,69,12,31,32,47,98,77,65,67,46,95,82,89,35,62,75,90,32,59,85,95,3,39,59,81,30,97,3,35,82,57,76,65,82,84,66,52,39,66,21,92,93,64,10,11,12,32,52,8,85,84,97,81,1,6,16,27,89,91],
        [5,11,90,66,77,89,37,74,27,97,59,71,15,16,75,30,28,29,36,70,45,93,15,10,65,25,39,58,38,46,64,28,73,39,83,58,17,75,37,86,52,95,5,2,84,2,35,90,25,28,78,99,21,7,36,19,1,47,32,92,21,72,45,7,34,21,59,75,6,48,47,41,41,30,34,18,94,62,97,70,19,66,57,51,46,82,42,50,90,44,87,22,98,39,52,79,45,21,6,90],
        [51,93,21,49,24,68,45,52,48,15,52,57,22,15,92,63,81,53,28,94,48,87,68,79,56,17,75,24,83,79,30,92,94,65,91,37,12,46,6,25,25,42,62,25,19,37,6,10,99,71,79,36,82,28,52,19,41,54,65,64,36,86,41,11,51,20,83,19,28,36,49,31,15,14,11,94,3,76,6,52,22,93,79,92,5,33,33,49,88,39,45,4,27,11,10,47,57,47,59,98],
        [52,16,75,47,58,54,57,40,98,34,80,13,53,1,56,48,45,22,25,84,18,84,29,4,21,80,34,59,99,69,33,51,18,96,46,18,27,41,57,85,58,98,63,46,34,10,23,38,29,13,81,14,94,31,94,50,85,79,35,8,89,38,87,39,60,62,10,71,19,35,71,55,42,75,61,71,91,22,55,91,69,25,68,51,87,94,39,69,6,78,79,7,84,68,53,30,26,45,48,38],
        [81,80,7,20,21,44,82,9,73,63,29,62,96,79,9,61,38,61,47,54,40,55,71,7,42,6,6,83,78,11,93,64,98,66,50,34,75,10,24,90,89,2,42,51,69,35,75,37,22,50,24,64,84,31,72,56,95,3,28,37,35,40,70,79,47,26,83,52,15,83,26,88,46,84,16,44,83,29,41,38,36,8,89,67,83,12,41,58,34,67,15,81,3,40,53,96,35,23,81,74],
        [71,84,58,37,9,48,24,65,2,89,90,13,81,23,47,58,75,51,79,30,70,12,98,31,93,42,98,97,59,69,40,32,22,98,4,53,4,46,6,37,37,98,5,22,39,53,37,45,48,86,21,72,26,14,70,11,47,13,64,74,14,59,47,26,6,2,21,18,32,93,98,36,68,71,75,75,8,67,30,85,53,41,96,18,8,71,43,4,7,75,54,75,80,79,55,36,27,71,53,64],
        [40,59,97,72,9,65,90,75,47,51,79,21,78,16,64,53,71,48,12,42,5,62,0,55,62,10,82,86,31,95,81,56,30,59,93,68,75,76,72,33,61,70,97,26,3,1,83,50,28,65,27,77,51,2,50,95,85,51,70,74,84,13,13,15,92,31,76,29,81,17,29,97,56,67,48,64,57,93,67,94,71,35,76,69,98,90,45,53,64,73,33,15,20,66,29,88,74,71,18,48],
        [54,93,83,77,80,35,74,49,80,39,79,7,19,0,18,66,69,29,38,71,84,83,80,36,49,96,61,30,66,47,8,16,33,6,73,26,3,87,25,95,69,9,51,33,88,89,49,88,78,2,65,21,1,37,56,2,56,81,64,71,21,36,45,62,73,59,73,79,45,35,41,1,83,67,92,47,37,59,49,82,76,25,80,3,1,3,33,5,4,59,62,94,69,88,72,46,5,88,9,19],
        [80,82,60,12,58,57,13,75,86,42,0,21,48,75,99,46,53,93,94,71,34,88,87,35,49,88,66,16,46,38,13,37,34,41,23,39,1,54,73,17,84,18,18,30,53,29,28,12,89,38,18,94,93,18,55,66,97,4,78,37,45,22,61,1,65,90,41,49,44,66,52,35,97,62,10,21,41,29,45,37,98,61,58,8,71,63,22,84,42,88,69,92,23,53,97,95,95,42,20,92],
        [4,36,52,84,91,10,39,35,69,74,91,75,77,25,47,14,71,87,35,68,45,27,56,93,95,7,66,35,48,1,51,95,64,56,18,36,33,6,13,81,93,30,80,57,28,62,57,7,72,29,58,53,55,40,60,4,91,30,97,8,33,6,4,69,29,97,21,45,34,51,66,90,31,9,28,36,68,13,12,9,57,67,81,37,92,15,60,98,6,9,3,47,78,80,30,60,61,42,44,39],
        [21,14,17,92,76,7,94,33,54,97,83,3,33,52,6,61,10,34,61,30,64,92,41,41,8,90,75,58,31,19,22,92,82,55,80,19,83,36,13,1,86,77,41,13,7,21,25,46,94,98,52,45,43,18,41,81,55,10,11,74,97,38,19,89,17,64,31,52,17,78,84,38,97,8,46,99,34,29,18,8,47,10,49,63,86,89,70,70,98,41,34,36,9,7,62,92,34,4,95,8],
        [90,30,45,10,91,66,98,78,96,61,62,1,82,77,89,46,86,91,76,80,57,76,83,44,63,28,61,72,14,12,47,86,67,97,14,83,19,14,72,57,12,7,76,51,40,90,81,72,55,0,52,2,43,45,86,5,61,15,24,82,44,84,47,18,28,84,24,29,47,79,50,66,98,31,37,76,2,76,49,28,69,85,51,22,92,11,35,27,89,57,20,85,79,8,10,77,10,96,40,4],
        [50,87,72,76,29,77,15,32,2,92,62,98,10,25,94,1,55,44,91,84,74,45,8,13,58,73,27,28,71,37,34,31,89,22,45,29,94,92,12,82,39,62,27,14,18,96,23,29,83,87,22,30,20,56,41,30,43,63,82,43,95,81,84,41,2,70,79,10,44,90,72,89,78,54,67,63,12,74,62,23,84,3,2,47,57,27,80,17,71,26,75,20,86,32,46,17,21,57,30,84],
        [74,11,53,42,95,62,70,26,13,82,80,75,22,32,51,83,74,51,34,63,9,86,10,93,13,23,73,32,67,81,58,83,53,71,73,38,83,54,2,63,97,3,84,69,41,86,4,65,83,59,89,9,82,16,85,35,27,24,62,40,97,11,22,3,90,45,87,15,50,21,25,77,38,49,22,23,9,94,45,15,43,35,29,9,26,84,18,72,2,58,75,57,49,38,79,13,85,19,2,3],
        [17,49,51,0,58,34,1,16,88,54,41,32,73,28,26,43,96,28,68,68,95,96,72,95,23,64,69,65,48,22,19,10,4,73,24,72,32,76,20,36,18,97,98,8,6,26,28,72,87,78,14,57,42,63,65,74,85,81,90,84,20,4,9,58,4,51,51,92,57,46,43,21,60,59,63,22,26,3,58,75,20,5,54,21,31,97,64,8,2,60,27,93,55,67,47,16,22,20,9,8],
        [86,6,53,60,58,70,18,68,59,22,58,3,79,40,59,14,35,28,68,22,79,19,72,22,74,97,10,75,94,59,19,2,7,47,90,32,69,45,12,52,40,55,7,4,32,21,60,68,85,43,57,63,64,81,91,28,78,12,79,78,12,14,85,65,1,75,6,63,30,64,49,50,15,45,13,55,57,20,27,73,84,54,66,10,56,58,2,9,2,46,11,9,96,76,23,8,9,64,2,47],
        [72,10,13,6,20,94,12,85,34,58,43,80,41,21,16,60,63,5,43,26,81,38,62,86,32,2,10,71,53,4,13,52,10,22,68,88,65,17,92,71,48,8,74,66,75,43,46,33,33,49,2,33,33,39,54,89,4,4,59,64,29,89,83,73,55,68,52,23,83,43,16,69,30,2,79,65,87,47,57,56,51,18,96,40,87,74,86,84,70,21,16,76,89,48,70,82,47,48,19,18],
        [62,71,49,5,28,59,81,0,53,90,35,84,18,40,3,10,83,3,6,52,38,48,49,1,87,13,78,38,62,79,38,28,45,58,96,69,25,93,57,60,49,26,99,21,32,19,15,80,98,41,69,89,41,85,57,11,8,54,57,62,85,15,21,8,40,51,16,40,25,19,14,66,82,76,91,10,4,89,44,17,44,22,82,61,39,75,98,39,56,95,45,66,91,60,36,76,60,6,5,45],
        [50,42,82,94,85,62,50,10,37,8,48,11,65,90,77,92,14,53,56,35,70,41,60,21,46,90,6,76,34,69,64,56,77,52,22,32,6,23,7,54,1,66,17,71,28,10,34,41,33,66,32,6,56,11,85,27,2,26,92,94,89,46,77,48,88,21,1,13,51,58,62,20,69,38,97,25,4,19,80,96,19,91,2,57,82,27,81,82,74,63,15,61,69,51,29,25,31,29,76,37],
        [61,88,43,8,34,39,27,64,90,38,80,34,7,26,63,23,21,88,90,0,36,14,86,63,31,80,4,79,27,79,98,16,32,72,68,17,65,21,24,50,7,24,38,59,29,79,45,52,32,20,75,28,86,65,84,20,45,79,0,65,44,72,98,89,53,64,76,8,94,33,27,9,19,0,70,48,68,7,50,36,92,42,45,47,26,85,18,19,93,19,46,3,21,29,78,0,90,44,48,5],
        [57,19,71,82,19,98,15,20,42,98,35,68,10,88,4,77,46,62,13,94,56,48,90,41,1,64,4,4,2,27,45,6,78,27,26,79,74,75,5,3,94,12,57,60,62,14,80,73,75,77,66,66,61,11,46,69,0,79,10,32,2,16,17,87,71,96,75,58,30,74,22,14,44,45,40,50,2,23,9,58,18,94,5,51,59,56,57,40,30,46,91,77,11,76,74,1,47,45,9,60],
        [27,97,2,32,50,57,48,15,95,74,65,11,66,41,72,82,13,63,46,81,30,32,19,57,21,3,86,84,97,44,26,23,63,14,23,62,76,47,36,58,66,62,12,91,10,69,48,79,54,40,61,31,4,73,41,8,7,97,2,61,89,93,21,16,74,42,76,53,91,16,76,21,74,65,53,8,98,86,71,19,75,16,22,98,98,22,48,84,34,68,66,20,45,62,71,89,55,20,0,91],
        [66,36,85,45,38,58,6,59,20,77,15,93,70,25,10,28,88,84,71,55,76,58,77,78,3,10,54,36,74,26,50,4,88,75,7,95,37,37,47,11,95,51,23,12,49,67,70,13,40,93,97,48,29,3,70,70,54,89,15,24,79,84,88,82,89,83,77,25,36,93,78,82,9,91,94,81,40,22,65,21,90,67,88,50,48,6,88,13,91,55,92,74,69,5,52,41,27,87,41,34],
        [8,46,44,42,6,7,96,49,95,10,90,11,86,32,74,60,74,2,88,93,85,91,88,80,16,25,67,0,18,91,76,91,68,48,83,28,89,12,52,51,66,30,18,0,84,72,48,93,2,13,67,26,4,98,71,71,97,47,19,52,31,82,96,35,0,98,99,16,59,81,15,29,68,53,63,62,7,56,49,76,78,44,24,56,69,1,73,94,98,77,21,23,93,61,65,80,27,34,64,25],
        [3,13,21,9,21,5,5,58,9,73,80,56,58,27,48,71,32,17,92,42,2,54,96,95,72,85,33,83,19,48,66,17,31,51,65,43,69,46,11,33,61,99,66,24,85,21,53,29,15,30,40,47,53,6,9,25,68,63,4,81,67,6,95,92,66,50,22,94,39,72,79,91,54,43,46,70,10,95,85,17,12,78,97,66,84,62,68,10,98,95,68,77,61,14,31,90,12,63,21,54],
        [10,37,47,13,9,47,31,45,11,19,42,11,5,93,6,48,92,96,11,19,33,22,83,15,66,31,44,49,2,67,31,26,18,47,79,84,41,37,84,68,2,33,32,7,50,35,52,84,91,86,29,64,19,63,38,47,43,59,86,55,57,42,52,47,39,18,47,89,43,71,2,82,23,10,12,48,67,62,7,34,75,30,52,10,6,79,8,37,78,93,85,99,97,29,49,83,14,94,24,46],
        [32,35,76,27,96,74,30,94,2,23,11,9,26,93,87,23,69,57,81,7,63,21,7,21,77,54,88,54,45,95,36,43,12,73,89,84,37,7,47,38,27,35,32,43,32,91,53,64,21,51,51,84,15,93,28,1,76,30,36,6,39,91,77,95,34,30,18,62,91,46,34,61,24,50,7,84,11,4,95,5,94,29,83,33,3,30,28,42,96,42,13,21,2,46,33,37,77,76,3,96],
        [44,64,8,54,27,83,86,22,39,11,82,3,34,62,85,3,82,69,96,18,70,15,46,89,77,47,16,69,70,92,5,6,79,75,33,64,24,60,28,85,8,29,36,9,84,43,43,59,34,3,62,20,27,19,42,11,80,46,12,52,67,46,40,50,43,85,17,63,23,78,29,40,23,35,92,3,77,78,5,68,11,73,27,40,96,79,93,56,14,75,60,86,95,89,22,13,83,56,26,45],
        [61,17,93,22,71,15,47,11,13,62,28,69,15,14,55,54,10,91,55,55,28,33,57,27,65,91,84,59,79,32,68,42,88,99,96,9,70,18,73,25,49,18,89,35,10,39,59,36,2,5,32,92,16,24,13,2,4,46,36,87,28,7,9,20,8,94,24,29,37,52,4,51,83,88,95,81,14,30,44,61,89,67,32,98,90,95,56,36,22,46,29,12,60,79,33,56,74,37,36,62],
        [65,18,30,52,9,32,30,65,65,38,23,86,55,93,51,98,2,57,81,19,91,23,3,7,20,46,50,90,28,61,76,62,84,41,25,81,83,54,83,80,58,97,45,69,30,70,92,68,63,73,54,92,63,16,14,52,47,88,1,97,13,17,8,21,49,37,71,15,45,15,88,92,9,8,23,43,82,95,78,75,21,40,44,30,24,9,81,23,45,53,5,14,96,17,84,13,54,42,53,74],
        [81,40,6,74,27,57,15,24,43,97,20,90,66,14,58,70,26,58,88,76,83,86,28,75,40,26,69,28,40,37,73,7,29,26,59,86,11,90,46,29,40,64,9,36,72,67,81,78,10,52,28,15,99,52,77,40,49,69,59,45,41,63,88,22,18,54,20,69,96,37,63,57,34,81,47,69,29,80,27,51,2,15,91,51,41,86,49,60,23,49,40,56,59,34,24,13,36,30,72,37],
        [83,54,91,60,38,80,86,92,72,92,39,66,73,67,61,84,4,40,18,83,72,6,8,56,63,68,14,61,45,24,69,26,74,44,82,4,39,67,79,73,95,32,97,87,69,17,55,77,42,76,92,45,82,61,99,42,8,89,58,20,92,90,91,79,96,64,59,60,88,3,68,10,93,26,55,89,57,2,46,27,68,37,31,40,38,72,81,22,42,44,12,5,27,26,13,62,27,42,90,62],
        [34,54,41,69,19,55,5,97,28,30,29,53,46,43,83,2,97,73,90,2,51,14,81,79,71,89,74,0,29,23,48,54,82,65,40,64,26,0,64,8,20,31,75,74,6,98,1,61,52,19,89,56,78,86,61,87,16,78,59,50,83,42,58,51,24,54,85,46,38,66,69,74,90,69,40,2,38,83,90,63,29,64,79,54,84,25,14,75,35,25,48,7,4,88,8,68,20,44,41,60]
    ])
    (-1.3232082006328512e225)

main :: IO Counts
main = runTestTT $ TestList [test1, test2, test3, test4]
