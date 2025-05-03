from kol2testy import runtests

def warrior(edges, n, s, t):
    pass

G = [ (1,5,10), (4,6,12), (3,2,8),
(2,4,4) , (2,0,10), (1,4,5),
(1,0,6) , (5,6,8) , (6,3,9)]
s = 0
t = 6

# warrior(G,s,t)

# zmien all_tests na True zeby uruchomic wszystkie testy
runtests( warrior, all_tests = True )
