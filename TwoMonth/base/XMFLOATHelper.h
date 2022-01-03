#include <DirectXMath.h>

//XMFLOAT3演算子

//2項演算子オーバーロード
const DirectX::XMFLOAT3 operator+(const DirectX::XMFLOAT3 lhs, const DirectX::XMFLOAT3 rhs);

const DirectX::XMFLOAT3 operator-(const DirectX::XMFLOAT3 &lhs, const DirectX::XMFLOAT3 &rhs);

const DirectX::XMFLOAT3 operator*(const DirectX::XMFLOAT3 &lhs, const DirectX::XMFLOAT3 &rhs);

const DirectX::XMFLOAT3 operator/(const DirectX::XMFLOAT3 &lhs, const DirectX::XMFLOAT3 &rhs);

const DirectX::XMFLOAT3 operator*(const DirectX::XMFLOAT3 &lhs, const float &s);

const DirectX::XMFLOAT3 operator/(const DirectX::XMFLOAT3 &lhs, const float &s);

//XMFLOAT4演算子

//2項演算子オーバーロード
const DirectX::XMFLOAT4 operator+(const DirectX::XMFLOAT4 &lhs, const DirectX::XMFLOAT4 &rhs);

const DirectX::XMFLOAT4 operator-(const DirectX::XMFLOAT4 &lhs, const DirectX::XMFLOAT4 &rhs);

const DirectX::XMFLOAT4 operator*(const DirectX::XMFLOAT4 &lhs, const DirectX::XMFLOAT4 &rhs);

const DirectX::XMFLOAT4 operator/(const DirectX::XMFLOAT4 &lhs, const DirectX::XMFLOAT4 &rhs);

const DirectX::XMFLOAT4 operator*(const DirectX::XMFLOAT4 &lhs, const float &s);

const DirectX::XMFLOAT4 operator/(const DirectX::XMFLOAT4 &lhs, const float &s);