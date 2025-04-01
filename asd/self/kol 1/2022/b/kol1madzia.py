from kol1btesty import runtests   
def counting_sort(T, k):
    count_numbers = [0 for _ in range(k+1)]  
    n = len(T)
    res = [0 for _ in range(n)]
    
    for i in range(n):
        num = ord(T[i]) - ord("a")
        count_numbers[num]+=1
    
    for i in range(1,k+1):
        count_numbers[i] += count_numbers[i-1]
    
    for i in range(n-1, -1, -1):
        num = ord(T[i]) - ord("a")
        count_numbers[num]-=1
        res[count_numbers[num]] = T[i]
    return res

def radix_sort(T, k, letter):
    n = len(T)
    count_numbers = [0 for _ in range(k+2)]  
    res = [0 for _ in range(n)]
    
    for i in range(n):
        lword = len(T[i])
        num = 0
        if lword >= letter:
            num = ord(T[i][lword - letter]) - ord("a") + 1
        count_numbers[num]+=1
    
    for i in range(1,k+2):
        count_numbers[i] += count_numbers[i-1]
    
    for i in range(n-1, -1, -1):
        lword = len(T[i])
        num = 0
        if lword >= letter:
            num = ord(T[i][lword - letter]) - ord("a") + 1
        count_numbers[num]-=1
        res[count_numbers[num]] = T[i]
    return res
      

def f(T):
    n = len(T)
    number_of_letters = ord("z") - ord("a") + 1
    maks_letters = 0
   
    for i in range(n):
        T[i] = counting_sort(T[i], number_of_letters)
        l = len(T[i])
        if l > maks_letters:
            maks_letters = l
            
    for i in range(1, maks_letters):
        T = radix_sort(T, number_of_letters, i)

    cur = []
    maks = 0
    counter = 0
    for i in range(n):
        if T[i] == cur:
            counter+=1
        else:
            if counter > maks:
                maks = counter
            counter = 1
            cur = T[i]
    if counter > maks:
        maks = counter
    return maks
runtests( f, all_tests=True )