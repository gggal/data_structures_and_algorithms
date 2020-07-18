data LinkedList a = Empty | Node a (LinkedList a) deriving (Eq, Show)

new = Empty

addElement :: LinkedList a -> a -> LinkedList a
addElement Empty newElement = (Node newElement Empty)
addElement linkedList newElement = (Node newElement linkedList)

containsElement :: (Eq a) => LinkedList a -> a -> Bool
containsElement Empty element = False
containsElement (Node topEl rest) element = (topEl == element) || (containsElement rest element)

getNthElement :: LinkedList a -> Int -> a
getNthElement (Empty) _ = error "no such element"
getNthElement (Node topEl _) 0 = topEl
getNthElement (Node _ rest) idx = ( getNthElement rest (idx - 1))

removeNthElement :: LinkedList a -> Int -> LinkedList a
removeNthElement Empty idx = Empty
removeNthElement (Node topEl (Node _  rest)) 1 = (Node topEl rest)
removeNthElement (Node topEl rest) 0 = rest
removeNthElement (Node topEl rest) idx = (Node topEl (removeNthElement rest (idx - 1)))

removeElement :: (Eq a) => LinkedList a -> a -> LinkedList a
removeElement Empty el = Empty
removeElement (Node topEl rest) el | (el == topEl) = rest
removeElement (Node topEl rest) el = (Node topEl (removeElement rest el))

length :: LinkedList  a -> Int
length linkedList = (lengthTailRec linkedList 0) 

lengthTailRec :: LinkedList a -> Int -> Int
lengthTailRec Empty accLength = accLength
lengthTailRec (Node _ rest) accLength = (lengthTailRec rest accLength + 1)