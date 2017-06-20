def palindrome():
  for i in range(999, 100, -1):
    for j in range(999, i, -1):
      n = str(i * j)
      print i, j, n
      if n == n[::-1]:
        return i, j, n
  return None


def product():
  cntr = 0
  for i in range(999, 100, -1):
    for j in range(999, i, -1):
      print i, j, i * j
      cntr += 1
      if cntr > 100:
        break


print(product())



# print(palindrome())