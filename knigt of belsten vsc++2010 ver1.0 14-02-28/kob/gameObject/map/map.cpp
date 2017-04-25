#include "map.h"
#include "../../file/TexRead.h"
	





Map::Map()
{
	m_Width=0;
	m_ScrollX=0;
	m_ScrollMinX=MOVE_MIN_X;
	m_pSpGraph_Road_Array=NULL;



	m_roadTypeMax=0;
	//m_pName_Road_Array=NULL;
	m_roadMax=0;

	m_BackGroundObject_Array=NULL;
	m_backGroundObjectTypeMax=0;
	m_backGroundObjectMax=0;

	m_FrontObject_Array=NULL;
	m_FrontObjectTypeMax=0;
	m_FrontObjectMax=0;
}


Map::~Map()
{
	m_GraphList_BackGroundObject.clear();
	m_GraphList_BackGroundObject.clear();

	SAFE_DELETE_ARRAY(m_pSpGraph_Road_Array);
	//SAFE_DELETE_ARRAY(m_pName_Road_Array);
	SAFE_DELETE_ARRAY(m_BackGroundObject_Array);

	m_spDrawBufferFarEnd.reset();
	m_spDrawBuffer.reset();

}

void Map::reset()
{	
	
	m_GraphList_BackGroundObject.clear();
	m_GraphList_BackGroundObject.clear();

	SAFE_DELETE_ARRAY(m_pSpGraph_Road_Array);
	//SAFE_DELETE_ARRAY(m_pName_Road_Array);
	SAFE_DELETE_ARRAY(m_BackGroundObject_Array);

	m_Width=0;
	m_ScrollX=0;
	m_pSpGraph_Road_Array=NULL;
	m_roadTypeMax=0;
	//m_pName_Road_Array=NULL;
	m_roadMax=0;

	m_BackGroundObject_Array=NULL;
	m_backGroundObjectTypeMax=0;
	m_backGroundObjectMax=0;

	m_spDrawBufferFarEnd.reset();
	m_spDrawBuffer.reset();
	
}


void Map::initialize(const char filepath)
{
	


}

void Map::initialize()
{
	int min=MOVE_MIN_X;
	if(min<0)min*=-1;
	m_Width=min+MOVE_MAX_X;

	initializeGraphList_Road("CsvMapData/testRoad.csv");
	initializeGraph_Road("CsvMapData/setRoadData.csv");
	initializeGraphList_BackGroundObject("CsvMapData/testBackGroundObject.csv");
	initializeGraph_BackGroundObject("CsvMapData/setBackGroundObjectData.csv");

	initializeGraphList_FrontObject("CsvMapData/testFrontObject.csv");
	initializeGraph_FrontObject("CsvMapData/setFrontObjectData.csv");

}

void Map::updateScroll(int playerX)
{
	m_ScrollX=playerX-(WINDOW_WIDTH/2);

	if(m_ScrollX<m_ScrollMinX)
	{
		m_ScrollX=m_ScrollMinX;
	}

	if(m_ScrollX>MOVE_MAX_X-(WINDOW_WIDTH))
	{
		m_ScrollX=MOVE_MAX_X-(WINDOW_WIDTH);
	}

}

void Map::fixScrollPosition(int x)
{
	if(m_ScrollX<x)
	{
		m_ScrollX+=10;
		if(m_ScrollX>x)
		{
			m_ScrollX=x;
		}
	}

	if(m_ScrollX>x)
	{
		m_ScrollX-=10;
		if(m_ScrollX<x)
		{
			m_ScrollX=x;
		}
	}

}

void Map::setScrollMinX(int x)
{
	if(x<=MOVE_MAX_X)
	{
		if(x>=MOVE_MIN_X)
		{
			m_ScrollMinX=x;		
		}
	}

}

void Map::initializeDrawBuffer(sp_DrawBuffer buffFarEnd,sp_DrawBuffer buff,sp_DrawBuffer buffFront)
{
//	++buffFarEnd;
//	++buff;
//	++buffFront;

	m_spDrawBufferFarEnd=buffFarEnd;
	m_spDrawBuffer=buff;
	m_spDrawBufferFront=buffFront;

	if(m_spGraphBackGroundFarEnd.get()==NULL)
	{
		m_spGraphBackGroundFarEnd=sp_Graphics2D(new Graphics2D());
		if(m_spGraphBackGroundFarEnd.get()!=NULL)
		{
//			++m_spGraphBackGroundFarEnd;
			m_spGraphBackGroundFarEnd->initialize("images/backGround/backGroundFarEnd.png");
		}
	}
}

