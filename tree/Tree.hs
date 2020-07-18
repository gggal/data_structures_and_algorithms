data Tree a = Empty | Node (Tree a) a (Tree a) deriving (Eq, Show)

new = Empty

single :: a -> Tree a
single el = (Node Empty el Empty)

addElement :: (Ord a) => Tree a -> a -> Tree a
addElement Empty el = single el
addElement (Node left el right) toAdd 
                                | el == toAdd = (Node left el right)
                                | toAdd < el = (Node (addElement left toAdd) el right)
                                | toAdd > el = (Node left el (addElement right toAdd))

containsElement :: (Ord a) => Tree a -> a -> Bool
containsElement Empty _ = False
containsElement (Node left el right) toCheck 
                                        | toCheck == el = True
                                        | otherwise = (containsElement left toCheck) && (containsElement right toCheck)

deleteElement :: (Ord a) => Tree a -> a -> Tree a
deleteElement Empty _ = Empty
deleteElement (Node left el right) toDel
                                        | toDel == el && left == Empty = right
                                        | toDel == el = (replaceRoot (Node left el right))
                                        | toDel < el = (Node (replaceRoot left) el right)
                                        | toDel > el = (Node left el (replaceRoot right))

replaceRoot :: (Ord a) => Tree a -> Tree a
replaceRoot Empty = Empty
replaceRoot (Node Empty el Empty) = Empty
replaceRoot (Node left el Empty) = left
replaceRoot (Node left el right) = (Node left (minEl right) (removeMinEl right))

minEl :: (Ord a) => Tree a -> a
minEl Empty = error "unreachable"
minEl (Node Empty el right) = el
minEl (Node left el right) = (minEl left)

removeMinEl :: (Ord a) => Tree a -> Tree a
removeMinEl Empty = Empty
removeMinEl (Node Empty el right) = right
removeMinEl (Node left el right) = (removeMinEl left)