from kol1btesty import runtests

def counting_sort(T):
  count_numbers = [0 for _ in range(27)]  
  n = len(T)
  res = ["" for _ in range(n)]
  
  for i in range(n):
      num = ord(T[i]) - ord("a")
      count_numbers[num]+=1
  
  for i in range(1, 27):
      count_numbers[i] += count_numbers[i-1]
  
  for i in range(n-1, -1, -1):
      num = ord(T[i]) - ord("a")
      count_numbers[num]-=1
      res[count_numbers[num]] = T[i]
  return ''.join(res)

def radix_sort(T):
  isDone = False
  current_index = 1 # From the back
  n = len(T)
  
  while not isDone:
    isDone = True
    count_numbers = [0 for _ in range(28)]  
    res = ["" for _ in range(n)]
    
    for i in range(n):
      current_word = T[i]
      len_word = len(current_word)
      
      if len_word - current_index >= 0:
        isDone = False
        
      num = 0 if len_word < current_index else ord(T[i][len_word - current_index]) - ord("a") + 1      
      
      count_numbers[num]+=1
    
    for i in range(1, 28):
      count_numbers[i] += count_numbers[i-1]
    
    for i in range(n-1, -1, -1):
      current_word = T[i]
      len_word = len(current_word)
      
      if len_word >= current_index:
        isDone = False
      
      num = 0 if current_index > len_word else ord(T[i][len_word - current_index]) - ord("a") + 1
      count_numbers[num]-=1
      res[count_numbers[num]] = T[i]
    
    current_index += 1  
    T = res

  return T

def f(T):
    n = len(T)

    for i in range(n):
        T[i] = counting_sort(T[i])
    
    T = radix_sort(T)
    
    current_word = ""
    current_power = 0
    res = 0
    
    for i in range(n):
      if T[i] == current_word:
        current_power += 1
      else:
        if current_power > res:
          res = current_power
          
        current_word = T[i]
        current_power = 1
    else:
      if current_power > res:
        res = current_power
    return res

T = ["tygrys", "kot", "wilk", "trysyg", "wlik", "sygryt", "likw", "tygrys"]
# print(f(T))

# Zamien all_tests=False na all_tests=True zeby uruchomic wszystkie testy
runtests( f, all_tests=True)
