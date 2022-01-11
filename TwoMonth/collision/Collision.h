#pragma once
#include"CollisionPrimitive.h"
#include"../2d/Sprite.h"
///<summary>
///当たり判定ヘルパークラス
///</summary>
class Collision
{
public:
	///<summary>
	///球と平面の当たり判定
	///</summary>
	/// <param name="sphere">球</param>
	/// <param name="plane">平面</param>
	/// <param name="inter">交点（平面上の最近接点）</param>
	/// <returns>交差しているか否か</returns>
	static bool CheckSpahere2Plane(const Sphere &sphere, const Plane &plane, DirectX::XMVECTOR *inter = nullptr);


	///<summary>
	///点と三角形の最近接点を求める
	///</summary>
	/// <param name="point">点</param>
	/// <param name="triangle">三角形</param>
	/// <param name="closest">最近接点(出力用)（平面上の最近接点）</param>
	/// <returns>交差しているか否か</returns>
	static void ClosestPtPoint2Triangle(const DirectX::XMVECTOR &point,
		const Triangle &triangle, DirectX::XMVECTOR *closest);

	///<summary>
	///球と法線付き三角形の当たりチェック
	///</summary>
	/// <param name="sphere">球</param>
	/// <param name="triangle">三角形</param>
	/// <param name="inter">交点（三角形上の最近接点）</param>
	/// <returns>交差しているか否か</returns>
	static bool CheckSphere2Triangle(const Sphere &sphere, const Triangle &triangle, DirectX::XMVECTOR *inter = nullptr);


	///<summary>
	///レイと平面の当たり判定
	///</summary>
	/// <param name="lay">レイ</param>
	/// <param name="plane">平面</param>
	/// <param name="inter">距離（出力用）</param>
	///  <param name="inter">交点（出力用）</param>
	/// <returns>交差しているか否か</returns>
	static bool CheckRay2Plane(const Ray &ray, const Plane &plane, float *distance = nullptr, DirectX::XMVECTOR *inter = nullptr);

	/// <summary>
	/// 長方形と長方形の当たり判定
	/// </summary>
	/// <param name="pos1"></param>
	/// <param name="width1"></param>
	/// <param name="height1"></param>
	/// <param name="pos2"></param>
	/// <param name="width2"></param>
	/// <param name="height2"></param>
	/// <returns></returns>
	static int MapChipCollision(XMFLOAT2 pos1, XMFLOAT2 oldPos, float width1, float height1, XMFLOAT2 pos2, float width2, float height2);


};