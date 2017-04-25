#ifndef INCLUDE_INTERFACE_H
#define INCLUDE_INTERFACE_H

#include "../../defines.h"
//#include "../../shared_ptr.h"
#include "../../2DGraph/2DGraphForDxLib.h"
#include "../../2DGraph/Draw2DForDxLib.h"

class Interface
{
private:
	sp_Graphics2D m_spGraph2D_HpGauge;
	sp_Graphics2D m_spGraph2D_HpPoint;

	sp_DrawBuffer m_spDrawBuffer;
public:

	Interface();
	~Interface();

	void initialize(sp_DrawBuffer spDrawBuffer);

	void DrawHpGauge(int point,int maxPoint);

	


};

#endif