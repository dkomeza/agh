from zadtesty import runtests
from queue import PriorityQueue

def dijkstra(G, s):
  d = [[float("inf")] * 17 for _ in range(len(G))]
  pq = PriorityQueue()
  
  d[s][0] = 0
  pq.put((0, s, 0))
  
  while not pq.empty():
    dv, v, fatique = pq.get()
    if d[v][fatique] < dv:
      continue
    
    for u, w in G[v]:
      f = fatique + w
      cost = w
      if f > 16:
        f = w
        cost += 8
      
      if dv + cost < d[u][f]:
        d[u][f] = dv + cost
        pq.put((d[u][f], u, f))

  return d
  

def goodknight( G, s, t ):
  n = len(G)
  adj = [[] for _ in range(n)]
  
  for i, row in enumerate(G):
    for v, w in enumerate(row):
      if i != v and w != -1:
        adj[i].append((v, w))
  
  d = dijkstra(adj, s)
  return min(d[t])

# zmien all_tests na True zeby uruchomic wszystkie testy
runtests( goodknight, all_tests = True )
