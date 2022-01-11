#pragma once
#include"CollisionPrimitive.h"
#include"../2d/Sprite.h"
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

	/// <summary>
	/// �����`�ƒ����`�̓����蔻��
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