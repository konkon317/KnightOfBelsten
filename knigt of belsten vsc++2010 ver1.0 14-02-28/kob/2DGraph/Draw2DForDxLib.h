//////////////////////
//	2013/7/18-7/19
//	���� �N��
//	Kousuke Fujii
/////////////////////



#ifndef INCLUDE_DRAW_2D
#define INCLUDE_DRAW_2D

#include "../defines.h"

#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>
using namespace std;

class Graphics2D;

struct Cell;

class DrawBuffer;

typedef vector<Cell> VCell;
typedef boost::shared_ptr<DrawBuffer> sp_DrawBuffer;


enum DRAW_MODE
{
	DRAW_NORMAL,	//�������ɕ`��
	DRAW_ROTA,		//���S����ɕ`��@��]�@�g�k����
	DRAW_ROTA_2,		//��]�̒��S���w�肵�� DRAW_ROTA
	DRAW_LEFT_BOTTOM,//�����
	DRAW_CENTER_BOTTOM
};

enum BLEND_MODE
{
	BLEND_NORMAL,

	BLEND_ALPHA,
	BLEND_ADD,
	BLEND_SUB,
	BLEND_MULA,
	BLEND_INVSRC
};

struct CellBlend
{
	BLEND_MODE m_blendMode;
	unsigned char m_pal;//�p�����[�^

	CellBlend(BLEND_MODE bl,char pal);
	CellBlend()
	{
		m_blendMode=BLEND_NORMAL;
		m_pal=0;
	}
	
};

struct Cell//�`��̂��߂̃f�[�^��ێ�����\����
{
	int m_x;
	int m_y;
	double m_z;

	int m_baseX;
	int m_baseY;

	DRAW_MODE m_DrawMode;
	
	bool m_bTurnFlag; 
	
	int m_handle;
	
	double m_angle;//�A���O��
	double m_exRate;//�g�嗦

	CellBlend m_cellBlend;

	Cell(int handle,DRAW_MODE m_DrawMode,int x,int y,double z,int baseX,int baseY,double angle,double exRate,bool bTurnFlag,CellBlend cellBlend);
};

/*
vector<Cell> vCell;//cell�̓��I�z��
int setNum=0;//����̃t���[���ŃZ�b�g���ꂽ��
*/

class DrawBuffer
{

private:
	VCell m_vCell;
	int m_setNum;

	CellBlend m_cellBlend;

	

public :
	
 DrawBuffer();
 ~DrawBuffer();

void setCellBlend(BLEND_MODE blend_mode,int pal)
{
	m_cellBlend.m_blendMode=blend_mode;


	if(pal<0)pal=0;
	if(pal>255)pal=255;


	m_cellBlend.m_pal=static_cast<unsigned char>(pal);
}

void resetCellBlend()
{
	m_cellBlend.m_blendMode=BLEND_NORMAL;
	m_cellBlend.m_pal=0;
}

 void resetVCell();//vCell�̃f�[�^�����ׂč폜����

//vCell�Ƀf�[�^���i�[���邽�߂̊֐�
 void DrawSet(Graphics2D *pGraph,int num ,int x,int y,bool bTurnFlag); 
 void DrawSet(Graphics2D *pGraph,int num ,int x,int y,double z,bool bTurnFlag);

 void DrawSetRota(Graphics2D *pGraph,int num ,int x,int y,double angle,double exRate,bool bTurnFlag);
 void DrawSetRota(Graphics2D *pGraph,int num ,int x,int y,double z,double angle,double exRate,bool bTurnFlag);

 void DrawSetRota(Graphics2D *pGraph,int num ,int x,int y,int baseX,int baseY,double angle,double exRate,bool bTurnFlag);
 void DrawSetRota(Graphics2D *pGraph,int num ,int x,int y,int baseX,int baseY,double z,double angle,double exRate,bool bTurnFlag);

 void DrawSetLeftBottom(Graphics2D *pGraph,int num ,int x,int y,double angle,double exRate,bool bTurnFlag);
 void DrawSetLeftBottom(Graphics2D *pGraph,int num ,int x,int y,double z,double angle,double exRate,bool bTurnFlag);

 void DrawSetCenterBottom(Graphics2D *pGraph,int num ,int x,int y,double angle,double exRate,bool bTurnFlag);
 void DrawSetCenterBottom(Graphics2D *pGraph,int num ,int x,int y,double z,double angle,double exRate,bool bTurnFlag);

 /*//�u�����h���[�h�̐ݒ肪�\�̃I�[�o�[���[�h
 void DrawSet(Graphics2D *pGraph,int num ,int x,int y,BLEND_MODE bl,int pal);
 void DrawSetCenter(Graphics2D *pGraph,int num,int x,int y,BLEND_MODE bl,int pal,double angle,double exRate=1.0);
 void DrawSetCenter(Graphics2D *pGraph,int num,int x,int y,BLEND_MODE bl,int pal);
 */

void DrawCell(Cell cell);//������CELL�����ƕ`�悷��
void DrawAll();

VCell* getVCell(){return &m_vCell;}

void sortZ();




};

#endif