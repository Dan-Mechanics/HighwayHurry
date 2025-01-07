#pragma once

/// <summary>
/// TODO: fix operators
/// and add assigment operator. assignment should be valeu type not reference
/// </summary>
struct Vector3 {
public: // Technically speaking, this doesnt have to be here since classes are default public.
	float xComponent{};
	float yComponent{};

	/// <summary>
	/// FUTURE: I could use quicksort for the sorting order of the zComponent entity.
	/// </summary>
	float zComponent{};

	Vector3();
	Vector3(const float x, const float y, const float z);

	

	Vector3 operator+(const Vector3& container) const;
	Vector3& operator+=(const Vector3& container);

	Vector3 operator-(const Vector3& container) const;
	Vector3& operator-=(const Vector3& container);

	/// <summary>
	/// BUG FIX: this was programmed wrong and messed with the obstacle
	/// speeds but somehow still worked, but is fixed now.
	/// </summary>
	Vector3 operator*(const float scalar) const;
	Vector3& operator*=(const float scalar);

	/// <summary>
	/// Alloc-free.
	/// </summary>
	void setAll(const float x, const float y, const float z);

	/// <summary>
	/// Print components.
	/// </summary>
	void logComponents() const;

	void add(const Vector3 vec);

	/// <summary>
	/// Multiply the components before adding them.
	/// </summary>
	void add(const Vector3& vec, const float mult);
	void remove(const Vector3 vec);
	void multiply(const float scalar);
	void divide(const float scalar);

	/// <summary>
	/// Multiply the components before adding them.
	/// </summary>
	void invert();

	/// <summary>
	/// Get length.
	/// </summary>
	float calculateMagnitude();

	/// <summary>
	/// Make the length 1.
	/// </summary>
	void normalize();

	/// <summary>
	/// Limit the length of the vector.
	/// </summary>
	void clampMagnitude(const float magnitude);

	/// <summary>
	/// https://discussions.unity.com/t/using-mathf-round-for-a-vector3/88858
	/// </summary>
	void round(const float grid);

	float calcDotProduct(const Vector3& other) const;
	float calcNormalizedDotProduct(Vector3 b) const;
	Vector3 cross(const Vector3& other) const;
	float getAngle() const;
	void setWithAngleAndLength(float angle, const float length);
	float calculateDistanceTo(const Vector3& other) const;
};