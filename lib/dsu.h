#ifndef LIB_DSU_H_
#define LIB_DSU_H_

#include <vector>
#include <cassert>

namespace lib {

class dsu {
public:
	dsu(): n_(0) {}
	explicit dsu(int n): n_(n), data_(n, -1) {}

	int merge(int x, int y) {
		assert(0<=x && x<n_);
		assert(0<=y && y<n_);
		x = root(x), y = root(y);
		if (x == y) return x;
		if (-data_[x] < -data_[y]) std::swap(x, y);
		data_[x] += data_[y];
		data_[y] = x;
		return x;
	}

	int root(int x) {
		assert(0<=x && x<n_);
		if (data_[x] < 0) return x;
		return data_[x] = root(data_[x]);
	}

	bool same(int x, int y) {
		assert(0<=x && x<n_);
		assert(0<=y && y<n_);
		return root(x)==root(y);
	}

	int size(int x) {
		assert(0<=x && x<n_);
		return -data_[root(x)];
	}

private:
	int n_;
	std::vector<int> data_;
};

} // namespace lib

#endif // LIB_DSU_H_
