from zad2testy import runtests

def merge(A, l, m, r):
    inversions = 0
    
    L = A[l:m+1]
    R = A[m+1:r+1]
    
    pl, pr, nl, nr = 0, 0, len(L), len(R)
    
    while pl < nl and pr < nr:
        if R[pr] < L[pl]:
            inversions += nl - pl
            A[l] = R[pr]
            pr += 1
        else:
            A[l] = L[pl]
            pl += 1
        l += 1
    
    while pl < nl:
        A[l] = L[pl]
        pl += 1
        l += 1
    
    while pr < nr:
        A[l] = R[pr]
        pr += 1
        l += 1
        
    return inversions
    
def merge_sort(A, l, r, inversions):
    if l < r:
        m = (l + r) // 2
        inversions = merge_sort(A, l, m, inversions)
        inversions += merge_sort(A, m + 1, r, inversions)
        
        inversions += merge(A, l, m, r)
        return inversions
    return 0

def count_inversions(A):
    inversions = 0
         
    return merge_sort(A, 0, len(A) - 1, inversions)
    

# Odkomentuj by uruchomic duze testy
# runtests( strong_string, all_tests=True )

# Zakomentuj gdy uruchamiasz duze testy
runtests( count_inversions, all_tests=True )

# print(count_inversions([1, 20, 6, 4, 5]))
