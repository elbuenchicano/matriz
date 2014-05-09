// ejerciciosACM.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "tmat.h"


template <class t>
t pot(t b, int a)
{
	if (a == 1) return b;
	if (a & 1)
		return b * pot(b*b, a >> 1);
	else
		return pot(b*b, a >> 1);
}

int fibo(int n)
{
	int z[] {1, 1, 1, 0};
	TMat<int> m(2, 2, z);
	if (n > 3){
		m = pot(m, n - 3);
		return m[0][0] * 2 + m[0][1];
	}
	if (n == 3) return 2;
	if (n < 3 ) return 1;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int z[] {1, 1, 1, 0};
	TMat<int> m(2, 2, z),m2;
	
	cout << fibo(39);
	
	return 0;
}

