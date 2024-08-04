def gcd(a, b):
    while b:
        a, b = b, a % b
    return a

def lcm(a, b):
    return a * b // gcd(a, b)

def find_period(s):
    n = len(s)
    prefix_table = [0] * n
    j = 0

    for i in range(1, n):
        while (j > 0 and s[i] != s[j]):
            j = prefix_table[j - 1]
        if s[i] == s[j]:
            j += 1
            prefix_table[i] = j
        else:
            prefix_table[i] = 0
    
    period = n - prefix_table[-1]
    if n % period == 0:
        return period
    else:
        return n

def can_form_t(s, n, m):
    period_s = find_period(s)
    period_length_s = len(s[:period_s])

    lcm_length = lcm(period_length_s * n, m)
    if lcm_length % period_length_s == 0:
        return True
    return False

# Example usage:
S = input()
n, m = map(int, input().split())

print(can_form_t(S, n, m))  # Output: True

