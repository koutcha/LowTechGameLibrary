#ifndef FILE_H
#define FILE_H
class File {

private:
	//データの先頭ポインタ
	char* data;
	//データのサイズ((size)byte)
	int size;
public:
	File(const char* filepass);
	~File();
	//sizeのゲッタ
	int getFileSize() const;
	const char* getData()const;
	//データのポインタ取得
	unsigned getUnsigned(int position) const;

};
#endif

