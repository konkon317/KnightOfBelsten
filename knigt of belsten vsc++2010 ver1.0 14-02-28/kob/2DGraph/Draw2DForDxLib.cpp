//////////////////////
//	2013/7/18-7/19
//	���� �N��
//	Kousuke Fujii
//  �g�p���C�u�����@DX���C�u���� http://homepage2.nifty.com/natupaji/DxLib/
/////////////////////

#include "Draw2DForDxLib.h"
#include "2DGraphForDxLib.h"
#include "DxLib.h"

bool compareZ(const Cell& left, const Cell& right)
{
	return left.m_z > right.m_z ;
}


/*
vector<Cell> vCell;
int setNum=0;*/

//�\����cellBlend�̃R���X�g���N�^
CellBlend::CellBlend(BLEND_MODE bl, char pal)
{	m_blendMode=bl;
	m_pal=pal;

}

//�\����Cell�̃R���X�g���N�^
Cell::Cell(int handle,DRAW_MODE drawMode, int x, int y, double z,int baseX,int baseY,double angle, double exRate,bool bTurnFlag,CellBlend cellBlend)
{	
	m_handle=handle;
	m_DrawMode=drawMode;
	m_z=z;
	m_x=x;
	m_y=y;

	m_baseX=baseX;
	m_baseY=baseY;
	
	m_angle=angle;
	m_exRate=exRate;

	m_bTurnFlag=bTurnFlag;

	m_cellBlend=cellBlend;

}



DrawBuffer::DrawBuffer()
{
	cout<<"drawbuffer const"<<endl;
	m_cellBlend.m_blendMode=BLEND_NORMAL;
	m_cellBlend.m_pal=0;
}

DrawBuffer::~DrawBuffer()
{	
	cout<<"drawBuffer dest"<<endl;
	m_vCell.erase(m_vCell.begin(),m_vCell.end());
}


void DrawBuffer::sortZ()
{
	std::sort(m_vCell.begin(),m_vCell.end(),compareZ);
}

//------------------------------------------------------------------------------
//vCell�Ƀf�[�^���i�[���邽�߂̊֐�


//�������ɕ`�悷��
void DrawBuffer::DrawSet(Graphics2D *pGraph ,int num,int x,int y,bool bTurnFlag)
{
	if(pGraph==NULL)
		return;

	//CellBlend cellBlend(BLEND_NORMAL,0);
	Cell cell(pGraph->getHandle(num),DRAW_NORMAL,x,y,0.0,0,0,0.0,1.0,bTurnFlag,m_cellBlend);
	m_vCell.push_back(cell);
	m_setNum++;
}

//�������ɕ`�悷��
//z�������I�[�o�[���[�h�@z���̓\�[�g�p
void DrawBuffer::DrawSet(Graphics2D *pGraph ,int num,int x,int y,double z,bool bTurnFlag)
{
	if(pGraph==NULL)
		return;

	//CellBlend cellBlend(BLEND_NORMAL,0);
	Cell cell(pGraph->getHandle(num),DRAW_NORMAL,x,y,z,0,0,0.0,1.0,bTurnFlag,m_cellBlend);
	m_vCell.push_back(cell);
	m_setNum++;
}

//���S�

void DrawBuffer::DrawSetRota(Graphics2D *pGraph ,int num,int x,int y,double angle,double exRate,bool bTurnFlag)
{
	if(pGraph==NULL)
		return;

	//CellBlend cellBlend(BLEND_NORMAL,0);
	Cell cell(pGraph->getHandle(num),DRAW_ROTA,x,y,0.0,0,0,angle,exRate,bTurnFlag,m_cellBlend);
	m_vCell.push_back(cell);
	m_setNum++;
}

//���S�
//z���݁@�i�\�[�g�p�j
void DrawBuffer::DrawSetRota(Graphics2D *pGraph ,int num,int x,int y,double z,double angle,double exRate,bool bTurnFlag)
{
	if(pGraph==NULL)
		return;

	//CellBlend cellBlend(BLEND_NORMAL,0);
	Cell cell(pGraph->getHandle(num),DRAW_ROTA,x,y,z,0,0,angle,exRate,bTurnFlag,m_cellBlend);
	m_vCell.push_back(cell);
	m_setNum++;
}


//��_�w��
void DrawBuffer::DrawSetRota(Graphics2D *pGraph ,int num,int x,int y,int baseX,int baseY,double angle,double exRate,bool bTurnFlag)
{
	if(pGraph==NULL)
		return;

	//CellBlend cellBlend(BLEND_NORMAL,0);
	Cell cell(pGraph->getHandle(num),DRAW_ROTA_2,x,y,0.0,baseX,baseY,angle,exRate,bTurnFlag,m_cellBlend);
	m_vCell.push_back(cell);
	m_setNum++;
}

//��_�w��
//z���݁@�i�\�[�g�p�j
void DrawBuffer::DrawSetRota(Graphics2D *pGraph ,int num,int x,int y,int baseX,int baseY,double z,double angle,double exRate,bool bTurnFlag)
{
	if(pGraph==NULL)
		return;

	//CellBlend cellBlend(BLEND_NORMAL,0);
	Cell cell(pGraph->getHandle(num),DRAW_ROTA_2,x,y,z,baseX,baseY,angle,exRate,bTurnFlag,m_cellBlend);
	m_vCell.push_back(cell);
	m_setNum++;
}





