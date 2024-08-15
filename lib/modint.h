#ifndef LIB_MODINT_H_
#define LIB_MODINT_H_

#include <iostream>
#include <utility>

namespace lib {

template <unsigned int MOD>
class modint {
public:
	constexpr modint() noexcept : val_(0) {}
	template <class T>
	constexpr modint(T val) noexcept : val_((val%=MOD)<0?val+MOD:val) {}

	constexpr unsigned int val() const noexcept { return val_; }

	constexpr modint& operator++() noexcept {
		if (++val_ == MOD) val_ = 0;
		return *this;
	}

	constexpr modint& operator--() noexcept {
		if (val_ == 0) val_ = MOD;
		return *this;
	}

	constexpr modint operator++(int) noexcept {
		modint res = *this;
		++*this;
		return *this;
	}

	constexpr modint operator--(int) noexcept {
		modint res = *this;
		--*this;
		return res;
	}

	constexpr modint& operator+=(const modint& rhs) noexcept {
		val_ += rhs.val_;
		if (val_ >= MOD) val_ -= MOD;
		return *this;
	}

	constexpr modint& operator-=(const modint& rhs) noexcept {
		if (val_ < rhs.val_) val_ += MOD;
		val_ -= rhs.val_;
		return *this;
	}

	constexpr modint& operator*=(const modint& rhs) noexcept {
		val_ = (long long)val_*rhs.val_%MOD;
		return *this;
	}

	constexpr modint& operator/=(const modint& rhs) noexcept {
		long long a = rhs.val_, b = MOD, u = 1, v = 0;
		while (b) {
			long long t = a/b;
			a -= t*b;
			std::swap(a, b);
			u -= t*v;
			std::swap(u, v);
		}
		int x = (long long)val_*u%MOD;
		if (x < 0) x += MOD;
		val_ = x;
		return *this;
	}

	friend constexpr modint operator+(const modint& lhs, const modint& rhs) noexcept {
		return (modint)lhs+=rhs;
	}

	friend constexpr modint operator-(const modint& lhs, const modint& rhs) noexcept {
		return (modint)lhs-=rhs;
	}

	friend constexpr modint operator*(const modint& lhs, const modint& rhs) noexcept {
		return (modint)lhs*=rhs;
	}

	friend constexpr modint operator/(const modint& lhs, const modint& rhs) noexcept {
		return (modint)lhs/=rhs;
	}

	friend constexpr bool operator==(const modint& lhs, const modint& rhs) noexcept {
		return lhs.val_==rhs.val_;
	}

	friend constexpr bool operator!=(const modint& lhs, const modint& rhs) noexcept {
		return lhs.val_!=rhs.val_;
	}

	friend std::istream& operator>>(std::istream& is, modint& rhs) {
		long long x;
		is >> x;
		rhs = (modint)x;
		return is;
	}

	friend std::ostream& operator<<(std::ostream& os, const modint& rhs) { return os<<rhs.val_; }

private:
	unsigned int val_;
};

} // namespace lib

#endif // LIB_MODINT_H_
