#ifndef FILE_H
#define FILE_H
class File {

private:
	//�f�[�^�̐擪�|�C���^
	char* data;
	//�f�[�^�̃T�C�Y((size)byte)
	int size;
public:
	File(const char* filepass);
	~File();
	//size�̃Q�b�^
	int getFileSize() const;
	const char* getData()const;
	//�f�[�^�̃|�C���^�擾
	unsigned getUnsigned(int position) const;

};
#endif

