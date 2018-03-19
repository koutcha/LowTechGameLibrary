#include "Image.h"
#include "GameLib\Framework.h"
#include "File.h"

using namespace GameLib;
//�A���t�@�u�����h
unsigned blend(unsigned src, unsigned dst)
{
	double srcA = static_cast<double>((src & 0xff000000) >> 24) / 255.0;
	double srcR = static_cast<double>((src & 0x00ff0000) >> 16);
	double srcG = static_cast<double>((src & 0x0000ff00) >> 8);
	double srcB = static_cast<double>((src & 0x000000ff));


	double dstR = static_cast<double>((dst & 0x00ff0000) >> 16);
	double dstG = static_cast<double>((dst & 0x0000ff00) >> 8);
	double dstB = static_cast<double>((dst & 0x000000ff));
	unsigned r = static_cast<unsigned>(dstR + srcA*(srcR - dstR));
	unsigned g = static_cast<unsigned>(dstG + srcG*(srcG - dstG));
	unsigned b = static_cast<unsigned>(dstB + srcB*(srcB - dstB));

	unsigned ret = r << 16;
	ret |= g << 8;
	ret |= b;

	return ret;

}
Image::Image(const char* filePath) :
	width(0),
	height(0),
	data(0) {
	//dds�t�@�C���̓ǂݍ���
	//new���Ȃ��i�X�R�[�v�������玩����del
	File f(filePath);
	//12�o�C�g���獂��
	height = f.getUnsigned(12);
	//16�o�C�g�@��
	width = f.getUnsigned(16);

	data = new unsigned[height*width];
	//128����F���
	for (int i = 0; i < height*width; ++i)
	{
		data[i] = f.getUnsigned(128 + i * 4);
	}
}
int Image::Width()
{
	return width;
}
int Image::Height()
{
	return height;
}
unsigned * Image::Data()const
{
	return this->data;
}
Image::~Image() {
	SAFE_DELETE_ARRAY(data);
}
