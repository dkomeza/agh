def ohnosort(A: list[int]):
  count = [0 for _ in range(len(A) ** 2)]
  output = [0 for _ in range(len(A))]
  
  for i in range(len(A)):
    j = A[i]
    count[j] += 1
  
  print(count)
   
  for i in range(1, len(A)**2):
    count[i] = count[i] + count[i - 1]
          
  print(count)
          
  for i in range(len(A) - 1, -1, -1):
      j = A[i]
      count[j] -= 1
      output[count[j]] = A[i]
  return output
  
A = [6, 38, 38, 15, 30, 24, 4, 36, 37, 28, 10, 2, 42, 22, 40, 16, 39, 33, 5, 18, 44, 7, 32, 25, 21]
print(ohnosort(A))