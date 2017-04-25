#ifndef INCLUDE_BASE_OBJECT_H
#define INCLUDE_BASE_OBJECT_H

#include "../defines.h"
//#include "../shared_ptr.h"
#include "../Input/InputForDxLib.h"
#include "../2DGraph/2DGraphForDxLib.h"
#include "../2DGraph/Draw2DForDxLib.h"

class BaseObject
{

private:


protected:
	double m_x;
	double m_y;
	double m_z;

	sp_DrawBuffer m_spDrawBufferShadow;
	sp_DrawBuffer m_spDrawBuffer;

	sp_Graphics2D m_spGraphShadow;
	//sp_Graphics2D m_spGraph;


	void setX(double x)	{m_x=x;}
	void setY(double y)	{m_y=y;}
	void setZ(double z)	{m_z=z;}

public:
	BaseObject();
	virtual ~BaseObject();

	double getX()const{return m_x;}
	double getY()const{return m_y;}
	double getZ()const{return m_z;}

	virtual void drawSetShadow(int scrollX);
//	virtual void drawSet();

	void setDrawBuffer(sp_DrawBuffer spDrawBuffer,sp_DrawBuffer spDrawBufferShadow);
	virtual void setGraphShadow(sp_Graphics2D spGraphShadow);

};





#endif
