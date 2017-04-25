#include "hitArea.h"

#include <string>

#include "../log.h"

bool CheckHit_Circle(int x0,int y0,circle circle0,bool useTurnX0,
					 int x1,int y1,circle circle1,bool useTurnX1)
{
	//円同士の当り判定を行います
	//接触しているならtrue


	//画像が左右反転しているか
	if(useTurnX0)
	{
		circle0.m_x*=-1;
	}
	
	if(useTurnX1)
	{
		circle1.m_x*=-1;
	}

	int centerX0=x0+circle0.m_x;
	int centerY0=y0+circle0.m_y;

	int centerX1=x1+circle1.m_x;
	int centerY1=y1+circle1.m_y;

	int distanceX=(centerX0-centerX1);
	int distanceY=(centerY0-centerY1);


	//三平方の定理を使って円の中心同士の距離を比較します

	int distance =(distanceX*distanceX)+(distanceY*distanceY);//実際の距離  正確には距離の二乗
	int checkDistance=(circle0.m_radius+circle1.m_radius)*(circle0.m_radius+circle1.m_radius);//最低限触れている距離 正確には距離の二乗

	if(distance<checkDistance)
	{
		return true;
	}
	else 
	{
		return false;
	}

}

//----------------------------------------------------------------------

HitArea::HitArea()
{
	//コンストラクタ

	m_circleMax=0;
	m_pCircle_Array=NULL;
	strcpy_s(m_filePath,"none");
	m_bIsInitialized=false;
}

//----------------------------------------------------------------------
HitArea::~HitArea()
{	
	//デストラクタです
	SAFE_DELETE_ARRAY(m_pCircle_Array);
}

//------------------------------------------------------------------------
void HitArea::reset()
{
	//メモリの解放を行いすべての変数をリセットします
	SAFE_DELETE_ARRAY(m_pCircle_Array);
	
	m_circleMax=0;
	strcpy_s(m_filePath,"none");
	m_bIsInitialized=false;
	m_bIsInitialized=false;
}

//---------------------------------------------------------------------

circle HitArea::getCircle(int i)
{
	//指定された添え字の円データを返します
	//失敗時にはすべて値が0のものを返します

	circle r;
	if(i>=0&&i<m_circleMax&&m_bIsInitialized)
	{
		r=m_pCircle_Array[i];
	}

	return r;

}

//--------------------------------------------------------------------

void HitArea::initialize(const char* filePath)
{
	//初期化関数


	strcpy_s(m_filePath,filePath);
	
	fout_log<<endl;
	fout_log<<"hitArea initialize"<<endl;
	TexRead texRead(m_filePath);

	if(!(texRead.isLoaded()))
	{
		return;
	}
	
	texRead.setFirst();	
	
	string str;

	char inputC[STRING_LENGTH];
	char* pLine;

	int pos=0;//今読んでいる位置
	pLine=texRead.readLine();
	
	
	getNextStringToComma(inputC,pLine,&pos);//次の文字列をinputCにコピーする　pLine[pos]から','または'\n'まで　

	str=inputC;

	if(str!="<aMax>")//内容に間違いがある場合
	{	
		return;	
	}

	
	//円の数を読み出す
	getNextStringToComma(inputC,pLine,&pos);//次の文字列をinputCにコピーする　pLine[pos]から','または'\n'まで　

	m_circleMax=atoi(inputC);	//円の数を格納

	//メモリ割り当て
	if(m_circleMax>0 && m_pCircle_Array==NULL)
	{
		m_pCircle_Array=new circle[m_circleMax];
	}
	
	for(int i=0;i<m_circleMax;i++)
	{
		//ラインの読み出し及び読み飛ばし行の判断
		
		//texReadのLineを更新　読み出しの過程でファイルが終了していないかのチェック
		if(texRead.readLineSkipOverSolidus()==false)
		{
			cout<<"問題発生"<<endl;	
			reset();
			return;
		}
		pLine=texRead.getLine();
		pos=0;
	
		int data[3];//x,y,rのデータを格納する

		for(int j=0;j<3;j++)
		{
			getNextStringToComma(inputC,pLine,&pos);//次の文字列をinputCにコピーする　pLine[pos]から','または'\n'まで　

			data[j]=atoi(inputC);
		}

		//構造体にデータを格納する
		m_pCircle_Array[i].m_x=data[0];
		m_pCircle_Array[i].m_y=data[1];
		m_pCircle_Array[i].m_radius=data[2];	
	
	}

	m_bIsInitialized=true;

}

//-----------------------------------

void HitArea::show()
{
	//デバッグ用の関数
	//メンバ変数の値をコンソール窓に書き出します

	fout_log<<m_filePath<<endl;
	fout_log<<"max :"<<m_circleMax<<endl;


	for(int i=0;i<m_circleMax;i++)
	{
		fout_log<< i<<" :"<<m_pCircle_Array[i].m_x<<","<<m_pCircle_Array[i].m_y<<","<<m_pCircle_Array[i].m_radius<<endl;

	}

}