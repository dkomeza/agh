class Branch():
    def __init__(self):
        self.s = ""
        self.p = ""
        self.left = None
        self.right = None
        
branch = Branch()

def isMatch(s: str, p: str, b: Branch) -> bool:
    b.s = s
    b.p = p
    
    isRepeating = False
    if len(p) > 1:
        isRepeating = p[1] == '*'
    
    if len(s) == 0 and len(p) == 2 and isRepeating:
        return True
                
    if len(s) == 1 and (len(p) == 1 or (len(p) == 2 and isRepeating)):
        return s[0] == p[0] or p[0] == '.'
    
    if len(s) == 0 or len(p) == 0:
        return False

    if isRepeating:
        left = Branch()
        right = Branch()
        b.left = left
        b.right = right
        
        if s[0] == p[0] or p[0] == '.':
            return isMatch(s[1:], p[2:], left) or isMatch(s[1:], p, right) or isMatch(s, p[2:], right)
        else:
            return isMatch(s, p[2:], left)
        
    else:
        if s[0] != p[0] and p[0] != '.':
            return False
        
        new = Branch()
        b.left = new
        return isMatch(s[1:], p[1:], new)
    
    
def print_tree(root, print_val, left="left", right="right"):
    def display(root, print_val=print_val, left=left, right=right):
        """Returns list of strings, width, height, and horizontal coordinate of the root."""
        # No child.
        if getattr(root, right) is None and getattr(root, left) is None:
            line = print_val(root)
            width = len(line)
            height = 1
            middle = width // 2
            return [line], width, height, middle

        # Only left child.
        if getattr(root, right) is None:
            lines, n, p, x = display(getattr(root, left))
            s = print_val(root)
            u = len(s)
            first_line = (x + 1) * ' ' + (n - x - 1) * '_' + s
            second_line = x * ' ' + '/' + (n - x - 1 + u) * ' '
            shifted_lines = [line + u * ' ' for line in lines]
            return [first_line, second_line] + shifted_lines, n + u, p + 2, n + u // 2

        # Only right child.
        if getattr(root, left) is None:
            lines, n, p, x = display(getattr(root, right))
            s = print_val(root)
            u = len(s)
            first_line = s + x * '_' + (n - x) * ' '
            second_line = (u + x) * ' ' + '\\' + (n - x - 1) * ' '
            shifted_lines = [u * ' ' + line for line in lines]
            return [first_line, second_line] + shifted_lines, n + u, p + 2, u // 2

        # Two children.
        left, n, p, x = display(getattr(root, left))
        right, m, q, y = display(getattr(root, right))
        s = print_val(root)
        u = len(s)
        first_line = (x + 1) * ' ' + (n - x - 1) * '_' + s + y * '_' + (m - y) * ' '
        second_line = x * ' ' + '/' + (n - x - 1 + u + y) * ' ' + '\\' + (m - y - 1) * ' '
        if p < q:
            left += [n * ' '] * (q - p)
        elif q < p:
            right += [m * ' '] * (p - q)
        zipped_lines = zip(left, right)
        lines = [first_line, second_line] + [a + u * ' ' + b for a, b in zipped_lines]
        return lines, n + m + u, max(p, q) + 2, n + u // 2

    lines, *_ = display(root, print_val, left, right)
    for line in lines:
        print(line)
        
# print(isMatch("aa", "a")) # False
# print(isMatch("aa", "a*")) # True
# print(isMatch("ab", ".*")) # True
# print(isMatch("aab", "c*a*b")) # True
print(isMatch("mississippi", "mis*is*p*.", branch)) # False

def print_line(branch: Branch):
    return f"{branch.s} - {branch.p}"

# print_tree(branch, print_line)
# print(isMatch("asdfasdf", ".*fd", branch))
# print(isMatch("a", "a*a", branch))
print_tree(branch, print_line)

