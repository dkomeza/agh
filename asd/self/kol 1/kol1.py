from kol1testy import runtests

def maxrank(T):
  mapped_indexes = [[n, 0] for n in T]
  
  res = 0
  
  def merge(A, l, m, r):
    nonlocal res
    
    start = l
    L = A[l:m+1]
    R = A[m+1:r+1]
    
    pl, pr, nl, nr = 0, 0, len(L), len(R)
    
    while pl < nl and pr < nr:
        if R[pr] > L[pl]:
            A[l] = L[pl]
            pl += 1
        else:
            rank = l - start - pr
            cpl = pl - 1
            while (L[cpl][0] == R[pr][0]):
              rank -= 1
              cpl -= 1
            
            R[pr][1] += rank
            
            if R[pr][1] > res: 
              res = R[pr][1]
            A[l] = R[pr]
            pr += 1
        l += 1
    while pl < nl:
      A[l] = L[pl]
      pl += 1
      l += 1
    
    pl -= 1
    while pr < nr:
      rank = l - start - pr
      while (L[pl][0] == R[pr][0]):
         rank -= 1
         pl -= 1
      
      R[pr][1] += rank
      if R[pr][1] > res: 
        res = R[pr][1]
        
      A[l] = R[pr]
      pr += 1
      l += 1
        
  def merge_sort(T, l, r):
    if l < r:
        m = (l + r) // 2
        merge_sort(T, l, m)
        merge_sort(T, m + 1, r)
        
        merge(T, l, m, r)
        
  merge_sort(mapped_indexes, 0, len(mapped_indexes) - 1)
  return res

# zmien all_tests na True zeby uruchomic wszystkie testy
runtests( maxrank, all_tests = True )

# A =  [12, 17, 6, 7, 16, 13, 10, 19, 12, 17]
# print(maxrank(A))