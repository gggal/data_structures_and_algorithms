newStack = []

push :: [a] -> a -> [a]
push stack el = stack ++ [el]

pop :: [a] -> [a]
pop [] = error "empty stack"
pop stack = (init stack)

peekStack :: [a] -> a
peekStack stack = last stack

sizeStack :: [a] -> Int
sizeStack stack = length stack

-- queue --

newQueue = []

enqueue :: [a] -> a -> [a]
enqueue queue el = queue ++ [el]

dequeue :: [a] -> [a]
dequeue [] = error "empty queue"
dequeue queue = (tail queue)

peekQueue :: [a] -> a
peekQueue [] = error "empty queue"
peekQueue queue = head queue

sizeQueue :: [a] -> Int
sizeQueue queue = length queue

-- linked cyclic queue

-- data Node a = EmptyNode | NonEmptyNode a (Node a) (Node a) deriving (Eq, Show)

-- newCyclicQueue = (,)




