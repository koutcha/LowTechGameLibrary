
#pragma comment(lib, "winmm.lib")
#include <windows.h>
#include "JoyPad.h"
#include <list>
#include <algorithm>

using namespace std;
//static�ϐ��̏�����
JoyPad* JoyPad::instance = 0;
JOYINFOEX* JoyPad::joyInfo = 0;
int JoyPad::joyPadNum = 0;
int* JoyPad::supoertedId = 0;
JoyPad::JoyPad() {

}
JoyPad::~JoyPad()
{
}
void JoyPad::Create()
{
	//���̂���������Ԃ�
	if (instance != 0) {
		return;
	}
	joyInfo = new JOYINFOEX;


	joyInfo->dwSize = sizeof(JOYINFOEX);
	joyInfo->dwFlags = JOY_RETURNALL;
	int padNum = 0;
	list<int> idList;
	for (unsigned int i = 0; i<joyGetNumDevs(); i++) {//�T�|�[�g����Ă���W���C�X�e�B�b�N�̐���Ԃ�
		if (JOYERR_NOERROR == joyGetPosEx(i, joyInfo)) {
			printf("�W���C�X�e�B�b�N No.%d�@�ڑ�����Ă��܂�\n", i);
			padNum++;
			idList.push_back(i);
		}
	}
	//�p�b�h���Ȃ����ĂȂ�������Ԃ�
	if (padNum < 1) {
		delete joyInfo;
		return;
	}
	//joyInfo�ێ�
	
	joyPadNum = padNum;
	supoertedId = new int[padNum];
	auto itr = idList.begin();
	for (int i = 0; i < padNum; ++i) {
		supoertedId[i] = *itr;
		printf("id:%d��No.%d��o�^�������I\n", i, *itr);
		itr++;
	}
}

void JoyPad::Destroy()
{
	delete instance;
	instance = 0;
	delete[] supoertedId;
	supoertedId = 0;
	delete joyInfo;
	joyInfo = 0;

}
JoyPad* JoyPad::getInstance()
{
	return instance;
}

int JoyPad::getJoyPadNum()
{
	return joyPadNum;
}

bool JoyPad::isOn(Buttons button, int id)
{
	unsigned flag = (unsigned)button;
	if (JOYERR_NOERROR == joyGetPosEx(supoertedId[id], joyInfo)) {
		flag = joyInfo->dwButtons & flag;
		if (flag > 0) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}

}

JoyPad::POVDirection JoyPad::getPOVDirection(int id)
{
	if (JOYERR_NOERROR == joyGetPosEx(supoertedId[id], joyInfo)) {
		return (POVDirection)joyInfo->dwPOV;
	}
	else {
		return POV_NONE;
	}

}

unsigned JoyPad::getXAxsis(int id)
{
	if (JOYERR_NOERROR == joyGetPosEx(supoertedId[id], joyInfo)) {
		return joyInfo->dwXpos;
	}
	else {
		return 32767;
	}
}

unsigned JoyPad::getYAxsis(int id)
{
	if (JOYERR_NOERROR == joyGetPosEx(supoertedId[id], joyInfo)) {
		return joyInfo->dwYpos;
	}
	else {
		return 32767;
	}
}
unsigned JoyPad::getZAxsis(int id)
{
	if (JOYERR_NOERROR == joyGetPosEx(supoertedId[id], joyInfo)) {
		return joyInfo->dwZpos;
	}
	else {
		return 32767;
	}
}

unsigned JoyPad::getRAxsis(int id)
{
	if (JOYERR_NOERROR == joyGetPosEx(supoertedId[id], joyInfo)) {
		return joyInfo->dwRpos;
	}
	else {
		return 32767;
	}
}
