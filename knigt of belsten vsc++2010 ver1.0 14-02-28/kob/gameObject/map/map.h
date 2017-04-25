#ifndef INCLUDE_MAP_H
#define INCLUDE_MAP_H

#include "../../defines.h"
//#include "../../shared_ptr.h"
#include "../../2DGraph/2DGraphForDxLib.h"
#include "../../2DGraph/Draw2DForDxLib.h"


#include <list>
#include <string>
#include "../../file/TexRead.h"

class Map;

typedef boost::shared_ptr<Map> sp_Map;

typedef list<sp_Graphics2D> SpGraph2DList;

struct backGroundObject
{
	string name;
	int x;
	int y;
	double scrollSpeed;
	double exrate;
	
	sp_Graphics2D spGraph;

	backGroundObject()
	{
		name="noname";
		x=0;
		y=0;
		scrollSpeed=1.0;
		exrate=1.0;
	}
};


class Map
{
private:

	int m_Width;

	int m_ScrollX;

	int m_ScrollMinX;

	sp_DrawBuffer m_spDrawBufferFarEnd;
	sp_DrawBuffer m_spDrawBuffer;
	sp_DrawBuffer m_spDrawBufferFront;

	sp_Graphics2D m_spGraphBackGroundFarEnd;

	SpGraph2DList m_GraphList_Road;
	int m_roadTypeMax;
	sp_Graphics2D* m_pSpGraph_Road_Array;
	int m_roadMax;//string * m_pName_Road_Array;


	//背景オブジェクト関連の変数
	SpGraph2DList m_GraphList_BackGroundObject;
	int m_backGroundObjectTypeMax;//string * m_pName_Road_Array;
	backGroundObject* m_BackGroundObject_Array;
	int m_backGroundObjectMax;
	

	//フロント　オブジェクト関連の変数
	SpGraph2DList m_GraphList_FrontObject;
	int m_FrontObjectTypeMax;//string * m_pName_Road_Array;
	backGroundObject* m_FrontObject_Array;
	int m_FrontObjectMax;


	
	void reset();


public:

	Map();
	~Map();

	void updateScroll(int playerX);

	void setScrollMinX(int x);



	int getWidth (){return m_Width;}

	void initialize(const char filePath);
	void initialize();

	void initializeDrawBuffer(sp_DrawBuffer buffFarEnd,sp_DrawBuffer buff,sp_DrawBuffer buffFront);


	//道関連の関数
	void initializeGraphList_Road(char* filePath);
	void initializeGraph_Road(char*filepath);
	sp_Graphics2D getGraph_RoadNamed(const char* name);
	
	//背景オブジェクト関連の関数
	void initializeGraphList_BackGroundObject(char *filePath);
	void initializeGraph_BackGroundObject(char* filePath);
	sp_Graphics2D getGraph_BackGroundObjectNamed(const char* name);

	//フロントオブジェクト関連の関数
	void initializeGraphList_FrontObject(char *filePath);
	void initializeGraph_FrontObject(char* filePath);
	sp_Graphics2D getGraph_FrontObjectNamed(const char* name);



	void drawSet();

	void fixScrollPosition(int x);
	
	int getScrolX(){return m_ScrollX;};



};

#endif