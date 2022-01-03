#pragma once
#include<xaudio2.h>
#pragma comment(lib,"xaudio2.lib")
#include <fstream>
#include <cassert>
#include<d3dx12.h>

using namespace Microsoft::WRL;
class Sound
{
public:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	ComPtr<IXAudio2>xAudio2;
	IXAudio2MasteringVoice *masterVoice;

	//�`�����N�w�b�_
	struct ChunkHeader
	{
		char id[4];
		int32_t size;//�`�����N�T�C�Y
	};

	struct RiffHeader
	{
		ChunkHeader chunk;
		char type[4];
	};

	struct FormatChunk
	{
		ChunkHeader chunk;
		WAVEFORMATEX fmt;
	};

	struct SoundData
	{
		WAVEFORMATEX wfex;
		BYTE *pBuffer;
		unsigned int BufferSize;
	};

	Sound();
	void Init();

	/// <summary>
	/// ���쐬
	/// </summary>
	/// <returns></returns>
	static Sound *Create();

	//WAVE�ǂݍ���
	static SoundData SoundLoadWave(const char *firename);
	//�������폜
	static void SoundUnload(SoundData *soundData);
	//1��Đ�
	void Sound::SoundSEPlayWave( const SoundData &soundData);
	//���[�v�Đ�
	 void Sound::SoundBGMPlayLoopWave( const SoundData &soundData, IXAudio2SourceVoice *pSourceVoice);

	void Sound::SoundStop( const SoundData &soundData, IXAudio2SourceVoice *pSourceVoice);

	IXAudio2SourceVoice *BGM = nullptr;
};

