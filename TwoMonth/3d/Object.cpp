#include "Object.h"
#include <DirectXTex.h>
#include<fstream>
#include<sstream>
#include<string>

using namespace DirectX;
using namespace Microsoft::WRL;
using namespace std;

ID3D12Device *Object::dev = nullptr;
ID3D12GraphicsCommandList *Object::cmdList = nullptr;
View *Object::view = nullptr;
Light *Object::light = nullptr;
Object::~Object()
{
	//OBJ�f�[�^�폜
	for (int i = (int)OBJdata.size() - 1; i >= 0; i--)
	{
		delete OBJdata[i];
		OBJdata.erase(OBJdata.begin() + i);
	}

	for (int i = (int)objectBuffer.size() - 1; i >= 0; i--)
	{
		delete objectBuffer[i];
		objectBuffer.erase(objectBuffer.begin() + i);
	}

	for (int i = (int)textureData.size() - 1; i >= 0; i--)
	{
		delete textureData[i];
		textureData.erase(textureData.begin() + i);
	}

}

void  Object::Init(ID3D12Device *dev, ID3D12GraphicsCommandList *cmdList, View *view, Light *light)
{
	Object::dev = dev;

	Object::cmdList = cmdList;

	Object::view = view;

	Object::light = light;

	//�p�C�v���C������
	object3dPipelineSet = Pipeline::Object3dCreateGraphicsPipeline(Object::dev);

	objPipelineSet = Pipeline::OBJCreateGraphicsPipeline(Object::dev);
}

Object *Object::Create()
{
	// 3D�I�u�W�F�N�g�̃C���X�^���X�𐶐�
	Object *object = new Object();
	if (object == nullptr) {
		return nullptr;
	}

	// ������
	return object;
}

void Object::AddSmoothData(ObjectData &polygon, unsigned short indexPosition, unsigned short indexVertex)
{
	polygon.smoothData[indexPosition].emplace_back(indexVertex);
}

void Object::CalculateSmoothedVertexNormals(ObjectData &polygon)
{
	auto itr = polygon.smoothData.begin();
	for (; itr != polygon.smoothData.end(); ++itr)
	{
		//�e�ʗp�̋��ʒ��_�R���N�V����
		std::vector<unsigned short> &v = itr->second;
		//�S���_�̖@���𕽋ς���
		XMVECTOR normal = {};
		for (unsigned short index : v)
		{
			normal += XMVectorSet(polygon.vertices[index]->normal.x, polygon.vertices[index]->normal.y, polygon.vertices[index]->normal.z, 0);
		}
		normal = XMVector3Normalize(normal / (float)v.size());
		//���ʖ@�����g�p����S�Ă̒��_�f�[�^�ɏ�������
		for (unsigned short index : v)
		{
			polygon.vertices[index]->normal = { normal.m128_f32[0],normal.m128_f32[1],normal.m128_f32[2] };
		}
	}
}

inline size_t Object::GetVertexCount(ObjectData &polygon)
{
	return polygon.vertices.size();
}

int  Object::LoadTexture(const wchar_t *filename)
{
	HRESULT result = S_FALSE;

	textureData.push_back(new Object::TextureData);

	if (texNum == 0)
	{
		//�ݒ�\����
		D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc{};
		descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
		descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;//�V�F�[�_�[���猩����
		descHeapDesc.NumDescriptors = constBufferNum;//�萔�o�b�t�@�̐�
		//�f�X�N���v�^�q�[�v�̐���
		result = dev->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(&descHeap));
	}


	TexMetadata metadata{};
	ScratchImage scratchImg{};
	//WIC�e�N�X�`���̃��[�h
	result = LoadFromWICFile(
		filename,
		WIC_FLAGS_NONE,
		&metadata, scratchImg);

	const Image *img = scratchImg.GetImage(0, 0, 0);//���f�[�^���o

	//���\�[�X�ݒ�
	CD3DX12_RESOURCE_DESC texresDesc = CD3DX12_RESOURCE_DESC::Tex2D(
		metadata.format,
		metadata.width,
		(UINT)metadata.height,
		(UINT16)metadata.arraySize,
		(UINT16)metadata.mipLevels);

	//�e�N�X�`���p�o�b�t�@�̐���
	result = dev->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK, D3D12_MEMORY_POOL_L0),
		D3D12_HEAP_FLAG_NONE,
		&texresDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,//�e�N�X�`���p�w��
		nullptr,
		IID_PPV_ARGS(&textureData[texNum]->texbuff));

	//�e�N�X�`���o�b�t�@�Ƀf�[�^�]��
	result = textureData[texNum]->texbuff->WriteToSubresource(
		0,
		nullptr,//�S�̈�փR�s�[
		img->pixels,//���f�[�^�A�h���X
		(UINT)img->rowPitch,//1���C���T�C�Y
		(UINT)img->slicePitch//�S�T�C�Y
	);

	//�f�X�N���v�^�q�[�v�̐擪�n���h�����擾
	textureData[texNum]->cpuDescHandleSRV = descHeap->GetCPUDescriptorHandleForHeapStart();
	//�n���h���̃A�h���X��i�߂�
	textureData[texNum]->cpuDescHandleSRV.ptr += texNum * dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	D3D12_GPU_DESCRIPTOR_HANDLE gpuDescHandleStart = descHeap->GetGPUDescriptorHandleForHeapStart();
	UINT descHandleIncrementSize = dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	//1��SRV
	textureData[texNum]->gpuDescHandleSRV = gpuDescHandleStart;
	textureData[texNum]->gpuDescHandleSRV.ptr += descHandleIncrementSize * texNum;

	//�V�F�[�_���\�[�X�r���[�ݒ�
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};//�ݒ�\����
	srvDesc.Format = metadata.format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;//�QD�e�N�X�`��
	srvDesc.Texture2D.MipLevels = 1;

	//�q�[�v�̂Q�ԖڂɃV�F�[�_�[���\�[�X�r���[���쐬
	dev->CreateShaderResourceView(textureData[texNum]->texbuff.Get(),//�r���[�Ɗ֘A�t����o�b�t�@
		&srvDesc,//�e�N�X�`���ݒ�\��
		textureData[texNum]->cpuDescHandleSRV
	);
	texNum++;
	return (int)texNum - 1;
}

