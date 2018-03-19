#include"GameLib\GameLib.h"
#include "File.h"
#include <fstream>


File::File(const char* filePath) :data(0), size(0) {
	std::ifstream inputFile(filePath, std::ifstream::binary);
	if (!inputFile) {
		HALT("ファイルがないよ");
	}
	else {
		//一番後ろへ移動
		inputFile.seekg(0, std::ifstream::end);
		//位置（末端）を保存
		size = static_cast<int>(inputFile.tellg());
		//最初に戻る
		inputFile.seekg(0, std::ifstream::beg);
		data = new char[size];
		//最初からsize分書き込み
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
	//1バイト左シフトしたものとor演算
	//0x0000????
	r |= up[position + 1] << 8;
	r |= up[position + 2] << 16;
	r |= up[position + 3] << 24;
	//unsignd完成
	return r;

}
