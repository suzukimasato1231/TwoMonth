#pragma once
#include<vector>
#include<string>
#include<d3dx12.h>
#include"../Pipeline/Pipeline.h"
#include"View.h"
#include<unordered_map>
#include"Light.h"
using namespace Microsoft::WRL;
using namespace DirectX;
#pragma comment(lib,"d3d12.lib")
const int constBufferNum = 256;
class Object
{
public:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	static ID3D12Device *dev;					//�f�o�C�X
	static ID3D12GraphicsCommandList *cmdList;	//�R�}���h���X�g
public://�\����
	//���_�f�[�^�\����
	struct Vertex
	{
		XMFLOAT3 pos;//xyz���W
		XMFLOAT3 normal;//�@���x�N�g��
		XMFLOAT2 uv;//uv���W
	};

	//�萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferData
	{
		XMFLOAT4 color;
		XMMATRIX mat;//3D�ϊ��s��
	};
	//�I�u�W�F�N�g�f�[�^�\����
	struct ObjectData
	{
		//���_�f�[�^
		std::vector<Vertex *> vertices;
		//�C���f�b�N�X�f�[�^
		std::vector<unsigned short *> indices;
		//���_�o�b�t�@�̐���
		ComPtr<ID3D12Resource> vertBuff = nullptr;
		//�C���f�b�N�X�o�b�t�@
		ComPtr<ID3D12Resource> indexBuff = nullptr;
		//���_�o�b�t�@�r���[�̍쐬
		D3D12_VERTEX_BUFFER_VIEW vbView{};
		//�C���f�b�N�X�o�b�t�@�r���[�̍쐬
		D3D12_INDEX_BUFFER_VIEW ibView{};
		//���[���h�s��
		XMMATRIX matWorld;
		//�I�u�W�F�ǂݍ��ݗp
		int OBJTexture = 0;
		//���_�@���X���[�W���O�p�f�[�^
		std::unordered_map<unsigned short, std::vector<unsigned short>>smoothData;
		ObjectData *parent = nullptr;
	};

	struct ConstBuffer
	{
		//GPU���\�[�X�̐���
		ComPtr<ID3D12Resource>constBuff = nullptr;
	};

	//OBJ�f�[�^�֘A
	// �萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferDataB0
	{
		//XMMATRIX mat;	// �R�c�ϊ��s��
		XMMATRIX viewproj;//�r���[�v���W�F�N�V�����s��
		XMMATRIX world;//���[���h���W
		XMFLOAT3 cameraPos;//�J�������W(���[���h���W)
	};
	struct ConstBufferDataB1
	{
		XMFLOAT3 ambient;	//�A���r�G���g�W��
		float pad1;			//�p�f�B���O
		XMFLOAT3 diffuse;	//�f�B�t���[�Y�W��
		float pad2;			//�p�f�B���O
		XMFLOAT3 specular;	//�X�y�L�����[�W��
		float alpha;		//�A���t�@
	};
	//�}�e���A��
	struct Material
	{
		std::string name;			//�}�e���A����
		XMFLOAT3 ambient;			//�A���r�G���g�e���x
		XMFLOAT3 diffuse;			//�f�B�t���[�Y�e���x
		XMFLOAT3 specular;			//�X�y�L�����[�e���x
		float alpha;				//�A���t�@
		std::string textureFilename;//�e�N�X�`���t�@�C����
		//�R���X�g���N�^
		Material()
		{
			ambient = { 0.3f,0.3f,0.3f };
			diffuse = { 0.0f,0.0f,0.0f };
			specular = { 0.0f,0.0f,0.0f };
			alpha = 1.0f;
		}
	};
	//OBJ�萔�o�b�t�@
	struct OBJData
	{
		ComPtr<ID3D12Resource> constBuffB0; // �萔�o�b�t�@
		ComPtr<ID3D12Resource> constBuffB1; // �萔�o�b�t�@
	};
	//�e�N�X�`���f�[�^
	struct TextureData
	{
		D3D12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV;
		D3D12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV;
		ComPtr<ID3D12Resource> texbuff;
	};
public://�p�C�v���C���ݒ�
	Pipeline::PipelineSet object3dPipelineSet;	//�I�u�W�F�N�g
	Pipeline::PipelineSet objPipelineSet;		//OBJ�ǂݍ���
public://�ϐ�	
	//�e�N�X�`���f�[�^�̍쐬
	std::vector <TextureData *>textureData;
	//OBJ�f�[�^
	std::vector<OBJData *> OBJdata;
	//�萔�o�b�t�@�p�̃f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap >descHeap = { nullptr };
	//�I�u�W�F�N�g�̃R���X�g�o�b�t�@
	std::vector <ConstBuffer *>objectBuffer;
	//�}�e���A��
	Material material;
public:
	Object() {};
	~Object();

	//������
	void Init(ID3D12Device *dev, ID3D12GraphicsCommandList *cmdList, View *view, Light *light);