void Object::CreateModel(Object::ObjectData &polygon)
{
	HRESULT result = S_FALSE;
	for (size_t i = 0; i < polygon.indices.size() / 3; i++)
	{//�O�p�`1���ƂɌv�Z���Ă���
		//�O�p�`�̃C���f�b�N�X�����o���āA�ꎞ�I�ȕϐ��ɓ����
		unsigned short indices0 = *polygon.indices[i * 3 + 0];
		unsigned short indices1 = *polygon.indices[i * 3 + 1];
		unsigned short indices2 = *polygon.indices[i * 3 + 2];
		//�O�p�`���\�����钸�_���W���x�N�g���ɑ��
		XMVECTOR p0 = XMLoadFloat3(&polygon.vertices[indices0]->pos);
		XMVECTOR p1 = XMLoadFloat3(&polygon.vertices[indices1]->pos);
		XMVECTOR p2 = XMLoadFloat3(&polygon.vertices[indices2]->pos);
		//p0��p1�x�N�g���Ap0��p2�x�N�g�����v�Z�i�x�N�g���̌��Z�j
		XMVECTOR v1 = XMVectorSubtract(p1, p0);
		XMVECTOR v2 = XMVectorSubtract(p2, p0);

		//�O�ς͗������琂���ȃx�N�g��
		XMVECTOR normal = XMVector3Cross(v1, v2);
		//���K���i�������P�ɂ���j
		normal = XMVector3Normalize(normal);
		//���߂��@���𒸓_�f�[�^�ɑ��
		XMStoreFloat3(&polygon.vertices[indices0]->normal, normal);
		XMStoreFloat3(&polygon.vertices[indices1]->normal, normal);
		XMStoreFloat3(&polygon.vertices[indices2]->normal, normal);
	}

	//���_�f�[�^�S�̂̃T�C�Y�����_�f�[�^����̃T�C�Y�����_�f�[�^�̗v�f��
	UINT sizeVB = static_cast<UINT>(sizeof(Vertex) * polygon.vertices.size());

	//�C���f�b�N�X�f�[�^�S�̂̃T�C�Y
	UINT sizeIB = static_cast<UINT>(sizeof(unsigned short) * polygon.indices.size());

	////���_�o�b�t�@�̐���
	result = dev->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),//�A�b�v���[�h�\
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(sizeVB),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&polygon.vertBuff)
	);

	////�C���f�b�N�X�o�b�t�@�̐���
	result = dev->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),//�A�b�v���[�h�\
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(sizeIB),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&polygon.indexBuff));

	Vertex *vertMap = nullptr;
	//GPU��̃o�b�t�@�ɑΉ��������z���������擾
	result = polygon.vertBuff->Map(0, nullptr, (void **)&vertMap);

	//�S���_�ɑ΂���
	for (size_t i = 0; i < polygon.vertices.size(); i++)
	{
		vertMap[i] = *polygon.vertices[i];//���W�R�s�[
	}

	//�}�b�v������
	polygon.vertBuff->Unmap(0, nullptr);

	//GPU��̃o�b�t�@�ɑΉ��������z���������擾
	unsigned short *indexMap = nullptr;
	result = polygon.indexBuff->Map(0, nullptr, (void **)&indexMap);

	//�S�C���f�b�N�X�ɑ΂���
	for (size_t i = 0; i < polygon.indices.size(); i++)
	{
		indexMap[i] = *polygon.indices[i];//�C���f�b�N�X���R�s�[
	}
	//�q���������
	polygon.indexBuff->Unmap(0, nullptr);

	//���_�o�b�t�@�r���[�̍쐬
	polygon.vbView.BufferLocation =
		polygon.vertBuff->GetGPUVirtualAddress();
	polygon.vbView.SizeInBytes = sizeVB;
	polygon.vbView.StrideInBytes = sizeof(Vertex);

	//�C���f�b�N�X�o�b�t�@�r���[�̍쐬
	polygon.ibView.BufferLocation = polygon.indexBuff->GetGPUVirtualAddress();
	polygon.ibView.Format = DXGI_FORMAT_R16_UINT;
	polygon.ibView.SizeInBytes = sizeIB;
}

void  Object::ConstantBuffer()
{
	HRESULT result;
	Object::objectBuffer.push_back(new Object::ConstBuffer);
	//�萔�o�b�t�@�̐���
	result = dev->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),//�A�b�v���[�h�\
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferData) + 0xff) & ~0xff),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&Object::objectBuffer[objNum]->constBuff)
	);
}


void  Object::MatWord(ObjectData &polygon, XMFLOAT3 position, XMFLOAT3 scale, XMFLOAT3 rotation, XMFLOAT4 color)
{
	HRESULT result;
	//���[���h�ϊ��F//�X�P�[�����O
	XMMATRIX matScale;//�X�P�[�����O�s��
	//���[���h�ϊ��F//��]
	XMMATRIX matRot;//��]�s��
	//���[���h�ϊ��F//���s�ړ�
	XMMATRIX matTrains;//���s�ړ��s��
	//���[���h�ϊ�
	matScale = XMMatrixScaling(scale.x, scale.y, scale.z);//�傫��
	matTrains = XMMatrixTranslation(position.x, position.y, position.z);//���s�ړ��s����Čv�Z
	matRot = XMMatrixIdentity();
	matRot *= XMMatrixRotationZ(XMConvertToRadians(rotation.z));//Z���܂��ɂS�T�x��]
	matRot *= XMMatrixRotationX(XMConvertToRadians(rotation.x));//X���܂��ɂS�T�x��]
	matRot *= XMMatrixRotationY(XMConvertToRadians(rotation.y));//Y���܂��ɂS�T�x��]

	polygon.matWorld = XMMatrixIdentity();//���[���h�s��͖��t���[�����Z�b�g
	polygon.matWorld *= matScale;//���[���h�s��ɃX�P�[�����O�𔽉f
	polygon.matWorld *= matRot;//���[���h�s��ɉ�]�𔽉f
	polygon.matWorld *= matTrains;//���[���h�s��ɕύX�ړ��𔽉f

	ConstBufferData *constMap = nullptr;
	//GPU��̃o�b�t�@�ɑΉ��������z���������擾
	result = Object::objectBuffer[objNum]->constBuff->Map(0, nullptr, (void **)&constMap);
	//�s��̍���   ���[���h�ϊ��s�� �� �r���[�ϊ��s�� �� �ˉe�ϊ��s��
	if (polygon.parent == nullptr)
	{
		constMap->mat = polygon.matWorld * view->GetMatView() * view->GetProjection();
	}
	else
	{
		constMap->mat = polygon.matWorld * polygon.parent->matWorld * view->GetMatView() * view->GetProjection();
	}
	constMap->color = color;
	Object::objectBuffer[objNum]->constBuff->Unmap(0, nullptr);
}


