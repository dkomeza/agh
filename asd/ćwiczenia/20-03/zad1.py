# def partition(A, l, r):
#   a, b, c = A[l], A[(l + r) // 2], A[r]
#   pivot = c
  
#   if (a < b) ^ (a < c):
#     pivot = a
#   elif (b < c) ^ (b < a):
#     pivot = b
#   else:
#     pivot = c
  
#   i = l
#   j = r
  
#   while True:
#     while A[i] < pivot:
#       i += 1
    
#     while A[j] > pivot:
#       j -= 1
    
#     if i >= j:
#       return j
    
#     A[i], A[j] = A[j], A[i]
    
# def quicksort(A, l, r):
#   while l < r:
#     q = partition(A, l, r)
    
#     if q - l > r - q:
#       quicksort(A, q + 1, r)
#       r = q - 1
#     else:
#       quicksort(A, l, q - 1)
#       l = q + 1


def partition(A, l, r):
  pivot = A[r]
  
  i = l
  
  #[]
  
  for j in range(l, r):
    if A[j] < pivot:
      A[k], A[j] = A[j], A[k]
      k += 1
  
  A[i], A[r] = A[r], A[i]
  
  return k

def quicksort(A, l, r):
  if l < r:
    q = partition(A, l, r)
    quicksort(A, l, q - 1)
    quicksort(A, q + 1, r)
   
A = [8, 3, 6, 4, 9, 5, 17, 20, 11, 7]
q = partition(A, 0, len(A) - 1)
# quicksort(A, 0, len(A) - 1)
print(A, A[q])
