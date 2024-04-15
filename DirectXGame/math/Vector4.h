#pragma once

/// <summary>
/// 4次元ベクトル
/// </summary>
struct Vector4 final {
	float x = 0;
	float y = 0;
	float z = 0;
	float w = 0;

	// ADD----------------------------------
	Vector4 operator+(const Vector4& obj) const {
		Vector4 result;
		result.x = x + obj.x;
		result.y = y + obj.y;
		result.z = z + obj.z;
		result.w = w + obj.w;

		return result;
	}
	void operator+=(const Vector4& obj) {
		x += obj.x;
		z += obj.z;
		y += obj.y;
		w += obj.w;
	}
	Vector4 operator+(float obj) const {
		Vector4 result;
		result.x = x + obj;
		result.y = y + obj;
		result.z = z + obj;
		result.w = w + obj;

		return result;
	}
	void operator+=(float obj) {
		x += obj;
		y += obj;
		z += obj;
		w += obj;
	}

	// SUB----------------------------------
	Vector4 operator-(const Vector4& obj) const {
		Vector4 result;
		result.x = x - obj.x;
		result.y = y - obj.y;
		result.z = z - obj.z;
		result.w = w - obj.w;

		return result;
	}
	void operator-=(const Vector4& obj) {
		x -= obj.x;
		y -= obj.y;
		z -= obj.z;
		w -= obj.w;
	}
	Vector4 operator-(float obj) const {
		Vector4 result;
		result.x = x - obj;
		result.y = y - obj;
		result.z = z - obj;
		result.w = w - obj;

		return result;
	}
	void operator-=(float obj) {
		x -= obj;
		y -= obj;
		z -= obj;
		w -= obj;
	}

	// MULTIPLY-----------------------------
	Vector4 operator*(const Vector4& obj) const {
		Vector4 result;
		result.x = x * obj.x;
		result.y = y * obj.y;
		result.z = z * obj.z;
		result.w = w * obj.w;

		return result;
	}
	void operator*=(const Vector4& obj) {
		x *= obj.x;
		y *= obj.y;
		z *= obj.z;
		w *= obj.w;
	}
	Vector4 operator*(float obj) const {
		Vector4 result;
		result.x = x * obj;
		result.y = y * obj;
		result.z = z * obj;
		result.w = w * obj;

		return result;
	}
	void operator*=(float obj) {
		x *= obj;
		y *= obj;
		z *= obj;
		w *= obj;
	}
};