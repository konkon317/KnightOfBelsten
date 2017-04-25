//////////////////////
//	2013/7/18-7/19
//	���� �N��
//	Kousuke Fujii
/////////////////////
#include "..\defines.h"
//#include "..\shared_ptr.h"

#ifndef FILE_PATH_LENGTH
#define FILE_PATH_LENGTH 128 //�t�@�C���p�X�̒���
#endif



#ifndef INCLUDE_GRAPHICS_2D
#define INCLUDE_GRAPHICS_2D

class Graphics2D;

typedef boost::shared_ptr<Graphics2D> sp_Graphics2D;//�X�}�[�g�|�C���^

//initialize shared_ptr Graphics
//spGraph�Ő錾���ꂽ�I�u�W�F�N�g�ɑ΂���new�Ń��������蓖�Č�A�������֐����Ăяo��
//���������蓖�Ă���摜���[�h�܂œ����ɍs�������ꍇ�Ɏg�p
extern void initializeSpGraph(sp_Graphics2D* pSpGraph,char* filePath);
extern void initializeSpGraph(sp_Graphics2D* pSpGraph,char* filePath,int max,int xSize,int ySize,int xNum,int yNum);


class Graphics2D
{
private:

	//�摜�n���h���z��̐�
	int m_max;

	//loadDivGraph�ŕ����ǂݍ��݂���Ƃ��������̉摜�T�C�Y
	int m_xSize;
	int m_ySize;

	//loadDivGraph�ŕ����ǂݍ��݂��鎞�̏c��������
	int m_xNum;
	int m_yNum;

	//���������ꂽ���ǂ���
	bool m_bIsInitialized;

	//�t�@�C���p�X
	char m_filePath[FILE_PATH_LENGTH];

	//�n���h���z��i�[�p
	int * m_pHandleBuff;

	string m_name;

public :

	Graphics2D();
	~Graphics2D();

	void reset();//�f�t�H���g�R���X�g���N�^�ŏ��������ꂽ���Ɠ�����Ԃɂ���

	//�������ēǂݍ��ޏꍇ
	void initialize(const char* filePath,int max,int xSize,int ySize,int xNum,int yNum);
	
	//�����ǂݍ��݂��g�p���Ȃ��ꍇ
	void initialize(const char* filePath);

	int getHandle(int num)const;//�ړI�̃n���h�����擾����
	
	void setName(const char *pC){m_name=pC;}
	string getName()const{return m_name;}


//�ȉ��C�����C���֐���` �P���ɒl���擾���邽�߂����̂���
	int getMax()const{return m_max;}
	int getXSize()const{return m_xSize;}
	int getYSize()const{return m_ySize;}
	int getXNum()const{return m_xNum;}
	int getYNum()const{return m_yNum;}
	bool isInitialized()const{return m_bIsInitialized;}//����������Ă��邩


};

#endif