void Map::initializeGraphList_Road(char *filePath)
{
	TexRead texRead(filePath);
	if(texRead.isLoaded())
	{
		cout<<"“Ç‚Ýž‚Ý¬Œ÷ initializeGraphList_Road"<<filePath<<endl;

		string str;

		char inputC[STRING_LENGTH];
		char *pLine;

		int pos=0;
		
		if(texRead.readLineSkipOverSolidus()==false)
		{
			cout<<"–â‘è”­¶"<<endl;	
			//reset();
			return;
		}
		pLine=texRead.getLine();
		pos=0;

		getNextStringToComma(inputC,pLine,&pos);
		str=inputC;

		if(str!="<max>")
		{
			return;
		}
		getNextStringToComma(inputC,pLine,&pos);
		m_roadTypeMax=atoi(inputC);

		if(m_roadTypeMax>=0)
		{
			
			for(int i=0;i<m_roadTypeMax;i++)
			{

				sp_Graphics2D spGraph2D;
				spGraph2D=sp_Graphics2D(new Graphics2D());
//				++spGraph2D;


				if(texRead.readLineSkipOverSolidus()==false)
				{
					cout<<"–â‘è”­¶"<<endl;	
					//reset();
					return;
				}
				pLine=texRead.getLine();
				pos=0;

				getNextStringToComma(inputC,pLine,&pos);
				str=inputC;

				spGraph2D->initialize(str.c_str());

				getNextStringToComma(inputC,pLine,&pos);
				str=inputC;

				spGraph2D->setName(str.c_str());

				m_GraphList_Road.push_back(spGraph2D);
//				++spGraph2D;
			}
		}
	}
}

void Map::initializeGraph_Road(char* filePath)
{
	TexRead texRead(filePath);
	if(texRead.isLoaded())
	{
		cout<<"“Ç‚Ýž‚Ý¬Œ÷ initializeGraphList_Road"<<filePath<<endl;

		string str;

		char inputC[STRING_LENGTH];
		char *pLine;

		int pos=0;
		
		if(texRead.readLineSkipOverSolidus()==false)
		{
			cout<<"–â‘è”­¶"<<endl;	
			//reset();
			return;
		}
		pLine=texRead.getLine();
		pos=0;

		getNextStringToComma(inputC,pLine,&pos);
		str=inputC;

		if(str!="<max>")
		{
			return;
		}
		getNextStringToComma(inputC,pLine,&pos);
		m_roadMax=atoi(inputC);

		if(m_roadMax>0)
		{
			if(m_pSpGraph_Road_Array==NULL)
			{
				m_pSpGraph_Road_Array=new sp_Graphics2D[m_roadMax];
				if(m_pSpGraph_Road_Array!=NULL)
				{
					for(int i=0;i<m_roadMax;i++)
					{
						if(texRead.readLineSkipOverSolidus()==false)
						{
							cout<<"–â‘è”­¶"<<endl;	
							//reset();
							return;
						}
						pLine=texRead.getLine();
						pos=0;
						getNextStringToComma(inputC,pLine,&pos);
						str=inputC;

//						++(m_pSpGraph_Road_Array[i]);
						m_pSpGraph_Road_Array[i]=getGraph_RoadNamed(str.c_str());

					}
				}
			
			}
		}
	}

}

sp_Graphics2D Map::getGraph_RoadNamed(const char* name)
{
	sp_Graphics2D r;
//	++r;
	string name_s=name;

	SpGraph2DList::iterator p=m_GraphList_Road.begin();
	
	if(!(m_GraphList_Road.empty()))
	while(p!=m_GraphList_Road.end())
	{
		if ((*p)->getName()==name_s)
		{
			r=(*p);
			break;
		}
		else
		{
			p++;
	
		}
	}
	//++r;
	return r;

}






