def quicksort(T):
  n = len(T)
  
  if n <= 1:
    return T
  pivot = T[n // 2]
  
  left = [x for x in T if x < pivot]
  middle = [x for x in T if x == pivot]
  right = [x for x in T if x > pivot]
  
  return quicksort(left) + middle + quicksort(right)

def compare(w: str):
  pl = 0
  pr = len(w) - 1
  
  while pl < pr:
    if w[pl] < w[pr]:
      return True
    elif w[pl] > w[pr]:
      return False
    
    pl += 1
    pr -= 1
    
  return True

def g(T):
  n = len(T)
  
  for i in range(n):
    if not compare(T[i]):
      T[i] = T[::-1]
      
  T = quicksort(T)
  
  maks = 0
  current = 0
  current_word = ""
  
  for w in T:
    if current_word == w:
      current += 1
    else: 
      if current > maks:
        maks = current
        
      current = 1
      current_word = w
  
  if current > maks:
    maks = current
  
  return maks
       