void  Object::OBJMatWord(ObjectData &polygon, XMFLOAT3 position, XMFLOAT3 scale, XMFLOAT3 rotation, XMFLOAT4 color)
{
	HRESULT result;
	//���[���h�ϊ��F//�X�P�[�����O
	XMMATRIX matScale;//�X�P�[�����O�s��
	//���[���h�ϊ��F//��]
	XMMATRIX matRot;//��]�s��
	//���[���h�ϊ��F//���s�ړ�
	XMMATRIX matTrains;//���s�ړ��s��
	//���[���h�ϊ�
	matScale = XMMatrixScaling(scale.x, scale.y, scale.z);//�傫��
	matTrains = XMMatrixTranslation(position.x, position.y, position.z);//���s�ړ��s����Čv�Z
	matRot = XMMatrixIdentity();
	matRot *= XMMatrixRotationZ(XMConvertToRadians(rotation.z));//Z���܂��ɂS�T�x��]
	matRot *= XMMatrixRotationX(XMConvertToRadians(rotation.x));//X���܂��ɂS�T�x��]
	matRot *= XMMatrixRotationY(XMConvertToRadians(rotation.y));//Y���܂��ɂS�T�x��]

	polygon.matWorld = XMMatrixIdentity();//���[���h�s��͖��t���[�����Z�b�g
	polygon.matWorld *= matScale;//���[���h�s��ɃX�P�[�����O�𔽉f
	polygon.matWorld *= matRot;//���[���h�s��ɉ�]�𔽉f
	polygon.matWorld *= matTrains;//���[���h�s��ɕύX�ړ��𔽉f

	const XMMATRIX &matViewProjection = view->GetMatView() * view->GetProjection();
	const XMFLOAT3 &cameraPos = view->GetEye();
	//GPU��̃o�b�t�@�ɑΉ��������z���������擾
	ConstBufferDataB0 *constMap = nullptr;
	result = Object::OBJdata[OBJNum]->constBuffB0->Map(0, nullptr, (void **)&constMap);


	//�s��̍���   ���[���h�ϊ��s�� �� �r���[�ϊ��s�� �� �ˉe�ϊ��s��
	constMap->viewproj = matViewProjection;
	if (polygon.parent == nullptr)
	{
		constMap->world = polygon.matWorld * view->GetMatView() * view->GetProjection();
	}
	else
	{
		constMap->world = polygon.matWorld * polygon.parent->matWorld * view->GetMatView() * view->GetProjection();
	}
	constMap->cameraPos = cameraPos;
	Object::OBJdata[OBJNum]->constBuffB0->Unmap(0, nullptr);


	//�萔�o�b�t�@�փf�[�^�]��
	ConstBufferDataB1 *constMap1 = nullptr;
	result = Object::OBJdata[OBJNum]->constBuffB1->Map(0, nullptr, (void **)&constMap1);
	constMap1->ambient = material.ambient;
	constMap1->diffuse = material.diffuse;
	constMap1->specular = material.specular;
	constMap1->alpha = material.alpha;
	Object::OBJdata[OBJNum]->constBuffB1->Unmap(0, nullptr);

}

void Object::PreDraw()
{
	objNum = 0;
	OBJNum = 0;
}

void Object::OBJConstantBuffer()
{
	HRESULT result;
	Object::OBJdata.push_back(new Object::OBJData);
	// �萔�o�b�t�@�̐���
	result = dev->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), 	// �A�b�v���[�h�\
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferDataB0) + 0xff) & ~0xff),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&Object::OBJdata[Object::OBJdata.size() - 1]->constBuffB0));

	// �萔�o�b�t�@�̐���
	result = dev->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), 	// �A�b�v���[�h�\
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferDataB1) + 0xff) & ~0xff),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&Object::OBJdata[Object::OBJdata.size() - 1]->constBuffB1));
}

void  Object::Draw(Object::ObjectData &polygon, XMFLOAT3 position, XMFLOAT3 scale, XMFLOAT3 matRot, XMFLOAT4 color, int graph)
{
	//�v���~�e�B�u�`��̐ݒ�R�}���h�i�O�p�`���X�g�j
	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//�f�X�N���v�^�q�[�v���Z�b�g
	ID3D12DescriptorHeap *ppHeaps[] = { descHeap.Get() };
	cmdList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
	if (objNum >= objectBuffer.size())
	{
		//�萔�o�b�t�@
		ConstantBuffer();
	}
	//�X�V
	MatWord(polygon, position, scale, matRot, color);

	cmdList->SetPipelineState(object3dPipelineSet.pipelinestate.Get());
	cmdList->SetGraphicsRootSignature(object3dPipelineSet.rootsignature.Get());

	//���_�o�b�t�@�̐ݒ�R�}���h
	cmdList->IASetVertexBuffers(0, 1, &polygon.vbView);

	////�C���f�b�N�X�o�b�t�@�r���[�̃Z�b�g�R�}���h
	cmdList->IASetIndexBuffer(&polygon.ibView);

	//�q�[�v�̐擪�ɂ���CBV�����[�g�p�����[�^�O�Ԃɐݒ�
	cmdList->SetGraphicsRootConstantBufferView(0, Object::objectBuffer[objNum]->constBuff->GetGPUVirtualAddress());

	if (graph >= 0)
	{
		//�q�[�v�̂Q�Ԗڂɂ���SRV�����[�g�p�����[�^�P�Ԃɐݒ�
		cmdList->SetGraphicsRootDescriptorTable(1, textureData[graph]->gpuDescHandleSRV);
	}
	//�`��R�}���h          //���_��				//�C���X�^���X��	//�J�n���_�ԍ�		//�C���X�^���X���Ƃ̉��Z�ԍ�
	cmdList->DrawIndexedInstanced(polygon.indices.size(), 1, 0, 0, 0);

	objNum++;
}

