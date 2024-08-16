#ifndef LIB_FAST_POW_H_
#define LIB_FAST_POW_H_

namespace lib {

template <class T>
T fast_pow(T x, unsigned long long n) {
	T res = 1;
	while (n) {
		if (n&1ULL) res *= x;
		x *= x;
		n >>= 1;
	}
	return res;
}

} // namesapce lib

#endif // LIB_FAST_POW_H_
