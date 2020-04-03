// leins, 22.03.2018 

#include <climits>
#include "numbers.h"

using namespace std;

static uint s_MyPow(uint a, uint n, my_error_t &error)
{
  uint res = 1;

  // odz check
  if (n == 0 && a == 0)
    error = err_bad_param;
  else if (n == 1)
    res = a;
  else if (a == 0)
    return 0;
  else
  {
    while (n)
    {
      if (UINT_MAX / a < res) // memory check
      {
        error = err_no_memory;
        break;
      }
      if (n & 1)
        res *= a;
      a *= a;
      n >>= 1;
    }
  }
  return res;
} // end of func

// number of partial permutations
// algoritm has taken by Novikov
uint GetU(uint m, uint n, my_error_t &error)
{
  uint res = 0;

  // odz check
  if (m == 0 && n == 0)
    error = err_bad_param;
  else
    res = s_MyPow(m, n, error);

  return res;
}

// number of partial permutations without repetitions
// algoritm has taken by Novikov
uint GetA(uint m, uint n, my_error_t &error)
{
  uint res = 1;

  // odz check
  if (n == 0)
    res = 1;
  else if (n > m && m > 0)
    res = 0;
  else
  {
    for (uint i = 0; i < n; i++)
    {
    if (res > UINT_MAX / (m - i)) // memory check
    {
      error = err_no_memory;
      break;
    }
    res *= m - i;
    }
  }
  return res;
}

// number of permutations
// algoritm has taken by Novikov
uint GetP(uint n, my_error_t &error)
{
  return GetA(n ,n, error);
}

// number of combinations
// algoritm has taken by Novikov
uint GetC(uint m, uint n, my_error_t &error)
{
  uint *A = new uint[n + 1];
  uint res = 1;

  // odz check
  if (n == 1 || m == n + 1)
    res = m;
  else if (n > m)
    res = 0;
  else if (n == m)
    res = 1;
  else
  {
    if (n > m - n)
      n = m - n;
    if (m > n + 1)
    {
      for (uint i = 0; i <= n; i++) // initialization
        A[i] = 1;

      for (uint i = 1; i <= m - n; i++)
      {
        for (uint j = 1; j <= n; j++)
        {
          if (A[j] > UINT_MAX - A[j - 1]) // memory check
          {
            error = err_no_memory;
            break;
          }
          A[j] = A[j] + A[j - 1];
        }

        if (error)
          break;
      }

      res = A[n];
    }
  }
  delete[] A;
  return res;
}

// number of Stirling of second kind
// algoritm has taken by Novikov
uint GetS(uint m, uint n, my_error_t &error)
{
  uint *D = new uint[n];
  uint res = 0;

  // odz check
  if (m == n || n == 1)
	res = 1;
  else if ((m > 0 && n == 0) || n > m)
  res = 0;

  else
  {
    for (uint i = 0; i < n; i++) // initialization
      D[i] = 1;

	for (uint i = 0; i < m - n; i++)
	{
	  for (uint j = 1; j < n; j++)
	  {
		if ((D[j - 1] > UINT_MAX - (j + 1) * D[j]) ||
		    ((j + 1) * D[j] > UINT_MAX - D[j - 1])) // memory check
		{
		  error = err_no_memory;
		  break;
		}
		D[j] = D[j - 1] + (j + 1) * D[j];
	  }
	  if (error)
		break;
	}
    
	res = D[n - 1];
  }

  delete[] D;
  return res;
}

// number of Bell
// algoritm has taken by Novikov
uint GetB(uint n, my_error_t &error)
{
  uint *A = new uint[n];
  uint res = 0;

  if (n > 0)
  {
	A[0] = 1;
	for (uint n1 = 1; n1 < n; n1++)
	{
	  int t = A[0];

	  A[0] = A[n1 - 1];
	  for (uint k = 1; k <= n1; k++)
	  {
		uint s = A[k];

		if (A[k - 1] > UINT_MAX - t) // memory check
		{                           // for all k A[k -1] > t (from Bells triangle)
		  error = err_no_memory;
		  break;
		}
		A[k] = A[k - 1] + t;        
		t = s;
	  }
	  if (error)
		break;
	}
	res = A[n - 1];
  }
  else if (n == 0)
	res = 1;
  else
	error = err_bad_param;

  delete[] A;
  return res;
}
