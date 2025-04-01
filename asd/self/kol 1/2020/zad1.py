class Node:
    def __init__(self, val=0, next = None):
        self.val = val
        self.next = next
        

def print_list(p):
    i = 0
    p = p
    while p != None:
        print(f"i: {i}->{p.val}", end="  ")
        p = p.next
        i+=1
    print("")
    
def arr_list(arr):
    res = Node(arr[0])
    p = res
    for i in range(1, len(arr)):
        p.next = Node(arr[i])
        p = p.next
    return res

def middle(p):
    fast = p
    while fast.next is not None and fast.next.next is not None:
        p = p.next
        fast = fast.next.next
    return p 

def merge(p, q):
    res = p
    
    if q.val < p.val:
      p = q
      q = res
      res = p
    
    tail = None
    while p and q:
      if p.val <= q.val:
        tail = p
        p = p.next
        
      else:
        temp = p
        p = q
        q = temp
        tail.next = p
    
    tail.next = q
        
    return res

def merge_sort(p):
    if p is not None and p.next is not None:
        x = middle(p)
        mid = x.next
        x.next = None
    
        p = merge_sort(p)
        mid = merge_sort(mid)
        return merge(p, mid)
    return p
    
    
def SortH(p,k):
    res = p
    
T = [0,1,3,2,4,6,5, 8] # jedno chaotyczna lista 1 = n-k [0,1,3,2,4,6,5] --> []
# T2 = [2, 4, 8] # jedno chaotyczna lista 1 = n-k [0,1,3,2,4,6,5] --> []
p = arr_list(T)
# p2 = arr_list(T2)

# p: 3 5 6
# q: 4 8
# tail: 3 5 6

# temp: 4 8

# res: 2 4 8
print_list(merge_sort(p))


# print(p)
# merge_sort(p)
# print_list(p)