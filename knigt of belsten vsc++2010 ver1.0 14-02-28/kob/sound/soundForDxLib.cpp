#include "soundForDxLib.h"

#include "DxLib.h"

#include "../file/TexRead.h"

list_sp_Sound g_SoundList;

//sound�N���X�̃����o�֐���`

Sound::Sound()
{
	m_handle=-1;
}

Sound::~Sound()
{
	DeleteSoundMem(m_handle);
	m_handle=-1;
}

void Sound::initialize(const char * filePath,const char * name)
{
	m_handle=LoadSoundMem(filePath);
	
	if(m_handle==-1)
	{
		cout<<"�T�E���h�̓ǂݍ��݂Ɏ��s���܂��� path:"<<filePath<<" name:"<<name<<endl;
		
		//MessageBox(NULL , TEXT("Kitty on your lap"),TEXT("���b�Z�[�W�{�b�N�X"),MB_OK);
	}

	m_name=name;
	m_filePath=filePath;
}


//-----------------------------------------------------
//extern�֐��̒�`
void initializeSoundsList(const char * headerPath)
{
	static bool FirstTime=true;

	if(FirstTime)
	{
		FirstTime=false;
		
		TexRead texRead(headerPath);
		if(texRead.isLoaded())
		{
			string str;
			char inputC[STRING_LENGTH];
			char* pLine;
			int pos=0;//���ǂ�ł���ʒu

			int max=0;

			//��s�ڂ�ǂݏo��
			if(texRead.readLineSkipOverSolidus()==false)
			{
				cout<<"��蔭��"<<endl;	
				return;
			}
			pLine=texRead.getLine();
			pos=0;
	
			getNextStringToComma(inputC,pLine,&pos);//���̕������inputC�ɃR�s�[����@pLine[pos]����','�܂���'\n'�܂Ł@
			str=inputC;
		
			if(str!="<max>")//���e�ɊԈႢ������ꍇ
			{	
				return;	
			}
			
			getNextStringToComma(inputC,pLine,&pos);//���̕������inputC�ɃR�s�[����@pLine[pos]����','�܂���'\n'�܂Ł@
			max=atoi(inputC);

			for(int i=0;i<max;i++)
			{
				if(texRead.readLineSkipOverSolidus()==false)
				{
					cout<<"��蔭��"<<endl;	
					return;
				}
				pLine=texRead.getLine();
				pos=0;

				getNextStringToComma(inputC,pLine,&pos);
				str =inputC;
				string path=str;

				getNextStringToComma(inputC,pLine,&pos);
				str =inputC;
				string name=str;

				sp_Sound spSound(new Sound());
				if(spSound.get()!=NULL)
				{
					spSound->initialize(path.c_str(),name.c_str());
					g_SoundList.push_back(spSound);					
				}
			}
		}	
	}
}



sp_Sound findSoundNamed(const char* Name)
{
	sp_Sound r;
	
	list_sp_Sound::iterator p=g_SoundList.begin();
	
	if(!(g_SoundList.empty()))
	while(p!=g_SoundList.end())
	{
		if ((*p)->getName()==Name)
		{
			r = (*p);

			break;
		}
		else
		{
			p++;	
		}
	}
	return r;
}


//name�Ɠ������O�̕t�����T�E���h�f�[�^��T���Đ�����
void playSound(const char * name,bool useLoop)
{
	sp_Sound spSound=findSoundNamed(name);

	if(spSound!=NULL)
	{
		int handle=spSound->getHandle();

		if(handle!=-1)
		{
			if(useLoop)
			{
				PlaySoundMem(handle,DX_PLAYTYPE_LOOP);
			}
			else
			{
				PlaySoundMem(handle,DX_PLAYTYPE_BACK);
			}
		}	
	}
}

//name�Ɠ������O�̕t�����T�E���h�f�[�^��T���Đ�����
void stopSound(const char * name)
{
	sp_Sound spSound=findSoundNamed(name);

	if(spSound!=NULL)
	{
		int handle=spSound->getHandle();

		if(handle!=-1)
		{
			StopSoundMem(handle);
		}	
	}
}