#ifndef LIB_FACTORIAL_TABLE_H_
#define LIB_FACTORIAL_TABLE_H_

#include <cassert>
#include <vector>

namespace lib {

template <class T>
class factorial_table {
public:
	factorial_table(): n_(0) {}
	explicit factorial_table(int n): n_(n), fac_(n+1), ifac_(n+1) {
		fac_[0] = 1;
		for (int i=1; i<=n; i++) fac_[i] = fac_[i-1]*i;
		ifac_[n] = 1/fac_[n];
		for (int i=n-1; i>=0; i--) ifac_[i] = ifac_[i+1]*(i+1);
	}

	T permutation(int n, int k) const {
		assert(0<=n && n<=n_);
		assert(0<=k && k<=n);
		return fac_[n]*ifac_[n-k];
	}

	T combination(int n, int k) const {
		assert(0<=n && n<=n_);
		assert(0<=k && k<=n);
		return fac_[n]*ifac_[n-k]*ifac_[k];
	}

	T homogeneous(int n, int k) const {
		assert(0<=k && k<=n_);
		assert(0<=n && n+k-1<=n_);
		return combination(n+k-1, k);
	}

private:
	const int n_;
	std::vector<T> fac_, ifac_;
};

} // namespace lib

#endif // LIB_FACTORIAL_TABLE_H_
