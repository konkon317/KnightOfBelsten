
//プログラム 藤井康輔 2013/2/4～2/5

//使用ライブラリ　DXライブラリ http://homepage2.nifty.com/natupaji/DxLib/

#ifndef INCLUDE_MYINPUT_H
#define INCLUDE_MYINPUT_H

#include "DxLib.h"


#define KEY_INPUT_BUFFER_SIZE 256
#define PAD_INPUT_BUFFER_SIZE 32

//パッドでのインプット用変数のための添え字
#define PAD_DOWN			0
#define PAD_LEFT			1
#define PAD_RIGHT			2
#define PAD_UP				3
#define PAD_BUTTON_A		4
#define PAD_BUTTON_B		5
#define PAD_BUTTON_X		6
#define PAD_BUTTON_Y		7
#define PAD_BUTTON_LB		8
#define PAD_BUTTON_RB		9
#define PAD_BUTTON_BACK		10
#define PAD_BUTTON_START	11

//ここまでxbox360コントローラに対応ボタンあり

#define PAD_BUTTON_9		12
#define PAD_BUTTON_10		13
#define PAD_BUTTON_11		14
#define PAD_BUTTON_12		15
#define PAD_BUTTON_13		16
#define PAD_BUTTON_14		17
#define PAD_BUTTON_15		18
#define PAD_BUTTON_16		19
#define PAD_BUTTON_17		20
#define PAD_BUTTON_18		21	
#define PAD_BUTTON_19		22
#define PAD_BUTTON_20		23
#define PAD_BUTTON_21		24
#define PAD_BUTTON_22		25
#define PAD_BUTTON_23		26
#define PAD_BUTTON_24		27
#define PAD_BUTTON_25		28
#define PAD_BUTTON_26		29
#define PAD_BUTTON_27		30
#define PAD_BUTTON_28		31


//----------------------------------------------------------
class KeyInput {

private :
	int mKeyCt[KEY_INPUT_BUFFER_SIZE];
	char mKeyStateBuffer[KEY_INPUT_BUFFER_SIZE];


public :
	KeyInput (void);

	~KeyInput ();

	int keyCt(int key);
	
	void  keyScan();
};

//---------------------------------------------------------


class PadInput{

private:
	int mInputState;
	int mButtonCt[PAD_INPUT_BUFFER_SIZE];
	static const int mButtonNum[PAD_INPUT_BUFFER_SIZE];
	const int mPadNum;
	const int ButtonNumInitialize(int i);

public :
	PadInput(int i);
	PadInput();//デフォルトコンストラクタ
	~PadInput();
	void buttonScan();


	int buttonCt(int button);
};

//---------------------------------------------------------


class Input{

private:
	
	static const int InputType[4];
	
	static const int AltKeys[PAD_INPUT_BUFFER_SIZE];

	const int mPlayerMax;
	const int mPadMax;
	const bool mAltF;

	PadInput* mPIn[4];
	KeyInput mKIn;

	int padMaxInitialize(int pMax);

public :
	Input(int playerMax,bool altF); // altF パッドがつながっていないときにキーボードで代替するか
	~Input();
	void scan();
	
	int keyCt(int key);
	int PadCt(int padNum,int button);
};


#endif