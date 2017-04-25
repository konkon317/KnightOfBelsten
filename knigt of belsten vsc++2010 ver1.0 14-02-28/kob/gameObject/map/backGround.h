#ifndef INCLUDE_BACKGROUND_H
#define INCLUDE_BACKGROUND_H

#include "../../defines.h"
//#include "../../shared_ptr.h"
#include "../../Input/InputForDxLib.h"
#include "../../2DGraph/2DGraphForDxLib.h"
#include "../../2DGraph/Draw2DForDxLib.h"


class BackGround 
{

private:

sp_Graphics2D m_spGraphBackGround_0;
sp_Graphics2D m_spGraphBackGround_1;

sp_DrawBuffer m_spDrawBufferFarEnd;
sp_DrawBuffer m_spDrawBuffer;

public :

	BackGround();
	~BackGround();
	
	void initialize(sp_DrawBuffer spBuff);

	void drawSet(int scrollX);



};


#endif 