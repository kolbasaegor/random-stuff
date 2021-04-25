module LolIntegral where

exampleFunction n = sqrt $ n^2 - 1

integration :: (Double -> Double) -> Double -> Double -> Double

integration f a b = area where
	n :: Int
	n = 5000

	h :: Double
	h = (b - a) / 5000

	x :: [Double]
	x = [a + h * (fromIntegral i) | i <- [0 .. n-1]]
	
	area = h * ( (f (x!!0) + f (x!!(n-1)))/2 + sumOfValues (1) (n) (f))

	sumOfValues :: Int -> Int -> (Double -> Double) -> Double
	sumOfValues from to function = helper 0 from to function

	helper :: Double -> Int -> Int -> (Double -> Double) -> Double
	helper acc from to function | from == to = acc
				    | otherwise  = helper (acc + function (x!!from)) (from+1) (to) (function)