void Object::OBJDraw(ObjectData &polygon, XMFLOAT3 position, XMFLOAT3 scale, XMFLOAT3 rotation, XMFLOAT4 color)
{
	//�v���~�e�B�u�`��̐ݒ�R�}���h�i�O�p�`���X�g�j
	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//�f�X�N���v�^�q�[�v���Z�b�g
	ID3D12DescriptorHeap *ppHeaps[] = { descHeap.Get() };
	cmdList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
	if (OBJNum >= Object::OBJdata.size())
	{
		//�萔�o�b�t�@
		OBJConstantBuffer();
	}
	//�X�V
	OBJMatWord(polygon, position, scale, rotation, color);

	cmdList->SetPipelineState(objPipelineSet.pipelinestate.Get());
	cmdList->SetGraphicsRootSignature(objPipelineSet.rootsignature.Get());

	//���_�o�b�t�@�̐ݒ�R�}���h
	cmdList->IASetVertexBuffers(0, 1, &polygon.vbView);

	////�C���f�b�N�X�o�b�t�@�r���[�̃Z�b�g�R�}���h
	cmdList->IASetIndexBuffer(&polygon.ibView);

	//�q�[�v�̐擪�ɂ���CBV�����[�g�p�����[�^�O�Ԃɐݒ�
	cmdList->SetGraphicsRootConstantBufferView(0, Object::OBJdata[OBJNum]->constBuffB0->GetGPUVirtualAddress());
	cmdList->SetGraphicsRootConstantBufferView(1, Object::OBJdata[OBJNum]->constBuffB1->GetGPUVirtualAddress());
	//�q�[�v�̂Q�Ԗڂɂ���SRV�����[�g�p�����[�^�P�Ԃɐݒ�
	cmdList->SetGraphicsRootDescriptorTable(2, textureData[polygon.OBJTexture]->gpuDescHandleSRV);
	//���C�g�̕`��
	light->Draw(cmdList, 3);
	//�`��R�}���h          //���_��				//�C���X�^���X��	//�J�n���_�ԍ�		//�C���X�^���X���Ƃ̉��Z�ԍ�
	cmdList->DrawIndexedInstanced((UINT)polygon.indices.size(), 1, 0, 0, 0);
	OBJNum++;
}


int Object::LoadMaterial(const std::string &directoryPath, const std::string &filename)
{
	int texNumber = 0;
	//�t�@�C���X�g���[��
	std::ifstream file;
	//�}�e���A���t�@�C�����J��
	file.open(directoryPath + filename);
	//�t�@�C���I�[�v�����s���`�F�b�N
	if (file.fail())
	{
		assert(0);
	}
	//1�s���ǂݍ���
	string line;
	while (getline(file, line))
	{
		//1�s���̕�������X�g���[���ɕϊ�
		std::istringstream line_stream(line);
		//���p�X�y�[�X��؂�ōs�̐擪��������擾
		string key;
		getline(line_stream, key, ' ');
		//�擪�̃^�u�����͖�������
		if (key[0] == '\t')
		{
			key.erase(key.begin());//�擪�̕������폜
		}
		//�擪������newmtl�Ȃ�}�e���A����
		if (key == "newmtl")
		{
			//�}�e���A�����ǂݍ���
			line_stream >> material.name;
		}
		//�擪������Ka�Ȃ�A���r�G���g�F
		if (key == "Ka")
		{
			line_stream >> material.ambient.x;
			line_stream >> material.ambient.y;
			line_stream >> material.ambient.z;
		}
		//�擪������Kd�Ȃ�f�B�t���[�Y�F
		if (key == "Kd")
		{
			line_stream >> material.diffuse.x;
			line_stream >> material.diffuse.y;
			line_stream >> material.diffuse.z;
		}
		//�擪������Ks�Ȃ�X�y�L�����[�F
		if (key == "Ks")
		{
			line_stream >> material.specular.x;
			line_stream >> material.specular.y;
			line_stream >> material.specular.z;
		}
		//�擪������map_Kd�Ȃ�e�N�X�`����
		if (key == "map_Kd")
		{
			//�e�N�X�`���̃t�@�C�����ǂݍ���
			line_stream >> material.textureFilename;
			//�e�N�X�`���ǂݍ���
			texNumber = OBJLoadTexture(directoryPath, material.textureFilename);
		}
	}
	//�t�@�C�������
	file.close();
	return  texNumber;
}

void Object::OBJCreateModel(ObjectData &polygon)
{
	HRESULT result;
	//���_�f�[�^�S�̂̃T�C�Y�����_�f�[�^����̃T�C�Y�����_�f�[�^�̗v�f��
	UINT sizeVB = static_cast<UINT>(sizeof(Vertex) * polygon.vertices.size());

	//�C���f�b�N�X�f�[�^�S�̂̃T�C�Y
	UINT sizeIB = static_cast<UINT>(sizeof(unsigned short) * polygon.indices.size());

	////���_�o�b�t�@�̐���
	result = dev->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),//�A�b�v���[�h�\
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(sizeVB),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&polygon.vertBuff)
	);

	////�C���f�b�N�X�o�b�t�@�̐���
	result = dev->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),//�A�b�v���[�h�\
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(sizeIB),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&polygon.indexBuff));

	Vertex *vertMap = nullptr;
	//GPU��̃o�b�t�@�ɑΉ��������z���������擾
	result = polygon.vertBuff->Map(0, nullptr, (void **)&vertMap);

	//�S���_�ɑ΂���
	for (size_t i = 0; i < polygon.vertices.size(); i++)
	{
		vertMap[i] = *polygon.vertices[i];//���W�R�s�[
	}

	//�}�b�v������
	polygon.vertBuff->Unmap(0, nullptr);

	//GPU��̃o�b�t�@�ɑΉ��������z���������擾
	unsigned short *indexMap = nullptr;
	result = polygon.indexBuff->Map(0, nullptr, (void **)&indexMap);

	//�S�C���f�b�N�X�ɑ΂���
	for (size_t i = 0; i < polygon.indices.size(); i++)
	{
		indexMap[i] = *polygon.indices[i];//�C���f�b�N�X���R�s�[
	}
	//�q���������
	polygon.indexBuff->Unmap(0, nullptr);

	//���_�o�b�t�@�r���[�̍쐬
	polygon.vbView.BufferLocation =
		polygon.vertBuff->GetGPUVirtualAddress();
	polygon.vbView.SizeInBytes = sizeVB;
	polygon.vbView.StrideInBytes = sizeof(Vertex);

	//�C���f�b�N�X�o�b�t�@�r���[�̍쐬
	polygon.ibView.BufferLocation = polygon.indexBuff->GetGPUVirtualAddress();
	polygon.ibView.Format = DXGI_FORMAT_R16_UINT;
	polygon.ibView.SizeInBytes = sizeIB;
}

