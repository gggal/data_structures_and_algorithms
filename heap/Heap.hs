data Tree a = Empty | Node (Tree a) a (Tree a) deriving (Eq, Show)

new = Empty

push :: (Ord a) => Tree a -> a -> Tree a
push Empty newEl = (Node Empty newEl Empty)
push node newEl = (siftUp (addLeaf node newEl pathToEl) pathToEl) where pathToEl = (path (size node))

pop :: (Ord a) => Tree a -> Tree a
pop Empty = Empty
pop (Node Empty el Empty) = Empty
pop node = (siftDown (moveLastToTop node))

top :: (Ord a) => Tree a -> a
top Empty = error "empty heap"
top (Node _ el _) = el

leftSub :: (Ord a) => Tree a -> Tree a
leftSub Empty = error "empty heap"
leftSub (Node left _ _) = left

rightSub :: (Ord a) => Tree a -> Tree a
rightSub Empty = error "empty heap"
rightSub (Node _ _ right) = right

moveLastToTop :: (Ord a) => Tree a -> Tree a
moveLastToTop Empty = Empty
moveLastToTop node = (Node left last right) where last = (getEl node (path ((size node) - 1)))
                                                  (Node left _ right) = (deleteEl node (path ((size node) - 1)))

getEl :: (Ord a) => Tree a -> [Bool] -> a
getEl Empty _ = error "empty tree"
getEl (Node _ el _) [] = el
getEl (Node left _ _) (True : tail) = (getEl left tail)
getEl (Node _ _ right) (False : tail) = (getEl right tail)

deleteEl :: (Ord a) => Tree a -> [Bool] -> Tree a
deleteEl Empty _ = Empty
deleteEl tree [] = Empty
deleteEl (Node left el right) (True : tail) = (Node (deleteEl left tail) el right)
deleteEl (Node left el right) (False : tail) = (Node left el (deleteEl right tail))


addLeaf :: (Ord a) => Tree a -> a -> [Bool] -> Tree a
addLeaf Empty leaf _ = (Node Empty leaf Empty)
addLeaf node leaf [] = error "path points to non-empty element"
addLeaf (Node left el Empty) newLeaf [False] = (Node left el (Node Empty newLeaf Empty))
addLeaf (Node Empty el right) newLeaf [True] = (Node (Node Empty newLeaf Empty) el right)
addLeaf (Node left el right) leaf (False : tail) = (Node left el (addLeaf right leaf tail))
addLeaf (Node left el right) leaf (True : tail) = (Node (addLeaf left leaf tail) el right)

siftUp :: (Ord a) => Tree a -> [Bool] -> Tree a
siftUp Empty _ = Empty
siftUp (Node Empty leaf Empty) _ = (Node Empty leaf Empty)
siftUp tree [] = tree
siftUp (Node left el right) (False : tail) = (Node left (min el sEl) (Node sLeft (max el sEl) sRight)) where (Node sLeft sEl sRight) = (siftUp right tail)
siftUp (Node left el right) (True : tail) = (Node (Node sLeft (max el sEl) sRight) (min el sEl) right) where (Node sLeft sEl sRight) = (siftUp left tail)

siftDown :: (Ord a) => Tree a -> Tree a
siftDown Empty = Empty
siftDown (Node Empty el Empty) = (Node Empty el Empty)
siftDown (Node left el right) 
                | right /= Empty && el > (top right) = (Node left (top right) (siftDown (Node (leftSub right) el (rightSub right))))
                | left /= Empty && el > (top left) = (Node (siftDown (Node (leftSub left) el (rightSub left))) (top left) right)
                | otherwise = (Node left el right)
                                

size :: (Ord a) => Tree a -> Int
size Empty = 0
size (Node Empty _ right) = 1 + (size right)
size (Node left _ Empty) = (size left) + 1
size (Node left _ right) = (size left) + 1 + (size right)

-- generates a list representing the directions from a leaf to the root
-- True for left, False for right, e.g. 10 - [False, True, True]
path :: Int -> [Bool]
path 0 = []
path 1 = [True]
path 2 = [False]
path n = (path (parent n)) ++ [n `mod` ((parent n) + 1) == 0]

parent :: Int -> Int
parent 0 = -1
parent n = (n - 1) `div` 2