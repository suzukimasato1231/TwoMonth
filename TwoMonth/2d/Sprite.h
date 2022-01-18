#pragma once
#include<vector>
#include<string>
#include<d3d12.h>
#include<dxgi1_6.h>
#include<DirectXMath.h>
#include "../Pipeline/Pipeline.h"
using namespace Microsoft::WRL;
using namespace DirectX;
//�e�N�X�`���̍ő喇��
const int spriteSRVCount = 512;

extern const int window_width;
extern const int window_height;

class Sprite
{
public://�\����
	struct SpriteData
	{
		//���_�o�b�t�@�̐���
		ComPtr<ID3D12Resource> vertBuff;
		//���_�o�b�t�@�r���[�̍쐬
		D3D12_VERTEX_BUFFER_VIEW vbView;
		//Z�����̉�]�p
		float rotation = 0.0f;
		//���W
		XMFLOAT3 position = { 0,0,0 };
		//���[���h�s��
		XMMATRIX matWorld;
		//�e�N�X�`���ԍ�
		UINT texNumber = 0;
		//�傫��
		XMFLOAT2 size = { 100,100 };

		XMFLOAT2 texLeftTop = { 0,0 };

		XMFLOAT2 texSize = { 0,0 };
		//�A���J�[�|�C���g
		XMFLOAT2 anchorpoint = { 0.5f,0.5f };
		//�e�N���X
		SpriteData *parent = nullptr;
	};

	struct VertexPosUv
	{
		XMFLOAT3 pos;//xyz���W
		XMFLOAT2 uv;//uv���W
	};


	//�萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferData
	{
		XMFLOAT4 color;
		XMMATRIX mat;//3D�ϊ��s��
	};

	//�X�v���C�g���ʃf�[�^
	struct SpriteCommon
	{
		//�p�C�v���C���Z�b�g
		Pipeline::PipelineSet pipelineSet;
		////�ˉe�s��
		XMMATRIX matProjection{};
		//�e�N�X�`���p�f�X�N���v�^�q�[�v�̐���
		ComPtr<ID3D12DescriptorHeap>descHeap;
		//�e�N�X�`�����\�[�X�i�e�N�X�`���o�b�t�@�j�̔z��
		ComPtr<ID3D12Resource>texBuff[spriteSRVCount];
	};

	struct ConstBuffer
	{
		//GPU���\�[�X�̐���1
		ComPtr<ID3D12Resource> constBuff;

	};

public:
	Sprite();
	~Sprite();
public:
	static ID3D12Device *dev;
	static ID3D12GraphicsCommandList *cmdList;
	//�X�v���C�g���ʃf�[�^
	 SpriteCommon spriteCommon;
public://�ÓI�֐�
	//�X�v���C�g�ݒ�ÓI������
	static void StaticInit(ID3D12Device *dev, ID3D12GraphicsCommandList *cmdList);

	static Sprite *Sprite::Create();
	
	  void Init();

	 void SpriteAllInitialization(int widow_width, int window_height);

	//�X�v���C�g���ʃf�[�^�𐶐�
	 SpriteCommon SpriteCommonCreate(int window_width, int window_height);
public:


	//�X�v���C�g����
	SpriteData SpriteCreate(const wchar_t *filename);

	//�X�v���C�g���ʃe�N�X�`���ǂݍ���
	int SpriteCommonLoadTexture(const wchar_t *filename);

	//�X�v���C�g�P�̒��_�o�b�t�@�̓]�� �傫����ς����
	void SpriteTransferVertexBuffer(const SpriteData &sprite);

	void PreDraw();

	void CreateConstBuffer();

	//�X�v���C�g�P�̍X�V
	void Update(SpriteData &sprite, XMFLOAT2 position, float width, float height, XMFLOAT2 anchorpoint, XMFLOAT4 color, bool isFlipX, bool isFlipY);

	/// <summary>
	/// //�X�v���C�g�P�̕`��
	/// </summary>
	/// <param name="sprite">�X�v���C�g�f�[�^</param>
	/// <param name="position">���W</param>
	/// <param name="width">���̒���</param>
	/// <param name="height">�c�̒���</param>
	/// <param name="anchorpoint">�A���J�[�|�C���g</param>
	/// <param name="color">�F</param>
	/// <param name="isFlipX"></param>
	/// <param name="isFlipY"></param>
	void Draw(SpriteData &sprite, XMFLOAT2 position, float width, float height, XMFLOAT2 anchorpoint = { 0.0f,0.0f }, XMFLOAT4 color = { 1.0f,1.0f,1.0f,1.0f }, bool isFlipX = false, bool isFlipY = false);

	//�X�v���C�g���ʃO���t�B�b�N�R�}���h�̃Z�b�g
	void SpriteCommonBeginDraw();
public://�f�o�b�N�e�L�X�g
	void DebugUpdate(SpriteData &sprite);
	//�X�v���C�g�P�̕`��/�X�v���C�g�f�[�^sprite
	void DebugDraw(SpriteData &sprite);
private:
	std::vector<ConstBuffer *>constBuffer;
public:
	UINT texnumber = 0;
	UINT spriteNum = 0;
};
