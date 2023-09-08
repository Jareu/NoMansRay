#pragma once

template <typename T>
class Vector3 {
public:
	T x = 0;
	T y = 0;
	T z = 0;

	Vector3() = delete;
	Vector3(T x, T y, T z) : x{ x }, y{ y }, z{ z } {
		static_assert(std::is_arithmetic<T>::value, "Vector3 must be numeric type.");
	};


	// addition with same type
	const Vector3 operator+(const Vector3& rhs) const {
		return Vector3{
			this->x + rhs.x,
			this->y + rhs.y,
			this->z + rhs.z
		};
	}

	// addition with different type
	template <typename B>
	const Vector3 operator+(const Vector3<B>& rhs) const {
		static_assert(std::is_arithmetic<B>::value, "RHS must be numeric type for operator +");
		return Vector3{
			this->x + static_cast<T> (rhs.x),
			this->y + static_cast<T> (rhs.y),
			this->z + static_cast<T> (rhs.z)
		};
	}

	// addition and assignment with same type
	Vector3& operator+=(const Vector3& rhs) {
		this->x = this->x + rhs.x;
		this->y = this->y + rhs.y;
		this->z = this->z + rhs.z;
		return *this;
	}

	// subtraction with same type
	const Vector3 operator-(const Vector3& rhs) const {
		return Vector3{
			this->x - rhs.x,
			this->y - rhs.y,
			this->z - rhs.z
		};
	}

	// subtraction with different type
	template <typename B>
	const Vector3 operator-(const Vector3<B>& rhs) const {
		static_assert(std::is_arithmetic<B>::value, "RHS must be numeric type for operator -");
		return Vector3{
			this->x - static_cast<T> (rhs.x),
			this->y - static_cast<T> (rhs.y),
			this->z - static_cast<T> (rhs.z)
		};
	}

	// subtraction and assignment with same type
	Vector3& operator-=(const Vector3& rhs) {
		this->x = this->x - rhs.x;
		this->y = this->y - rhs.y;
		this->z = this->z - rhs.z;
		return *this;
	}

	// multiplication with scalar
	template <typename B>
	Vector3 operator*(const B& rhs) const {
		static_assert(std::is_arithmetic<B>::value, "RHS must be numeric type for operator *");
		return Vector3{
			this->x * static_cast<T> (rhs),
			this->y * static_cast<T> (rhs),
			this->z * static_cast<T> (rhs)
		};
	}

	// multiplication and assignment with scalar
	template <typename B>
	Vector3& operator*=(const B& rhs) {
		static_assert(std::is_arithmetic<B>::value, "RHS must be numeric type for operator *=");
		this->x = this->x * static_cast<T> (rhs);
		this->y = this->y * static_cast<T> (rhs);
		this->z = this->z * static_cast<T> (rhs);
		return *this;
	}

	// division with scalar
	template <typename B>
	Vector3 operator/(const B& rhs) const {
		static_assert(std::is_arithmetic<B>::value, "RHS must be numeric type for operator /");
		return Vector3{
			this->x / static_cast<T> (rhs),
			this->y / static_cast<T> (rhs),
			this->z / static_cast<T> (rhs)
		};
	}

	// division and assignment with scalar
	template <typename B>
	Vector3& operator/=(const B& rhs) {
		static_assert(std::is_arithmetic<B>::value, "RHS must be numeric type for operator /=");
		this->x = this->x / static_cast<T> (rhs);
		this->y = this->y / static_cast<T> (rhs);
		this->z = this->z / static_cast<T> (rhs);
		return *this;
	}
};