void Map::initializeGraphList_BackGroundObject(char *filePath)
{
	TexRead texRead(filePath);
	if(texRead.isLoaded())
	{
		cout<<"“Ç‚Ýž‚Ý¬Œ÷ initializeGraphList_BackGroundObject"<<filePath<<endl;

		string str;

		char inputC[STRING_LENGTH];
		char *pLine;

		int pos=0;
		
		if(texRead.readLineSkipOverSolidus()==false)
		{
			cout<<"–â‘è”­¶"<<endl;	
			//reset();
			return;
		}
		pLine=texRead.getLine();
		pos=0;

		getNextStringToComma(inputC,pLine,&pos);
		str=inputC;

		if(str!="<max>")
		{
			return;
		}
		getNextStringToComma(inputC,pLine,&pos);
		m_backGroundObjectTypeMax=atoi(inputC);

		if(m_backGroundObjectTypeMax>=0)
		{
			
			for(int i=0;i<m_backGroundObjectTypeMax;i++)
			{

				sp_Graphics2D spGraph2D;
				spGraph2D=sp_Graphics2D(new Graphics2D());
				//++spGraph2D;


				if(texRead.readLineSkipOverSolidus()==false)
				{
					cout<<"–â‘è”­¶"<<endl;	
					//reset();
					return;
				}
				pLine=texRead.getLine();
				pos=0;

				getNextStringToComma(inputC,pLine,&pos);
				str=inputC;

				spGraph2D->initialize(str.c_str());

				getNextStringToComma(inputC,pLine,&pos);
				str=inputC;

				spGraph2D->setName(str.c_str());

				m_GraphList_BackGroundObject.push_back(spGraph2D);
//				++spGraph2D;
			}
		}
	}
}



void Map::initializeGraph_BackGroundObject(char* filePath)
{
	TexRead texRead(filePath);
	if(texRead.isLoaded())
	{
		cout<<"“Ç‚Ýž‚Ý¬Œ÷ initializeGraphList_Road"<<filePath<<endl;

		string str;

		char inputC[STRING_LENGTH];
		char *pLine;

		int pos=0;
		
		if(texRead.readLineSkipOverSolidus()==false)
		{
			cout<<"–â‘è”­¶"<<endl;	
			//reset();
			return;
		}
		pLine=texRead.getLine();
		pos=0;

		getNextStringToComma(inputC,pLine,&pos);
		str=inputC;

		if(str!="<max>")
		{
			return;
		}
		getNextStringToComma(inputC,pLine,&pos);
		m_backGroundObjectMax=atoi(inputC);

		if(m_backGroundObjectMax>0)
		{
			if(m_BackGroundObject_Array==NULL)
			{
				m_BackGroundObject_Array=new backGroundObject[m_backGroundObjectMax];
				if(m_BackGroundObject_Array!=NULL)
				{
					for(int i=0;i<m_backGroundObjectMax;i++)
					{
						if(texRead.readLineSkipOverSolidus()==false)
						{
							cout<<"–â‘è”­¶"<<endl;	
							//reset();
							return;
						}
						pLine=texRead.getLine();
						pos=0;
						getNextStringToComma(inputC,pLine,&pos);
						str=inputC;

//						++(m_BackGroundObject_Array[i].spGraph);
						m_BackGroundObject_Array[i].spGraph=getGraph_BackGroundObjectNamed(str.c_str());

						getNextStringToComma(inputC,pLine,&pos);
						str=inputC;
						m_BackGroundObject_Array[i].x=atoi(str.c_str());
						
						getNextStringToComma(inputC,pLine,&pos);
						str=inputC;
						m_BackGroundObject_Array[i].y=atoi(str.c_str());

						getNextStringToComma(inputC,pLine,&pos);
						str=inputC;
						m_BackGroundObject_Array[i].scrollSpeed=atof(str.c_str());

						getNextStringToComma(inputC,pLine,&pos);
						str=inputC;
						m_BackGroundObject_Array[i].exrate=atof(str.c_str());

					}
				}
			
			}
		}
	}

}

sp_Graphics2D Map::getGraph_BackGroundObjectNamed(const char* name)
{
	sp_Graphics2D r;
//	++r;
	string name_s=name;

	SpGraph2DList::iterator p=m_GraphList_BackGroundObject.begin();
	
	if(!(m_GraphList_BackGroundObject.empty()))
	while(p!=m_GraphList_BackGroundObject.end())
	{
		if ((*p)->getName()==name_s)
		{
			return (*p);
			break;
		}
		else
		{
			p++;
	
		}
	}
//	++r;
	return r;

}






