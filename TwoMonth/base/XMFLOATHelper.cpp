#include"XMFLOATHelper.h"

const DirectX::XMFLOAT3 operator+(const DirectX::XMFLOAT3 lhs, const DirectX::XMFLOAT3 rhs)
{
	DirectX::XMFLOAT3 result;
	result.x = lhs.x + rhs.x;
	result.y = lhs.y + rhs.y;
	result.z = lhs.z + rhs.z;
	return result;
}

const DirectX::XMFLOAT3 operator-(const DirectX::XMFLOAT3 &lhs, const DirectX::XMFLOAT3 &rhs)
{
	DirectX::XMFLOAT3 result;
	result.x = lhs.x - rhs.x;
	result.y = lhs.y - rhs.y;
	result.z = lhs.z - rhs.z;
	return result;
}

const DirectX::XMFLOAT3 operator*(const DirectX::XMFLOAT3 &lhs, const DirectX::XMFLOAT3 &rhs)
{
	DirectX::XMFLOAT3 result;
	result.x = lhs.x * rhs.x;
	result.y = lhs.y * rhs.y;
	result.z = lhs.z * rhs.z;
	return result;
}

const DirectX::XMFLOAT3 operator/(const DirectX::XMFLOAT3 &lhs, const DirectX::XMFLOAT3 &rhs)
{
	DirectX::XMFLOAT3 result;
	result.x = lhs.x / rhs.x;
	result.y = lhs.y / rhs.y;
	result.z = lhs.z / rhs.z;
	return result;
}

const DirectX::XMFLOAT3 operator*(const DirectX::XMFLOAT3 &lhs, const float &s)
{
	DirectX::XMFLOAT3 result;
	result.x = lhs.x * s;
	result.y = lhs.y * s;
	result.z = lhs.z * s;
	return result;
}

const DirectX::XMFLOAT3 operator/(const DirectX::XMFLOAT3 &lhs, const float &s)
{
	DirectX::XMFLOAT3 result;
	result.x = lhs.x / s;
	result.y = lhs.y / s;
	result.z = lhs.z / s;
	return result;
}


const DirectX::XMFLOAT4 operator+(const DirectX::XMFLOAT4 &lhs, const DirectX::XMFLOAT4 &rhs)
{
	DirectX::XMFLOAT4 result;
	result.x = lhs.x + rhs.x;
	result.y = lhs.y + rhs.y;
	result.z = lhs.z + rhs.z;
	result.w = lhs.w + rhs.w;
	return result;
}

const DirectX::XMFLOAT4 operator-(const DirectX::XMFLOAT4 &lhs, const DirectX::XMFLOAT4 &rhs)
{
	DirectX::XMFLOAT4 result;
	result.x = lhs.x - rhs.x;
	result.y = lhs.y - rhs.y;
	result.z = lhs.z - rhs.z;
	result.w = lhs.w - rhs.w;
	return result;
}

const DirectX::XMFLOAT4 operator*(const DirectX::XMFLOAT4 &lhs, const DirectX::XMFLOAT4 &rhs)
{
	DirectX::XMFLOAT4 result;
	result.x = lhs.x * rhs.x;
	result.y = lhs.y * rhs.y;
	result.z = lhs.z * rhs.z;
	result.w = lhs.w * rhs.w;
	return result;
}

const DirectX::XMFLOAT4 operator/(const DirectX::XMFLOAT4 &lhs, const DirectX::XMFLOAT4 &rhs)
{
	DirectX::XMFLOAT4 result;
	result.x = lhs.x / rhs.x;
	result.y = lhs.y / rhs.y;
	result.z = lhs.z / rhs.z;
	result.w = lhs.w / rhs.w;
	return result;
}

const DirectX::XMFLOAT4 operator*(const DirectX::XMFLOAT4 &lhs, const float &s)
{
	DirectX::XMFLOAT4 result;
	result.x = lhs.x * s;
	result.y = lhs.y * s;
	result.z = lhs.z * s;
	result.w = lhs.w * s;
	return result;
}

const DirectX::XMFLOAT4 operator/(const DirectX::XMFLOAT4 &lhs, const float &s)
{
	DirectX::XMFLOAT4 result;
	result.x = lhs.x / s;
	result.y = lhs.y / s;
	result.z = lhs.z / s;
	result.w = lhs.w / s;
	return result;
}