//�����
void DrawBuffer::DrawSetLeftBottom(Graphics2D *pGraph ,int num,int x,int y,double angle,double exRate,bool bTurnFlag)
{
	if(pGraph==NULL)
		return;

	//CellBlend cellBlend(BLEND_NORMAL,0);
	Cell cell(pGraph->getHandle(num),DRAW_LEFT_BOTTOM,x,y,0.0,0,0,angle,exRate,bTurnFlag,m_cellBlend);
	m_vCell.push_back(cell);
	m_setNum++;
}

//�����
//z���݁@�i�\�[�g�p�j
void DrawBuffer::DrawSetLeftBottom(Graphics2D *pGraph ,int num,int x,int y,double z,double angle,double exRate,bool bTurnFlag)
{
	if(pGraph==NULL)
		return;

	//CellBlend cellBlend(BLEND_NORMAL,0);
	Cell cell(pGraph->getHandle(num),DRAW_LEFT_BOTTOM,x,y,z,0,0,angle,exRate,bTurnFlag,m_cellBlend);
	m_vCell.push_back(cell);
	m_setNum++;
}

//�����
void DrawBuffer::DrawSetCenterBottom(Graphics2D *pGraph ,int num,int x,int y,double angle,double exRate,bool bTurnFlag)
{
	if(pGraph==NULL)
		return;

	//CellBlend cellBlend(BLEND_NORMAL,0);
	Cell cell(pGraph->getHandle(num),DRAW_CENTER_BOTTOM,x,y,0.0,0,0,angle,exRate,bTurnFlag,m_cellBlend);
	m_vCell.push_back(cell);
	m_setNum++;
}

//�����
//z���݁@�i�\�[�g�p�j
void DrawBuffer::DrawSetCenterBottom(Graphics2D *pGraph ,int num,int x,int y,double z,double angle,double exRate,bool bTurnFlag)
{
	if(pGraph==NULL)
		return;

	//CellBlend cellBlend(BLEND_NORMAL,0);
	Cell cell(pGraph->getHandle(num),DRAW_CENTER_BOTTOM,x,y,z,0,0,angle,exRate,bTurnFlag,m_cellBlend);
	m_vCell.push_back(cell);
	m_setNum++;
}







//-------------------------------------------------------------------------------

void DrawBuffer::DrawCell(Cell cell)//CELL�̃f�[�^����`��
{
	//cout<<cell.m_z<<endl;

	if(cell.m_cellBlend.m_blendMode!=BLEND_NORMAL)//�u�����h���[�h�̐ݒ肪����Ȃ�
	{
		int blendModeDxlib=0;
		switch(cell.m_cellBlend.m_blendMode)
		{
			case BLEND_ALPHA:	blendModeDxlib=DX_BLENDMODE_ALPHA;	break;
			case BLEND_ADD:		blendModeDxlib=DX_BLENDMODE_ADD;	break;
			case BLEND_SUB:		blendModeDxlib=DX_BLENDMODE_SUB;	break;
			case BLEND_MULA:	blendModeDxlib=DX_BLENDMODE_MULA;	break;
			case BLEND_INVSRC:	blendModeDxlib=DX_BLENDMODE_INVSRC;	break;	
		}
		//�u�����h���[�h�̕ύX
		SetDrawBlendMode(blendModeDxlib,cell.m_cellBlend.m_pal);
	}

	//�`��

	switch(cell.m_DrawMode)
	{
	case DRAW_NORMAL:
		
		DrawGraph(cell.m_x,cell.m_y,cell.m_handle,true);

		break;
	case DRAW_ROTA:
		DrawRotaGraph(cell.m_x,cell.m_y,cell.m_exRate,cell.m_angle,cell.m_handle,true,cell.m_bTurnFlag);
		break;

	case DRAW_ROTA_2:
		if(cell.m_bTurnFlag)
		{
			int xSize=0;
			int ySize=0;
			GetGraphSize(cell.m_handle,&xSize,&ySize);
			DrawRotaGraph2(cell.m_x,cell.m_y,xSize-cell.m_baseX,cell.m_baseY,cell.m_exRate,cell.m_angle,cell.m_handle,true,cell.m_bTurnFlag);
		
		}
		else
		{		
			DrawRotaGraph2(cell.m_x,cell.m_y,cell.m_baseX,cell.m_baseY,cell.m_exRate,cell.m_angle,cell.m_handle,true,cell.m_bTurnFlag);
		}

		break;
	case DRAW_LEFT_BOTTOM:
		{
			int xSize=0;
			int ySize=0;
			GetGraphSize(cell.m_handle,&xSize,&ySize);
			DrawRotaGraph2(cell.m_x,cell.m_y,0,ySize,cell.m_exRate,cell.m_angle,cell.m_handle,true,cell.m_bTurnFlag);
		
		}
		break;

	case DRAW_CENTER_BOTTOM:
		{
			int xSize=0;
			int ySize=0;
			GetGraphSize(cell.m_handle,&xSize,&ySize);
			DrawRotaGraph2(cell.m_x,cell.m_y,xSize/2,ySize,cell.m_exRate,cell.m_angle,cell.m_handle,true,cell.m_bTurnFlag);
		
		}
		break;
	
	}

	//�u�����h���[�h�����ɖ߂�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
}

//-------------------------------------------------------------------------------

void DrawBuffer::DrawAll()//���ׂĂ�`��
{
	int size=m_vCell.size();
	for(unsigned int i=0;i<size;i++)
	{
		DrawCell(m_vCell[i]);
	}
	return ;
}

//-------------------------------------------------------------------------------

void DrawBuffer::resetVCell()//VCell�ɒ~���Ă���f�[�^�����ׂď�������
{
	m_vCell.erase(m_vCell.begin(),m_vCell.end());
	m_setNum=0;

}