int Object::OBJLoadTexture(const std::string &directoryPath, const std::string &filename)
{
	HRESULT result = S_FALSE;
	textureData.push_back(new Object::TextureData);
	if (texNum == 0)
	{
		//�ݒ�\����
		D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc{};
		descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
		descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;//�V�F�[�_�[���猩����
		descHeapDesc.NumDescriptors = constBufferNum;//�萔�o�b�t�@�̐�
		//�f�X�N���v�^�q�[�v�̐���
		result = dev->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(&descHeap));
	}
	// WIC�e�N�X�`���̃��[�h
	TexMetadata metadata{};
	ScratchImage scratchImg{};

	//�t�@�C���p�X������
	string filepath = directoryPath + filename;

	//���j�R�[�h������ɕϊ�����
	wchar_t wfilepath[128];
	int iBufferSize = MultiByteToWideChar(CP_ACP, 0, filepath.c_str(), -1, wfilepath, _countof(wfilepath));

	result = LoadFromWICFile(
		wfilepath, WIC_FLAGS_NONE,
		&metadata, scratchImg
	);
	if (FAILED(result)) {
		return result;
	}
	const Image *img = scratchImg.GetImage(0, 0, 0); // ���f�[�^���o

	// ���\�[�X�ݒ�
	CD3DX12_RESOURCE_DESC texresDesc = CD3DX12_RESOURCE_DESC::Tex2D(
		metadata.format,
		metadata.width,
		(UINT)metadata.height,
		(UINT16)metadata.arraySize,
		(UINT16)metadata.mipLevels
	);
	// �e�N�X�`���p�o�b�t�@�̐���
	result = dev->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK, D3D12_MEMORY_POOL_L0),
		D3D12_HEAP_FLAG_NONE,
		&texresDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ, // �e�N�X�`���p�w��
		nullptr,
		IID_PPV_ARGS(&textureData[texNum]->texbuff));
	if (FAILED(result)) {
		return result;
	}
	// �e�N�X�`���o�b�t�@�Ƀf�[�^�]��
	result = textureData[texNum]->texbuff->WriteToSubresource(
		0,
		nullptr, // �S�̈�փR�s�[
		img->pixels,    // ���f�[�^�A�h���X
		(UINT)img->rowPitch,  // 1���C���T�C�Y
		(UINT)img->slicePitch // 1���T�C�Y
	);
	if (FAILED(result)) {
		return result;
	}
	UINT descHandleIncrementSize = dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	// �V�F�[�_���\�[�X�r���[�쐬
	textureData[texNum]->cpuDescHandleSRV = CD3DX12_CPU_DESCRIPTOR_HANDLE(descHeap->GetCPUDescriptorHandleForHeapStart(), 0, descHandleIncrementSize);
	//�n���h���̃A�h���X��i�߂�
	textureData[texNum]->cpuDescHandleSRV.ptr += texNum * descHandleIncrementSize;
	textureData[texNum]->gpuDescHandleSRV = CD3DX12_GPU_DESCRIPTOR_HANDLE(descHeap->GetGPUDescriptorHandleForHeapStart(), 0, descHandleIncrementSize);
	textureData[texNum]->gpuDescHandleSRV.ptr += descHandleIncrementSize * texNum;

	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{}; // �ݒ�\����
	D3D12_RESOURCE_DESC resDesc = textureData[texNum]->texbuff->GetDesc();

	srvDesc.Format = resDesc.Format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;//2D�e�N�X�`��
	srvDesc.Texture2D.MipLevels = 1;

	dev->CreateShaderResourceView(textureData[texNum]->texbuff.Get(), //�r���[�Ɗ֘A�t����o�b�t�@
		&srvDesc, //�e�N�X�`���ݒ���
		textureData[texNum]->cpuDescHandleSRV
	);
	texNum++;
	return (int)texNum - 1;
}



Object::ObjectData  Object::CreateTriangularPyramid(const float width, const float height)
{
	Object::ObjectData polygon;
	const int DIV = 3;
	//�O�p��
	for (int i = 0; i < DIV; i++)
	{
		polygon.vertices.push_back(new Vertex);
		polygon.vertices[polygon.vertices.size() - 1]->pos = { width * sinf(2 * XM_PI / DIV * i) ,width * cosf(2 * XM_PI / DIV * i),0 };
	}
	polygon.vertices.push_back(new Vertex);
	polygon.vertices[polygon.vertices.size() - 1]->pos = { 0,0,0 };
	polygon.vertices.push_back(new Vertex);
	polygon.vertices[polygon.vertices.size() - 1]->pos = { 0,0,-height };

	for (int i = 0; i < polygon.vertices.size(); i++)
	{
		polygon.vertices[i]->normal = {};

	}
	polygon.vertices[0]->uv = { 0.0f,0.0f }, polygon.vertices[1]->uv = { 1.0f,0.0f };
	polygon.vertices[2]->uv = { 0.0f,1.0f }, polygon.vertices[3]->uv = { 1.0f,1.0f };
	polygon.vertices[4]->uv = { 1.0f,1.0f };
	//�C���f�b�N�X
	//���
	polygon.indices.push_back(new unsigned short(1)), polygon.indices.push_back(new unsigned short(0)), polygon.indices.push_back(new unsigned short(3));
	polygon.indices.push_back(new unsigned short(2)), polygon.indices.push_back(new unsigned short(1)), polygon.indices.push_back(new unsigned short(3));
	polygon.indices.push_back(new unsigned short(0)), polygon.indices.push_back(new unsigned short(2)), polygon.indices.push_back(new unsigned short(3));
	//����
	polygon.indices.push_back(new unsigned short(0)), polygon.indices.push_back(new unsigned short(1)), polygon.indices.push_back(new unsigned short(4));
	polygon.indices.push_back(new unsigned short(1)), polygon.indices.push_back(new unsigned short(2)), polygon.indices.push_back(new unsigned short(4));
	polygon.indices.push_back(new unsigned short(2)), polygon.indices.push_back(new unsigned short(0)), polygon.indices.push_back(new unsigned short(4));

	CreateModel(polygon);

	return polygon;
}

Object::ObjectData  Object::CreateRect(const float width, const float height)
{
	Object::ObjectData polygon;
	polygon.vertices.push_back(new Vertex);
	polygon.vertices[polygon.vertices.size() - 1]->pos = { -width / 2, -height / 2, 0.0f };
	polygon.vertices[polygon.vertices.size() - 1]->uv = { 0.0f,1.0f };

	polygon.vertices.push_back(new Vertex);
	polygon.vertices[polygon.vertices.size() - 1]->pos = { -width / 2, height / 2, 0.0f };
	polygon.vertices[polygon.vertices.size() - 1]->uv = { 0.0f,0.0f };

	polygon.vertices.push_back(new Vertex);
	polygon.vertices[polygon.vertices.size() - 1]->pos = { width / 2, -height / 2,  0.0f };
	polygon.vertices[polygon.vertices.size() - 1]->uv = { 1.0f,1.0f };

	polygon.vertices.push_back(new Vertex);
	polygon.vertices[polygon.vertices.size() - 1]->pos = { width / 2, height / 2, 0.0f };
	polygon.vertices[polygon.vertices.size() - 1]->uv = { 1.0f,0.0f };


	for (int i = 0; i < polygon.vertices.size(); i++)
	{
		polygon.vertices[i]->normal = {};
	}

	polygon.indices.push_back(new unsigned short(0)), polygon.indices.push_back(new unsigned short(1)), polygon.indices.push_back(new unsigned short(2));

	polygon.indices.push_back(new unsigned short(2)), polygon.indices.push_back(new unsigned short(1)), polygon.indices.push_back(new unsigned short(3));

	CreateModel(polygon);

	return polygon;
}

