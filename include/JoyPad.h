#ifndef JOYPAD_H
#define JOYPAD_H
struct joyinfoex_tag;
typedef joyinfoex_tag JOYINFOEX;
class JoyPad {
public:
	enum Buttons {
		Button1 = 0x1,
		Button2 = 0x2,
		Button3 = 0x4,
		Button4 = 0x8,
		Button5 = 0x10,
		Button6 = 0x20,
		Button7 = 0x40,
		Button8 = 0x80,
		Button9 = 0x100,
		Butoon10 = 0x200
	};
	enum POVDirection {
		POV_UP = 0,
		POV_UP_LEFT = 4500,
		POV_LEFT = 9000,
		POV_DOWN_LEFT = 13500,
		POV_DOWN = 18000,
		POV_DOWN_RIGHT = 22500,
		POV_RIGHT = 27000,
		POV_UP_RIGHT = 31500,
		POV_NONE = 0xffff
	};
	static void Create();
	static void Destroy();
	static  JoyPad* getInstance();
	static int getJoyPadNum();

	bool isOn(Buttons, int id);
	POVDirection getPOVDirection(int i);
	unsigned getXAxsis(int id);
	unsigned getYAxsis(int id);
	unsigned getZAxsis(int id);
	unsigned getRAxsis(int id);

private:
	JoyPad();
	~JoyPad();
	static JoyPad* instance;
	static int* supoertedId;
	static int joyPadNum;
	static JOYINFOEX* joyInfo;
};
#endif