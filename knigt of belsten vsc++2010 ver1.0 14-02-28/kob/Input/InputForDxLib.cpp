//�v���O���� ����N�� 2013/2/4�`2/5

//�g�p���C�u�����@DX���C�u���� http://homepage2.nifty.com/natupaji/DxLib/


#include "InputForDxLib.h"

#include <iostream>
using namespace std;


//�ÓI�Ȓ萔�̐ݒ�

const int PadInput::mButtonNum[]={
1    , 1<<1 , 1<<2 , 1<<3,  1<<4 , 1<<5 , 1<<6 , 1<<7 ,
1<<8 , 1<<9 , 1<<10, 1<<11, 1<<12, 1<<13, 1<<14, 1<<15,
1<<16, 1<<17, 1<<18, 1<<19, 1<<20, 1<<21, 1<<22, 1<<23,
1<<24, 1<<25, 1<<26, 1<<27, 1<<28, 1<<29, 1<<30, 1<<31,
};

const int Input::InputType[4]={
	DX_INPUT_PAD1,
	DX_INPUT_PAD2,
	DX_INPUT_PAD3,
	DX_INPUT_PAD4
};

const int Input::AltKeys[32]=
{
KEY_INPUT_DOWN	,KEY_INPUT_LEFT	,KEY_INPUT_RIGHT,KEY_INPUT_UP	,
KEY_INPUT_X		,KEY_INPUT_Z	,KEY_INPUT_S	,KEY_INPUT_A	,
KEY_INPUT_Q		,KEY_INPUT_W	,KEY_INPUT_TAB	,KEY_INPUT_SPACE,
KEY_INPUT_N		,KEY_INPUT_M	,//�����܂ŃQ�[���p�b�h�Ƀ{�^������(xbox360�R���g���[��)

KEY_INPUT_1		,KEY_INPUT_2	,
KEY_INPUT_3		,KEY_INPUT_4	,KEY_INPUT_5	,KEY_INPUT_6	,
KEY_INPUT_7		,KEY_INPUT_8	,KEY_INPUT_9	,KEY_INPUT_0	,
KEY_INPUT_NUMPAD0	,KEY_INPUT_NUMPAD1	,KEY_INPUT_NUMPAD2	,KEY_INPUT_NUMPAD3	,
KEY_INPUT_NUMPAD4	,KEY_INPUT_NUMPAD5	,KEY_INPUT_NUMPAD6	,KEY_INPUT_NUMPAD7	,
};




//---------------------------------------------------------

KeyInput::KeyInput (void)
{
	cout<<"keyInput �쐬"<<endl;
	for (int i=0;i<KEY_INPUT_BUFFER_SIZE;i++)mKeyCt[i]=0;
}
//---------------------------------------------------------

KeyInput::~KeyInput (){
cout<<"�����܂���-KeyInput"<<endl;
}

//---------------------------------------------------------

int KeyInput::keyCt(int key)
{
	if (key>=0&&key<KEY_INPUT_BUFFER_SIZE)
	return mKeyCt[key];
	
	else return 0;
}

//---------------------------------------------------------

void  KeyInput::keyScan()//�X�L����
{
	GetHitKeyStateAll(mKeyStateBuffer);

	for (int i=0;i<KEY_INPUT_BUFFER_SIZE;i++)
	{
	if (mKeyStateBuffer[i]==1)
		{
			mKeyCt[i]++;
		}
		else 
			mKeyCt[i]=0;
	}
}

//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------



//---------------------------------------------------------
PadInput::PadInput(int i):mPadNum(i)
{
	cout<<"�p�b�h�C���v�b�g�쐬 number"<<mPadNum<<endl;
	mInputState=0;
}

PadInput::PadInput():mPadNum(0)
{
	mInputState=0;
}

//---------------------------------------------------------

PadInput::~PadInput(){
cout<<"�����܂���-PadInput"<<endl;

}

