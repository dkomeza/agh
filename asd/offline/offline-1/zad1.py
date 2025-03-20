from zad1testy import runtests

def quicksort(T: list[str]):
  n = len(T)
  
  if n <= 1:
    return T
  
  a, b, c = T[0], T[n // 2], T[n - 1]

  pivot = a
  
  if (a < b) ^ (a < c):
    pivot = a
  elif (b < a) ^ (b < c):
    pivot = b
  else:
    pivot = c
  
  left = []
  middle = []
  right = []
  
  for i in range(n):
    if T[i] < pivot:
        left.append(T[i])
    elif T[i] == pivot:
      middle.append(T[i])
    else:
        right.append(T[i])
        
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

  
def strong_string(T):
    n = len(T)
    # maks = 0
    # d = {}
  
    for i in range(n):
        if not compare(T[i]):
            T[i] = T[i][::-1]
        
        # if T[i] in d:
        #   d[T[i]] += 1
        #   if d[T[i]] > maks:
        #     maks = d[T[i]]
        # else:
        #   d[T[i]] = 1
        #   if maks < 1:
        #     maks = 1
        
    T = sorted(T)
    
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


# Odkomentuj by uruchomic duze testy
runtests( strong_string, all_tests=True )

# Zakomentuj gdy uruchamiasz duze testy
# runtests( strong_string, all_tests=False )
