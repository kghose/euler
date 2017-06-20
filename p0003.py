def primes(m=100):
  """Return a list of all prime numbers up-to and including m"""
  pl = []
  for n in range(2, m + 1):
    is_prime = True
    for x in pl:
      if n % x == 0:
        is_prime = False
        break
    if is_prime:
      pl.append(n)
  return pl


def test_primes():
  assert primes(10) == [2, 3, 5, 7]


def prime_recur(m=100, n=2, pl=[]):
  """Return all primes up to and including m.
  e.g. prime_recur(10)"""
  if n <= m:
    for x in pl:
      if n % x == 0:
        return prime_recur(m=m, n=n + 1, pl=pl)  # It's not a prime, continue the hunt
    return prime_recur(m=m, n=n + 1, pl=pl + [n])  # It's a prime, add to the list and continue the hunt
  else:
    return pl  # We are done, go back


def test_primes_recur():
  assert prime_recur(10) == [2, 3, 5, 7]