//---------------------------------------------------------
void PadInput::buttonScan()
{
	mInputState=DxLib::GetJoypadInputState(mPadNum);
	
	for(int i=0;i<PAD_INPUT_BUFFER_SIZE;i++)
	{
		if((mInputState&mButtonNum[i])!=0)
		{
		mButtonCt[i]++;
		}
		else mButtonCt[i]=0;
	}

}
//---------------------------------------------------------

int  PadInput::buttonCt(int button)
{
	if(button>=0&&button<PAD_INPUT_BUFFER_SIZE)
	{
	return mButtonCt[button];
	}
	else return 0;
}

//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------

Input::Input(int pMax,bool altF):mPlayerMax(pMax),mAltF(altF),
mPadMax(padMaxInitialize(pMax))
{
cout<<"input �N���X�̍쐬"<<endl<<endl;


cout <<"�v���[���[�� ="<<mPlayerMax<<endl;
if(!(mPlayerMax>0&&mPlayerMax<=4))
{
	cout<<"�G���[ �v���C���[�̐l���ݒ肪�Ԉ���Ă��܂�"<<endl;
	cout<<"1����4�܂ł̐��l���R���X�g���N�^�ɓn���Ă�������"<<endl;
}
cout<<endl;


cout <<"padmax ="<<mPadMax<<endl;
if(mPadMax==0)cout<<"--�Q�[���p�b�h���ڑ�����Ă��܂���--"<<endl;
cout<<endl;


cout <<"altF ="<<mAltF<<endl;
if(mPadMax==0)
{
	cout<<"�Q�[���p�b�h�̐ڑ����Ȃ����߁A";
	if(mAltF)cout<<"�v���[���[1�́A�L�[�{�[�h�ł̑���ɂȂ�܂�"<<endl;
	if(!mAltF)
	{
		cout<<endl<<"�E�B���h�E����ăQ�[���p�b�h��ڑ�������A�Q�[�����ċN�����Ă�������"<<endl;
		cout<<"�܂��� Input�N���X �̃R���X�g���N�^(altF)�� true ��n���v���O���������Ă�������"<<endl;
	}
}
cout<<endl;


for(int i=0;i<4;i++)
{
mPIn[i]=0;//�|�C���^������
}

if(mPadMax!=0)
{
	for(int i=0;i<mPadMax;i++)
	{
	mPIn[i] = new PadInput(InputType[i]);
	}
}

cout<<"�Q�[���p�b�h���̓N���X * "<<mPadMax<<endl;
for(int i=0 ;i<4;i++)
{
	char* c =((mPIn[i]))?"O":"X";
	cout<<c<<endl;
	cout<<(mPIn[i])<<endl;
}

cout<<endl;


cout<<"input �N���X�̍쐬�@�R���X�g���N�^�I���"<<endl<<endl;
}
//---------------------------------------------------------
Input::~Input()
{
for (int i=0;i<4;i++)
{
	if(mPIn[i])
	{
	delete mPIn[i];
	mPIn[i]=0;
	}
}


cout<<"�����܂���-Input"<<endl;
}

//--------------------------------------------------------
int Input::padMaxInitialize(int plMax)
{
	int padNum=GetJoypadNum();
	int r=0;

	if(padNum==0)return 0;
	r=(padNum>plMax)?plMax:padNum;

	if(r>4)r=4;

return r;
}

//--------------------------------------------------------

void Input::scan()
{
	mKIn.keyScan();

	if(mPadMax!=0)
	{
		for(int i=0;i<mPadMax;i++)
		{
			(mPIn[i])->buttonScan();
		}
	}
}

//--------------------------------------------------------


int Input::keyCt(int key)
{
	return mKIn.keyCt(key);
}

//--------------------------------------------------------
int Input::PadCt(int padNum,int button)
{
	int r=0;
	if(padNum>=0 )
	{
		if(mPadMax!=0)
		{
			if(padNum<mPadMax)
			{
			r=(mPIn[padNum])->buttonCt(button);
			}
		}
		else 
			if(padNum==0&&mAltF)
		{
			if(button<32&&button>=0)
			{
				r=keyCt(AltKeys[button]);
			}
		}
	}
	return r;
}