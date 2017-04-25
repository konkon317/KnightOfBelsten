#include "baseObject.h"


//--------------------------------------------------

BaseObject::BaseObject()
{
	m_x=m_y=m_z=0;

}

//--------------------------------------------------

BaseObject::~BaseObject()
{
	//empty
	//動的にメモリを確保したり、ファイルを開いていないので今のところ空
}

//--------------------------------------------------

void BaseObject::setDrawBuffer(sp_DrawBuffer spDrawBuffer, sp_DrawBuffer spDrawBufferShadow)
{
	

	m_spDrawBuffer=spDrawBuffer;
	m_spDrawBufferShadow=spDrawBufferShadow;

}


//--------------------------------------------------

void BaseObject::setGraphShadow(sp_Graphics2D spGraphShadow)
{
	m_spGraphShadow=spGraphShadow;
}


//--------------------------------------------------

void BaseObject::drawSetShadow(int scrollX)
{
	
	m_spDrawBufferShadow->DrawSetRota(m_spGraphShadow.get(),0,
			static_cast<int>(m_x)-scrollX,458+static_cast<int>(240.0-m_z)
			,m_z,0.0,1.0-(0.1*(m_z/240.0)),false);
}