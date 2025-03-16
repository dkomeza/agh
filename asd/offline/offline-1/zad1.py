from zad1testy import runtests

def quicksort(T: list[str]):
  n = len(T)
  
  if n <= 1:
    return T

  ind = n // 2

  pivot = T[ind]
  
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
  
#   left = [x for x in T if x < pivot]
#   middle = [x for x in T if x == pivot]
#   right = [x for x in T if x > pivot]
  
#   return quicksort(left) + middle + quicksort(right)

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
  
    for i in range(n):
        if not compare(T[i]):
            T[i] = T[i][::-1]
        
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


# Odkomentuj by uruchomic duze testy
# runtests( strong_string, all_tests=True )

# Zakomentuj gdy uruchamiasz duze testy
runtests( strong_string, all_tests=True )
