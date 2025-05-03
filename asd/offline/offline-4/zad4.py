from zad4testy import runtests

# min heap
def heapify(S: list, x: int,n: int):
    childpos = 2 * x + 1
    
    while childpos < n:
        right = childpos + 1
        
        if right < n and S[right] < S[childpos]:
            childpos = right
            
        if S[childpos] < S[x]:
            S[x], S[childpos] = S[childpos], S[x]
            x = childpos
            childpos = 2 * x + 1
        else:
            break

def heappop(S: list):
    last = S.pop()
    if S:
        first = S[0]
        S[0] = last
        last = first
        heapify(S, 0, len(S))
    return last

def heappush(S: list, v):
    S.append(v)
    
    s, e = 0, len(S) - 1
    new = S[e]
    
    while s < e:
        p = (e - 1) >> 1
        parent = S[p]
        
        if new < parent:
            S[e] = parent
            e = p
        else:
            break
    S[e] = new
    

def dijkstra(G, s):
    distances = [float('inf')] * len(G)
    distances[s] = 0
    visited = [False] * len(G)

    for _ in range(len(G)):
        min_distance = float('inf')
        u = None
        for i in range(len(G)):
            if not visited[i] and distances[i] < min_distance:
                min_distance = distances[i]
                u = i

        if u is None:
            break

        visited[u] = True

        for v, w in G[u]:
            if not visited[v]:
                alt = distances[u] + w
                if alt < distances[v]:
                    distances[v] = alt
    return distances

def optimized_dijkstra(G, s):
    from queue import PriorityQueue

    dist = [float("inf")] * len(G)
    dist[s] = 0
    
    pq = PriorityQueue()
    pq.put((0,s))


    while not pq.empty():
        d, u = pq.get()

        if d > dist[u]:
            continue
        
        for v, weight in G[u]:
            if dist[u] + weight < dist[v]:
                dist[v] = dist[u] + weight
                pq.put((dist[v], v))
    return dist

def spacetravel(n, E, S, a, b):
    num_nodes = n + 1
    singularity = n  # Index for the singularity hub node
    adj = [[] for _ in range(num_nodes)]

    # Add edges for direct flights from the list E
    for u, v, t in E:
        adj[u].append((v, t))
        adj[v].append((u, t))

    for planet in S:
        # Add bidirectional zero-weight edges between the planet and the hub
        adj[planet].append((singularity, 0))
        adj[singularity].append((planet, 0))

    dist = optimized_dijkstra(adj, a)

    return None if dist[b] == float("inf") else dist[b]

# zmien all_tests na True zeby uruchomic wszystkie testy
runtests( spacetravel, all_tests = True )