void Map::drawSet()
{

	//static double pal=0;
	//al+=0.1;
//	m_spDrawBuffer->DrawSet(m_spGraphBackGround_0.getPointerReference(),0,0,0,false);

	if(m_spDrawBuffer.get()!=NULL&&m_spDrawBufferFarEnd.get()!=NULL&&m_spDrawBufferFront.get()!=NULL)
	{
		for(int i=0;i<m_roadMax;i++)
		{
			if(m_pSpGraph_Road_Array!=NULL)
			{
				if(m_pSpGraph_Road_Array[i].get()!=NULL)
				{
					m_spDrawBufferFarEnd->DrawSet(m_pSpGraph_Road_Array[i].get(),0,MOVE_MIN_X+(i*ROAD_SIZE_X)-m_ScrollX,458,0,false);
				}
			}

		}
		
		for(int i=0;i<m_backGroundObjectMax;i++)
		{
			if(m_BackGroundObject_Array!=NULL)
			{
				if(m_BackGroundObject_Array[i].spGraph.get()!=NULL)
				{
					//int setX=(WINDOW_WIDTH/2)+(i*WINDOW_WIDTH);
					double x=0;

					if(m_BackGroundObject_Array[i].scrollSpeed<1&&m_BackGroundObject_Array[i].scrollSpeed>=0)
					{
						x=((1.0-m_BackGroundObject_Array[i].scrollSpeed)*(m_BackGroundObject_Array[i].x-(m_ScrollX+(WINDOW_WIDTH/2))));
					}
				//	m_spDrawBuffer->DrawSetCenterBottom(m_spGraphBackGround_0.getPointerReference(),0,static_cast<int>(setX-(scrollX+x)),300,ex,1.0,false);

					
					//m_spDrawBufferFarEnd->setCellBlend(BLEND_SUB,static_cast<int>(pal));

					m_spDrawBuffer->DrawSetCenterBottom(m_BackGroundObject_Array[i].spGraph.get()
					,0,static_cast<int>(m_BackGroundObject_Array[i].x-(m_ScrollX+x))
					,BACK_GROUND_OBJECT_BASE_Y-m_BackGroundObject_Array[i].y,m_BackGroundObject_Array[i].y,0,m_BackGroundObject_Array[i].exrate,false);
					
					//m_spDrawBufferFarEnd->resetCellBlend();
				}
			}
		}


		for(int i=0;i<m_FrontObjectMax;i++)
		{
			if(m_FrontObject_Array!=NULL)
			{
				if(m_FrontObject_Array[i].spGraph.get()!=NULL)
				{
					//int setX=(WINDOW_WIDTH/2)+(i*WINDOW_WIDTH);
					double x=0;

					if(m_FrontObject_Array[i].scrollSpeed>=0)
					{
						x=((1.0-m_FrontObject_Array[i].scrollSpeed)*(m_FrontObject_Array[i].x-(m_ScrollX+(WINDOW_WIDTH/2))));
					}
				//	m_spDrawBuffer->DrawSetCenterBottom(m_spGraphFront_0.getPointerReference(),0,static_cast<int>(setX-(scrollX+x)),300,ex,1.0,false);

					
					//m_spDrawBufferFarEnd->setCellBlend(BLEND_SUB,static_cast<int>(pal));

					m_spDrawBufferFront->DrawSetCenterBottom(m_FrontObject_Array[i].spGraph.get()
					,0,static_cast<int>(m_FrontObject_Array[i].x-(m_ScrollX+x))
					,FRONT_OBJECT_BASE_Y-m_FrontObject_Array[i].y,m_FrontObject_Array[i].y,0,m_FrontObject_Array[i].exrate,false);
					
					//m_spDrawBufferFarEnd->resetCellBlend();
				}
			}
		}
	}



	if(m_spGraphBackGroundFarEnd.get()!=NULL)
	{
		int x=static_cast<int>(0.09*m_ScrollX);
		while(x>WINDOW_WIDTH)
		{
			x-=WINDOW_WIDTH;
		}
		while(x<0)
		{
			x+=WINDOW_WIDTH;
		}

		m_spDrawBufferFarEnd->DrawSetLeftBottom(m_spGraphBackGroundFarEnd.get(),0,-x,458,1000,0,1.0,false);
		m_spDrawBufferFarEnd->DrawSetLeftBottom(m_spGraphBackGroundFarEnd.get(),0,-x+WINDOW_WIDTH,458,1000,0,1.0,false);

	}

}











