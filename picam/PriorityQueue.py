class PriorityQueue:
    def __init__(self):
        self._heap = []
    
    def push(self,data):
        self._heap.append(data)

        now = len(self._heap) -1

        while(now > 0):
            nxt = (now - 1) // 2
            if(self._heap[now].CompareTo(self._heap[nxt]) < 0):
                break
            self._heap[now] , self._heap[nxt] = self._heap[nxt] , self._heap[now]
            now = nxt

    def pop(self):
        ret = self._heap[0]
        
        lastIndex = len(self._heap) -1

        self._heap[0] = self._heap[lastIndex]
        del self._heap[lastIndex]
        lastIndex -= 1

        now = 0
        while(True):
            left = 2 * now + 1
            right = 2 * left + 2
            nxt = now
            
            if(left <= lastIndex and self._heap[nxt].CompareTo(self._heap[left]) < 0):
                nxt = left

            if(right <= lastIndex and self._heap[nxt].CompareTo(self._heap[right]) < 0):
                nxt = right

            if(nxt == now):
                break

            self._heap[now] , self._heap[nxt] = self._heap[nxt] , self._heap[now]
            now = nxt

        return ret

    def Count(self):
        return len(self._heap)

class PQNode:
    def __init__(self,f,g=0,y=0,x=0):
        self.F = f
        self.G = g
        self.Y = y
        self.X = x

    def CompareTo(self,other):
        if(other.F == self.F):
            return 0
        
        return 1 if(self.F < other.F) else -1


# pq = PriorityQueue()

# pq.push(PQNode(5))
# pq.push(PQNode(13))
# pq.push(PQNode(3))
# pq.push(PQNode(19))
# pq.push(PQNode(35))
# pq.push(PQNode(15))
# pq.push(PQNode(1))


# print(pq.pop().F)
# print(pq.pop().F)
# print(pq.pop().F)
# print(pq.pop().F)
# print(pq.pop().F)
