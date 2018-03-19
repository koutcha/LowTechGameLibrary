#ifndef IMAGE_H
#define IMAGE_H
class Image {
private:
	int width;
	int height;
	unsigned* data;
public:
	Image(const char* filePath);
	int Width();
	int Height();
	unsigned* Data()const;

	~Image();

};

unsigned blend(unsigned src, unsigned dst);
#endif