	/// <summary>
	/// 3D�I�u�W�F�N�g����
	/// </summary>
	/// <returns></returns>
	static Object *Create();
public://�J�����N���X
	static View *view;
	//���C�g
	static Light *light;
public://�}�`���f���쐬
	/// <summary>
	/// �O�p��
	/// </summary>
	/// <param name="width">���̒���</param>
	/// <param name="height">�c�̒���</param>
	/// <returns></returns>
	ObjectData CreateTriangularPyramid(const float width, const float height);
	/// <summary>
	/// �Z�`
	/// </summary>
	/// <param name="width">���̒���</param>
	/// <param name="height">�c�̒���</param>
	/// <returns></returns>
	ObjectData CreateRect(const float width, const float height);
	/// <summary>
	/// �~
	/// </summary>
	/// <param name="r">���a</param>
	/// <param name="num">������</param>
	/// <returns></returns>
	ObjectData CreateCircle(const float r, const int num);
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="width">���̒���</param>
	/// <param name="height">�c�̒���</param>
	/// <param name="depth">�[��</param>
	/// <returns></returns>
	ObjectData CreateSquare(const float width, const float height, const float depth);
	/// <summary>
	/// �~��
	/// </summary>
	/// <param name="division">������</param>
	/// <param name="prizmHeight">����</param>
	/// <param name="radius">��ʂ̔��a</param>
	/// <returns></returns>
	ObjectData CreateCylinder(int division, int prizmHeight, int radius);
	/// <summary>
	/// OBJ�I�u�W�F�N�g�쐬
	/// </summary>
	/// <param name="filename">filename</param>
	/// <param name="smoothing"></param>
	/// <returns></returns>
	ObjectData CreateOBJ(const std::string filename, bool smoothing = false);
public://�I�u�W�F�N�g�֘A
	//���f���쐬
	void CreateModel(ObjectData &polygon);
	// �e�N�X�`���ǂݍ���
	int LoadTexture(const wchar_t *filename);
	//�萔�o�b�t�@�ݒ�
	void ConstantBuffer();
	//�I�u�W�F�N�g�̃f�[�^�X�V
	void MatWord(ObjectData &polygon, XMFLOAT3 position, XMFLOAT3 scale, XMFLOAT3 matRot, XMFLOAT4 color);
	//�I�u�W�F�N�g�`��O
	void PreDraw();
	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="polygon">�I�u�W�F�N�g�f�[�^ </param>
	/// <param name="position">���W</param>
	/// <param name="scale">�傫��</param>
	/// <param name="matRot">��]</param>
	/// <param name="color">�F</param>
	/// <param name="graph">�摜�f�[�^</param>
	void Draw(ObjectData &polygon, XMFLOAT3 position, XMFLOAT3 scale, XMFLOAT3  matRot, XMFLOAT4 color, int graph = -1);
public://OBJ�֘A
	int OBJLoadTexture(const std::string &directoryPath, const std::string &filename);
	//�}�e���A���ǂݍ���
	int LoadMaterial(const std::string &directoryPath, const std::string &filename);
	/// <summary>
	/// �G�b�W�������f�[�^�̒ǉ�
	/// </summary>
	/// <param name="indexPosition">���W�C���f�b�N�X</param>
	/// <param name="indexVertex">���_�C���f�b�N�X</param>
	void AddSmoothData(ObjectData &polygon, unsigned short indexPosition, unsigned short indexVertex);

	///<summary>
	///���������ꂽ���_�@���̌v�Z
	/// </summary>
	void CalculateSmoothedVertexNormals(ObjectData &polygon);

	/// <summary>
	/// ���_�f�[�^�̐����擾
	/// </summary>
	/// <returns>���_�f�[�^�̐�</returns>
	inline size_t GetVertexCount(ObjectData &polygon);
	//���f���쐬
	void OBJCreateModel(ObjectData &polygon);
	//�萔�o�b�t�@�ݒ�
	void OBJConstantBuffer();
	/// <summary>
	/// �I�u�W�F�N�g�̃f�[�^�X�V
	/// </summary>
	/// <param name="position">���W</param>
	/// <param name="scale">�傫��</param>
	/// <param name="matRot">��]</param>
	/// <param name="color">�F</param>
	void OBJMatWord(ObjectData &polygon, XMFLOAT3 position, XMFLOAT3 scale, XMFLOAT3 matRot, XMFLOAT4 color);
	/// <summary>
	/// OBJ�`��
	/// </summary>
	/// <param name="polygon">�I�u�W�F�N�g�f�[�^</param>
	/// <param name="position">���W</param>
	/// <param name="scale">�傫��</param>
	/// <param name="matRot">��]</param>
	/// <param name="color">�F</param>
	void OBJDraw(ObjectData &polygon, XMFLOAT3 position, XMFLOAT3 scale, XMFLOAT3 matRot, XMFLOAT4 color = { 1,1,1,1 });
public:
	size_t OBJNum = 0;//OBJ�ǂݍ��݂̐�
	size_t objNum = 0;//�I�u�W�F�N�g�̐�
	size_t texNum = 0;//�e�N�X�`���̐�
};