Object::ObjectData Object::CreateCircle(const float r, const int num)
{
	Object::ObjectData polygon;
	for (int i = 0; i < num; i++)
	{
		polygon.vertices.push_back(new Vertex);
		polygon.vertices[polygon.vertices.size() - 1]->pos.x = r * sinf(6.28f / num * i);
		polygon.vertices[polygon.vertices.size() - 1]->pos.y = r * cosf(6.28f / num * i);
		polygon.vertices[polygon.vertices.size() - 1]->pos.z = 0;
		polygon.vertices[polygon.vertices.size() - 1]->uv = { 0,0 };
	}

	polygon.vertices.push_back(new Vertex);
	polygon.vertices[polygon.vertices.size() - 1]->pos = { 0,0,0 };

	for (int i = 0; i < num; i++)
	{
		polygon.indices.push_back(new unsigned short(i));
		polygon.indices.push_back(new unsigned short(i + 1));
		polygon.indices.push_back(new unsigned short(num));
	}
	*polygon.indices[polygon.indices.size() - 2] = 0;

	CreateModel(polygon);

	return polygon;
}

Object::ObjectData Object::CreateSquare(const float width, const float height, const float depth)
{
	Object::ObjectData polygon;
	//�O
	polygon.vertices.push_back(new Vertex);
	polygon.vertices[polygon.vertices.size() - 1]->pos = { -width / 2,-height / 2,-depth / 2 };
	polygon.vertices[polygon.vertices.size() - 1]->uv = { 0.0f,1.0f };

	polygon.vertices.push_back(new Vertex);
	polygon.vertices[polygon.vertices.size() - 1]->pos = { -width / 2,height / 2,-depth / 2 };
	polygon.vertices[polygon.vertices.size() - 1]->uv = { 0.0f,0.0f };

	polygon.vertices.push_back(new Vertex);
	polygon.vertices[polygon.vertices.size() - 1]->pos = { width / 2,-height / 2,-depth / 2 };
	polygon.vertices[polygon.vertices.size() - 1]->uv = { 1.0f,1.0f };

	polygon.vertices.push_back(new Vertex);
	polygon.vertices[polygon.vertices.size() - 1]->pos = { width / 2,height / 2,-depth / 2 };
	polygon.vertices[polygon.vertices.size() - 1]->uv = { 1.0f,0.0f };

	//���
	polygon.vertices.push_back(new Vertex);
	polygon.vertices[polygon.vertices.size() - 1]->pos = { -width / 2,-height / 2,depth / 2 };
	polygon.vertices[polygon.vertices.size() - 1]->uv = { 0.0f,1.0f };

	polygon.vertices.push_back(new Vertex);
	polygon.vertices[polygon.vertices.size() - 1]->pos = { -width / 2,height / 2,depth / 2 };
	polygon.vertices[polygon.vertices.size() - 1]->uv = { 0.0f,0.0f };

	polygon.vertices.push_back(new Vertex);
	polygon.vertices[polygon.vertices.size() - 1]->pos = { width / 2,-height / 2,depth / 2 };
	polygon.vertices[polygon.vertices.size() - 1]->uv = { 1.0f,1.0f };

	polygon.vertices.push_back(new Vertex);
	polygon.vertices[polygon.vertices.size() - 1]->pos = { width / 2,height / 2,depth / 2 };
	polygon.vertices[polygon.vertices.size() - 1]->uv = { 1.0f,0.0f };

	//��
	polygon.vertices.push_back(new Vertex);
	polygon.vertices[polygon.vertices.size() - 1]->pos = { -width / 2,-height / 2,-depth / 2 };
	polygon.vertices[polygon.vertices.size() - 1]->uv = { 0.0f,1.0f };

	polygon.vertices.push_back(new Vertex);
	polygon.vertices[polygon.vertices.size() - 1]->pos = { -width / 2,-height / 2,depth / 2 };
	polygon.vertices[polygon.vertices.size() - 1]->uv = { 0.0f,0.0f };

	polygon.vertices.push_back(new Vertex);
	polygon.vertices[polygon.vertices.size() - 1]->pos = { -width / 2,height / 2,-depth / 2 };
	polygon.vertices[polygon.vertices.size() - 1]->uv = { 1.0f,1.0f };

	polygon.vertices.push_back(new Vertex);
	polygon.vertices[polygon.vertices.size() - 1]->pos = { -width / 2,height / 2,depth / 2 };
	polygon.vertices[polygon.vertices.size() - 1]->uv = { 1.0f,0.0f };


	//�E
	polygon.vertices.push_back(new Vertex);
	polygon.vertices[polygon.vertices.size() - 1]->pos = { width / 2,-height / 2,-depth / 2 };
	polygon.vertices[polygon.vertices.size() - 1]->uv = { 0.0f,1.0f };

	polygon.vertices.push_back(new Vertex);
	polygon.vertices[polygon.vertices.size() - 1]->pos = { width / 2,-height / 2,depth / 2 };
	polygon.vertices[polygon.vertices.size() - 1]->uv = { 0.0f,0.0f };

	polygon.vertices.push_back(new Vertex);
	polygon.vertices[polygon.vertices.size() - 1]->pos = { width / 2,height / 2,-depth / 2 };
	polygon.vertices[polygon.vertices.size() - 1]->uv = { 1.0f,1.0f };

	polygon.vertices.push_back(new Vertex);
	polygon.vertices[polygon.vertices.size() - 1]->pos = { width / 2,height / 2,depth / 2 };
	polygon.vertices[polygon.vertices.size() - 1]->uv = { 1.0f,0.0f };


	//��
	polygon.vertices.push_back(new Vertex);
	polygon.vertices[polygon.vertices.size() - 1]->pos = { -width / 2,-height / 2,depth / 2 };
	polygon.vertices[polygon.vertices.size() - 1]->uv = { 0.0f,1.0f };

	polygon.vertices.push_back(new Vertex);
	polygon.vertices[polygon.vertices.size() - 1]->pos = { -width / 2,-height / 2,-depth / 2 };
	polygon.vertices[polygon.vertices.size() - 1]->uv = { 0.0f,0.0f };

	polygon.vertices.push_back(new Vertex);
	polygon.vertices[polygon.vertices.size() - 1]->pos = { width / 2,-height / 2,depth / 2 };
	polygon.vertices[polygon.vertices.size() - 1]->uv = { 1.0f,1.0f };

	polygon.vertices.push_back(new Vertex);
	polygon.vertices[polygon.vertices.size() - 1]->pos = { width / 2,-height / 2,-depth / 2 };
	polygon.vertices[polygon.vertices.size() - 1]->uv = { 1.0f,0.0f };

	//��
	polygon.vertices.push_back(new Vertex);
	polygon.vertices[polygon.vertices.size() - 1]->pos = { -width / 2,height / 2,depth / 2 };
	polygon.vertices[polygon.vertices.size() - 1]->uv = { 0.0f,1.0f };

	polygon.vertices.push_back(new Vertex);
	polygon.vertices[polygon.vertices.size() - 1]->pos = { -width / 2,height / 2,-depth / 2 };
	polygon.vertices[polygon.vertices.size() - 1]->uv = { 0.0f,0.0f };

	polygon.vertices.push_back(new Vertex);
	polygon.vertices[polygon.vertices.size() - 1]->pos = { width / 2,height / 2,depth / 2 };
	polygon.vertices[polygon.vertices.size() - 1]->uv = { 1.0f,1.0f };

	polygon.vertices.push_back(new Vertex);
	polygon.vertices[polygon.vertices.size() - 1]->pos = { width / 2,height / 2,-depth / 2 };
	polygon.vertices[polygon.vertices.size() - 1]->uv = { 1.0f,0.0f };
	//�O
	polygon.indices.push_back(new unsigned short(0)), polygon.indices.push_back(new unsigned short(1)), polygon.indices.push_back(new unsigned short(2));
	polygon.indices.push_back(new unsigned short(2)), polygon.indices.push_back(new unsigned short(1)), polygon.indices.push_back(new unsigned short(3));
	//���
	polygon.indices.push_back(new unsigned short(5)), polygon.indices.push_back(new unsigned short(4)), polygon.indices.push_back(new unsigned short(6));
	polygon.indices.push_back(new unsigned short(5)), polygon.indices.push_back(new unsigned short(6)), polygon.indices.push_back(new unsigned short(7));
	//��
	polygon.indices.push_back(new unsigned short(8)), polygon.indices.push_back(new unsigned short(9)), polygon.indices.push_back(new unsigned short(10));
	polygon.indices.push_back(new unsigned short(10)), polygon.indices.push_back(new unsigned short(9)), polygon.indices.push_back(new unsigned short(11));
	//�E
	polygon.indices.push_back(new unsigned short(13)), polygon.indices.push_back(new unsigned short(12)), polygon.indices.push_back(new unsigned short(14));
	polygon.indices.push_back(new unsigned short(13)), polygon.indices.push_back(new unsigned short(14)), polygon.indices.push_back(new unsigned short(15));
	//��
	polygon.indices.push_back(new unsigned short(16)), polygon.indices.push_back(new unsigned short(17)), polygon.indices.push_back(new unsigned short(18));
	polygon.indices.push_back(new unsigned short(18)), polygon.indices.push_back(new unsigned short(17)), polygon.indices.push_back(new unsigned short(19));
	//��
	polygon.indices.push_back(new unsigned short(21)), polygon.indices.push_back(new unsigned short(20)), polygon.indices.push_back(new unsigned short(22));
	polygon.indices.push_back(new unsigned short(21)), polygon.indices.push_back(new unsigned short(22)), polygon.indices.push_back(new unsigned short(23));
	CreateModel(polygon);

	return polygon;
}