void Map::initializeGraphList_FrontObject(char *filePath)
{
	TexRead texRead(filePath);
	if(texRead.isLoaded())
	{
		cout<<"“Ç‚Ýž‚Ý¬Œ÷ initializeGraphList_FrontObject"<<filePath<<endl;

		string str;

		char inputC[STRING_LENGTH];
		char *pLine;

		int pos=0;
		
		if(texRead.readLineSkipOverSolidus()==false)
		{
			cout<<"–â‘è”­¶"<<endl;	
			//reset();
			return;
		}
		pLine=texRead.getLine();
		pos=0;

		getNextStringToComma(inputC,pLine,&pos);
		str=inputC;

		if(str!="<max>")
		{
			return;
		}
		getNextStringToComma(inputC,pLine,&pos);
		m_FrontObjectTypeMax=atoi(inputC);

		if(m_FrontObjectTypeMax>=0)
		{
			
			for(int i=0;i<m_FrontObjectTypeMax;i++)
			{

				sp_Graphics2D spGraph2D;
				spGraph2D=sp_Graphics2D(new Graphics2D());
//				++spGraph2D;


				if(texRead.readLineSkipOverSolidus()==false)
				{
					cout<<"–â‘è”­¶"<<endl;	
					//reset();
					return;
				}
				pLine=texRead.getLine();
				pos=0;

				getNextStringToComma(inputC,pLine,&pos);
				str=inputC;

				spGraph2D->initialize(str.c_str());

				getNextStringToComma(inputC,pLine,&pos);
				str=inputC;

				spGraph2D->setName(str.c_str());

				m_GraphList_FrontObject.push_back(spGraph2D);
//				++spGraph2D;
			}
		}
	}
}



void Map::initializeGraph_FrontObject(char* filePath)
{
	TexRead texRead(filePath);
	if(texRead.isLoaded())
	{
		cout<<"“Ç‚Ýž‚Ý¬Œ÷ initializeGraphList_Road"<<filePath<<endl;

		string str;

		char inputC[STRING_LENGTH];
		char *pLine;

		int pos=0;
		
		if(texRead.readLineSkipOverSolidus()==false)
		{
			cout<<"–â‘è”­¶"<<endl;	
			//reset();
			return;
		}
		pLine=texRead.getLine();
		pos=0;

		getNextStringToComma(inputC,pLine,&pos);
		str=inputC;

		if(str!="<max>")
		{
			return;
		}
		getNextStringToComma(inputC,pLine,&pos);
		m_FrontObjectMax=atoi(inputC);

		if(m_FrontObjectMax>0)
		{
			if(m_FrontObject_Array==NULL)
			{
				m_FrontObject_Array=new backGroundObject[m_FrontObjectMax];
				if(m_FrontObject_Array!=NULL)
				{
					for(int i=0;i<m_FrontObjectMax;i++)
					{
						if(texRead.readLineSkipOverSolidus()==false)
						{
							cout<<"–â‘è”­¶"<<endl;	
							//reset();
							return;
						}
						pLine=texRead.getLine();
						pos=0;
						getNextStringToComma(inputC,pLine,&pos);
						str=inputC;

//						++(m_FrontObject_Array[i].spGraph);
						m_FrontObject_Array[i].spGraph=getGraph_FrontObjectNamed(str.c_str());

						getNextStringToComma(inputC,pLine,&pos);
						str=inputC;
						m_FrontObject_Array[i].x=atoi(str.c_str());
						
						getNextStringToComma(inputC,pLine,&pos);
						str=inputC;
						m_FrontObject_Array[i].y=atoi(str.c_str());

						getNextStringToComma(inputC,pLine,&pos);
						str=inputC;
						m_FrontObject_Array[i].scrollSpeed=atof(str.c_str());

						getNextStringToComma(inputC,pLine,&pos);
						str=inputC;
						m_FrontObject_Array[i].exrate=atof(str.c_str());

					}
				}
			
			}
		}
	}

}

sp_Graphics2D Map::getGraph_FrontObjectNamed(const char* name)
{
	sp_Graphics2D r;
//	++r;
	string name_s=name;

	SpGraph2DList::iterator p=m_GraphList_FrontObject.begin();
	
	if(!(m_GraphList_FrontObject.empty()))
	while(p!=m_GraphList_FrontObject.end())
	{
		if ((*p)->getName()==name_s)
		{
			r= (*p);
			break;
		}
		else
		{
			p++;
	
		}
	}
	
	return r;

}



