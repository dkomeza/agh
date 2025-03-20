def partition(A, l, r):
  pivot = A[l]
  i = l
  j = r
  
  while True:
    while A[i] < pivot:
      i += 1
    
    while A[j] > pivot:
      j -= 1
    
    if i >= j:
      return j
    
    A[i], A[j] = A[j], A[i]
    
def quicksort(A, l, r):
  while l < r:
    q = partition(A, l, r)
    
    if q - l > r - q:
      quicksort(A, q + 1, r)
      r = q - 1
    else:
      quicksort(A, l, q - 1)
      l = q + 1
    
A = [8, 3, 6, 4, 9, 5, 17, 20, 11, 1]
quicksort(A, 0, len(A) - 1)
print(A)
    