Object::ObjectData Object::CreateCylinder(int division, int prizmHeight, int radius)
{
	Object::ObjectData polygon;

	HRESULT result = S_FALSE;

	std::vector<Vertex> realVertices;
	// ���_���W�̌v�Z�i�d������j
	{
		realVertices.resize((division + 1) * 2);
		int index = 0;
		float zValue;

		// ���
		zValue = prizmHeight / 2.0f;
		for (int i = 0; i < division; i++)
		{
			XMFLOAT3 vertex;
			vertex.x = radius * sinf(XM_2PI / division * i);
			vertex.y = radius * cosf(XM_2PI / division * i);
			vertex.z = zValue;
			realVertices[index++].pos = vertex;
		}
		realVertices[index++].pos = XMFLOAT3(0, 0, zValue);	// ��ʂ̒��S�_
		// �V��
		zValue = -prizmHeight / 2.0f;
		for (int i = 0; i < division; i++)
		{
			XMFLOAT3 vertex;
			vertex.x = radius * sinf(XM_2PI / division * i);
			vertex.y = radius * cosf(XM_2PI / division * i);
			vertex.z = zValue;
			realVertices[index++].pos = vertex;
		}
		realVertices[index++].pos = XMFLOAT3(0, 0, zValue);	// �V�ʂ̒��S�_
	}

	// ���_���W�̌v�Z�i�d���Ȃ��j
	{

		// ���
		for (int i = 0; i < division; i++)
		{
			unsigned short index0 = i + 1;
			unsigned short index1 = i;
			unsigned short index2 = division;
			polygon.vertices.push_back(new Vertex);
			polygon.vertices[polygon.vertices.size() - 1]->pos = realVertices[index0].pos;
			polygon.vertices.push_back(new Vertex);
			polygon.vertices[polygon.vertices.size() - 1]->pos = realVertices[index1].pos;
			polygon.vertices.push_back(new Vertex);
			polygon.vertices[polygon.vertices.size() - 1]->pos = realVertices[index2].pos; // ��ʂ̒��S�_
		}
		// ��ʂ̍Ō�̎O�p�`��1�Ԗڂ̃C���f�b�N�X��0�ɏ�������
		polygon.vertices[polygon.vertices.size() - 3]->pos = realVertices[0].pos;

		int topStart = division + 1;
		// �V��
		for (int i = 0; i < division; i++)
		{
			unsigned short index0 = topStart + i;
			unsigned short index1 = topStart + i + 1;
			unsigned short index2 = topStart + division;
			polygon.vertices.push_back(new Vertex);
			polygon.vertices[polygon.vertices.size() - 1]->pos = realVertices[index0].pos;
			polygon.vertices.push_back(new Vertex);
			polygon.vertices[polygon.vertices.size() - 1]->pos = realVertices[index1].pos;
			polygon.vertices.push_back(new Vertex);
			polygon.vertices[polygon.vertices.size() - 1]->pos = realVertices[index2].pos; // �V�ʂ̒��S�_
		}
		// �V�ʂ̍Ō�̎O�p�`��1�Ԗڂ̃C���f�b�N�X��0�ɏ�������
		polygon.vertices[polygon.vertices.size() - 2]->pos = realVertices[topStart].pos;

		// ����
		for (int i = 0; i < division; i++)
		{
			unsigned short index0 = i + 1;
			unsigned short index1 = topStart + i + 1;
			unsigned short index2 = i;
			unsigned short index3 = topStart + i;

			if (i == division - 1)
			{
				index0 = 0;
				index1 = topStart;
			}
			polygon.vertices.push_back(new Vertex);
			polygon.vertices[polygon.vertices.size() - 1]->pos = realVertices[index0].pos;

			polygon.vertices.push_back(new Vertex);
			polygon.vertices[polygon.vertices.size() - 1]->pos = realVertices[index1].pos;

			polygon.vertices.push_back(new Vertex);
			polygon.vertices[polygon.vertices.size() - 1]->pos = realVertices[index2].pos;

			polygon.vertices.push_back(new Vertex);
			polygon.vertices[polygon.vertices.size() - 1]->pos = realVertices[index2].pos;

			polygon.vertices.push_back(new Vertex);
			polygon.vertices[polygon.vertices.size() - 1]->pos = realVertices[index1].pos;

			polygon.vertices.push_back(new Vertex);
			polygon.vertices[polygon.vertices.size() - 1]->pos = realVertices[index3].pos;
		}
	}
	int planeCount = division * 2 + division * 2;		// �ʂ̐�
	planeCount = planeCount * 3;
	// ���_�C���f�b�N�X�̐ݒ�
	{
		for (int i = 0; i < planeCount; i++)
		{
			polygon.indices.push_back(new unsigned short(i));
		}
	}
	CreateModel(polygon);
	return polygon;
}

