from enum import Enum
from PriorityQueue import PriorityQueue, PQNode
import sys

TileType = { "Empty" : 0 , "Wall" : 1}
dir = {"Up": 0, "Left" : 1, "Down" : 2, "Right" : 3}

class Pos:
    def __init__(self, y, x):
        self.Y = y
        self.X = x

class Board:
    def __init__(self, tile, dest, pos):
        self.tile = tile
        self.DestY = dest[0]
        self.DestX = dest[1]
        self.PosY = pos[0]
        self.PosX = pos[1]
        self.points = []


    def A_Star(self):
        deltaY = [-1,0,1,0]
        deltaX = [0,-1,0,1]
        cost = [0,0,0,0]

        parent = [[Pos(-1,-1) for x in range(len(self.tile[0]))] for y in range(len(self.tile))]

        closed = [[False for x in range(len(self.tile[0]))] for y in range(len(self.tile))] 
        open = [[sys.maxsize for x in range(len(self.tile[0]))] for y in range(len(self.tile))]
        
        pq = PriorityQueue()

        open[self.PosY][self.PosX] = 0 + abs(self.DestY - self.PosY) + abs(self.DestX - self.PosX)
        pq.push(PQNode( abs(self.DestY - self.PosY) + abs(self.DestX - self.PosX), \
                        0, \
                        self.PosY, \
                        self.PosX))
        parent[self.PosY][self.PosX] = Pos(self.PosY, self.PosX)

        while(pq.Count() > 0):
            node = pq.pop()

            if(closed[node.Y][node.X]):
                continue
            
            closed[node.Y][node.X] = True

            if(node.Y == self.DestY and node.X == self.DestX):
                break
            
            for i in range(len(deltaY)):
                nextY = node.Y + deltaY[i]
                nextX = node.X + deltaX[i]

                if(nextX < 0 or nextX >= len(self.tile[0]) or nextY < 0 or nextY >=len(self.tile) ):
                    continue
                if(self.tile[nextY][nextX] == TileType["Wall"]):
                    continue
                if(closed[nextY][nextX]):
                    continue

                
                g = node.G + cost[i]
                h = abs(self.DestY - nextY) + abs(self.DestX - nextX)

                if(open[nextY][nextX] < g + h):
                    continue
                
                open[nextY][nextX] = g + h
                pq.push(PQNode(g + h, g, nextY, nextX))
                parent[nextY][nextX] = Pos(node.Y, node.X)

        
        y = self.DestY
        x = self.DestX

        while(parent[y][x].Y != y or parent[y][x].X != x):
            self.points.append(Pos(y,x))
            pos = parent[y][x]
            y = pos.Y
            x = pos.X
        
        self.points.append(Pos(y,x))

        return self.points
            
            


def navigator(arrow, strt, dst):
    tile = [[0,0,1,0,0],[0,0,0,0,0],[1,0,1,0,0]]
    map = Board(tile, strt, dst) # Board(tile, (2, 3), (0,1))
    a_Star_path = map.A_Star()

    ret = []
    for pos in a_Star_path:
        ret.append( [pos.Y, pos.X])

    return ret



    

