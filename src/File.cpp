#include"GameLib\GameLib.h"
#include "File.h"
#include <fstream>


File::File(const char* filePath) :data(0), size(0) {
	std::ifstream inputFile(filePath, std::ifstream::binary);
	if (!inputFile) {
		HALT("�t�@�C�����Ȃ���");
	}
	else {
		//��Ԍ��ֈړ�
		inputFile.seekg(0, std::ifstream::end);
		//�ʒu�i���[�j��ۑ�
		size = static_cast<int>(inputFile.tellg());
		//�ŏ��ɖ߂�
		inputFile.seekg(0, std::ifstream::beg);
		data = new char[size];
		//�ŏ�����size����������
		inputFile.read(data, size);

	}
}
File::~File() {
	SAFE_DELETE_ARRAY(data);
}
int File::getFileSize() const
{
	return size;
}
const char * File::getData() const
{
	return data;
}
unsigned File::getUnsigned(int position) const
{
	const unsigned char* up;
	//
	up = reinterpret_cast< const unsigned char* >(data);
	//0x000000??
	unsigned r = up[position];
	//1�o�C�g���V�t�g�������̂�or���Z
	//0x0000????
	r |= up[position + 1] << 8;
	r |= up[position + 2] << 16;
	r |= up[position + 3] << 24;
	//unsignd����
	return r;

}