Object::ObjectData Object::CreateOBJ(const std::string filename, bool smoothing)
{
	Object::ObjectData polygon;

	int index = 0;//�C���f�b�N�X�̐�����
	//�t�@�C���X�g���[��
	std::ifstream file;
	//.obj�t�@�C�����J��
	std::string directoryPath = "Resources/" + filename + "/";
	file.open(directoryPath + filename + ".obj");
	//�t�@�C���I�[�v�����s���`�F�b�N
	if (file.fail())
	{
		assert(0);
	}
	vector<XMFLOAT3>positions;//���_���W
	vector<XMFLOAT3>normals;//�@���x�N�g��
	vector<XMFLOAT2>texcoords;//�e�N�X�`��UV
	//�P�s���ǂݍ���
	string line;
	while (getline(file, line))
	{
		//1�s���̕�������X�g���[���ɕϊ����ĉ�͂��₷������
		std::istringstream line_stream(line);

		//���p�X�y�[�X��؂�ōs�̐擪��������擾
		string key;
		getline(line_stream, key, ' ');

		if (key == "mtllib")
		{
			//�}�e���A���̃t�@�C�����ǂݍ���
			string filename;
			line_stream >> filename;
			//�}�e���A���ǂݍ���
			polygon.OBJTexture = LoadMaterial(directoryPath, filename);
		}

		//�擪������v�Ȃ璸�_���W
		if (key == "v")
		{
			//X,Y,Z���W�ǂݍ���
			XMFLOAT3 position{};
			line_stream >> position.x;
			line_stream >> position.y;
			line_stream >> position.z;
			//���W�f�[�^�ɒǉ�
			positions.emplace_back(position);
		}
		//�擪������vt�Ȃ�e�N�X�`��
		if (key == "vt")
		{
			//U,V�����ǂݍ���
			XMFLOAT2 texcoord{};
			line_stream >> texcoord.x;
			line_stream >> texcoord.y;
			//V�������]
			texcoord.y = 1.0f - texcoord.y;
			//�e�N�X�`�����W�f�[�^�ɒǉ�
			texcoords.emplace_back(texcoord);
		}
		//�擪������vn�Ȃ�@���x�N�g��
		if (key == "vn")
		{
			//X,Y,Z�����ǂݍ���
			XMFLOAT3 normal{};
			line_stream >> normal.x;
			line_stream >> normal.y;
			line_stream >> normal.z;
			//�@���x�N�g���f�[�^�ɒǉ�
			normals.emplace_back(normal);
		}

		//�擪������f�Ȃ�|���S���i�O�p�`�j
		if (key == "f")
		{
			int faceIndexCount = 0;
			//���p�X�y�[�X��؂�ōs�̑�����ǂݍ���
			string index_string;
			while (getline(line_stream, index_string, ' '))
			{
				//���_�C���f�b�N�X�P���̕�������X�g���[���ɕϊ����ĉ�͂��₷������
				std::istringstream index_stream(index_string);
				unsigned short indexPosition, indexNormal, indexTexcoord;
				index_stream >> indexPosition;
				index_stream.seekg(1, ios_base::cur);//�X���b�V�����΂�
				index_stream >> indexTexcoord;
				index_stream.seekg(1, ios_base::cur);//�X���b�V�����΂�
				index_stream >> indexNormal;

				//���_�f�[�^�̒ǉ�
				Vertex vertex{};
				vertex.pos = positions[indexPosition - 1];
				vertex.normal = normals[indexNormal - 1];
				vertex.uv = texcoords[indexTexcoord - 1];
				polygon.vertices.push_back(new Vertex);
				polygon.vertices[polygon.vertices.size() - 1]->pos = vertex.pos;
				polygon.vertices[polygon.vertices.size() - 1]->normal = vertex.normal;
				polygon.vertices[polygon.vertices.size() - 1]->uv = vertex.uv;
				//�G�b�W�~�����p�̃f�[�^��ǉ�
				if (smoothing)
				{
					//v�L�[(���W�f�[�^)�̔ԍ��ƁA�S�č����������_�̃C���f�b�N�X���Z�b�g�œo�^����
					AddSmoothData(polygon, indexPosition, (unsigned short)GetVertexCount(polygon) - 1);
				}
				// �C���f�b�N�X�f�[�^�̒ǉ�
				if (faceIndexCount >= 3) {
					// �l�p�`�|���S����4�_�ڂȂ̂ŁA
					// �l�p�`��0,1,2,3�̓� 2,3,0�ŎO�p�`���\�z����
					polygon.indices.push_back(new unsigned short(polygon.indices.size() - 1 - index));
					polygon.indices.push_back(new unsigned short(polygon.indices.size() - 1 - index));
					polygon.indices.push_back(new unsigned short(polygon.indices.size() - 5 - index));
					index += 2;
				}
				else
				{
					polygon.indices.push_back(new unsigned short(polygon.indices.size() - index));
				}

				faceIndexCount++;

			}
		}
	}
	//�t�@�C�������
	file.close();
	//���_�@���̕��ςɂ��G�b�W���~����
	if (smoothing)
	{
		CalculateSmoothedVertexNormals(polygon);
	}
	OBJCreateModel(polygon);

	return polygon;
}
