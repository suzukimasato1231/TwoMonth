#pragma once
#include"CollisionPrimitive.h"

///<summary>
///�����蔻��w���p�[�N���X
///</summary>
class Collision
{
public:
	///<summary>
	///���ƕ��ʂ̓����蔻��
	///</summary>
	/// <param name="sphere">��</param>
	/// <param name="plane">����</param>
	/// <param name="inter">��_�i���ʏ�̍ŋߐړ_�j</param>
	/// <returns>�������Ă��邩�ۂ�</returns>
	static bool CheckSpahere2Plane(const Sphere &sphere, const Plane &plane, DirectX::XMVECTOR *inter = nullptr);


	///<summary>
	///�_�ƎO�p�`�̍ŋߐړ_�����߂�
	///</summary>
	/// <param name="point">�_</param>
	/// <param name="triangle">�O�p�`</param>
	/// <param name="closest">�ŋߐړ_(�o�͗p)�i���ʏ�̍ŋߐړ_�j</param>
	/// <returns>�������Ă��邩�ۂ�</returns>
	static void ClosestPtPoint2Triangle(const DirectX::XMVECTOR &point,
		const Triangle &triangle, DirectX::XMVECTOR *closest);

	///<summary>
	///���Ɩ@���t���O�p�`�̓�����`�F�b�N
	///</summary>
	/// <param name="sphere">��</param>
	/// <param name="triangle">�O�p�`</param>
	/// <param name="inter">��_�i�O�p�`��̍ŋߐړ_�j</param>
	/// <returns>�������Ă��邩�ۂ�</returns>
	static bool CheckSphere2Triangle(const Sphere &sphere, const Triangle &triangle, DirectX::XMVECTOR *inter = nullptr);


	///<summary>
	///���C�ƕ��ʂ̓����蔻��
	///</summary>
	/// <param name="lay">���C</param>
	/// <param name="plane">����</param>
	/// <param name="inter">�����i�o�͗p�j</param>
	///  <param name="inter">��_�i�o�͗p�j</param>
	/// <returns>�������Ă��邩�ۂ�</returns>
	static bool CheckRay2Plane(const Ray &ray, const Plane &plane, float *distance = nullptr, DirectX::XMVECTOR *inter = nullptr);


};