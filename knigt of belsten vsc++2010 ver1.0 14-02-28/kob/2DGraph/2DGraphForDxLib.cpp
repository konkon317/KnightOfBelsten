//////////////////////
//	2013/7/18-7/19
//	藤井 康輔
//	Kousuke Fujii
//  使用ライブラリ　DXライブラリ http://homepage2.nifty.com/natupaji/DxLib/
/////////////////////

#include "2DGraphForDxLib.h"
#include "DxLib.h"
#include "..\defines.h"

#include <iostream>
using namespace std;


//------------------------------------------------------------------------------

 void initializeSpGraph(sp_Graphics2D* pSpGraph,char* filePath)
 {	
	//initialize shared_ptr Graphics
	//spGraphで宣言されたオブジェクトに対してnewでメモリ割り当て後、初期化関数を呼び出す
	//メモリ割り当てから画像ロードまで同時に行いたい場合に使用
	
	if(pSpGraph->get()==NULL)
	{
		(*pSpGraph)=sp_Graphics2D(new Graphics2D());//オブジェクトをnewする
		
		if(pSpGraph->get()!=NULL)//問題なくnew されたか
		{
		
			(*pSpGraph)->initialize(filePath);//画像のロード
		}
	}
 }



 void initializeSpGraph(sp_Graphics2D* pSpGraph,char* filePath,int max,int xSize,int ySize,int xNum,int yNum)
 {		
	//initialize shared_ptr Graphics
	//spGraphで宣言されたオブジェクトに対してnewでメモリ割り当て後、初期化関数を呼び出す
	//メモリ割り当てから画像ロードまで同時に行いたい場合に使用
	//分割ロード用のオーバーロード

	if(pSpGraph->get()==NULL)
	{
		*pSpGraph=sp_Graphics2D(new Graphics2D());//オブジェクトをnewする
		
		if(pSpGraph->get()!=NULL)//問題なくnewされたか
		{
			(*pSpGraph)->initialize(filePath,max,xSize,ySize,xNum,yNum);//画像のロード
		}
	} 
 }

//以下Graphics2D メンバ関数
//----------------------------------------------------------------------------
//デフォルトコンストラクタ
Graphics2D::Graphics2D()
{
	m_max=0;			//画像ハンドル配列の数
	m_xSize=m_ySize;	//loadDivGraphで分割読み込みするとき一つ当たりの画像サイズ
	m_xNum=m_yNum;		//loadDivGraphで分割読み込みする時の縦横分割数
	m_bIsInitialized=false;//初期化されているか
	
	for(int i=0;i<FILE_PATH_LENGTH;i++)
	{
		m_filePath[i]='\0';//ファイルパス
	}
	m_pHandleBuff=NULL;
}

//----------------------------------------------------------------------------
//デストラクタ
Graphics2D::~Graphics2D()
{
	cout<<"2DGraphデストラクタ in "<<m_filePath<<endl;

	for(int i=0;i<m_max;i++)//画像を削除する
	{
		DeleteGraph(m_pHandleBuff[i]);
		m_pHandleBuff[i]=-1;
	}

	SAFE_DELETE_ARRAY(m_pHandleBuff);//メモリの解放後 nullを入れる
}

//---------------------------------------------------------------------------
//以下コンストラクタ、デストラクタ以外の関数定義
//----------------------------------------------------------------------------

void Graphics2D::reset()
{
	//デフォルトコンストラクタで初期化されたときと同じ状態へ

	for(int i=0;i<m_max;i++)//画像をメモリから削除する
	{
		DeleteGraph(m_pHandleBuff[i]);
		m_pHandleBuff[i]=-1;
	}

	SAFE_DELETE_ARRAY(m_pHandleBuff);//メモリの解放後 nullを入れる

	//諸数値をリセット
	m_max=0;		
	m_xSize=m_ySize;	
	m_xNum=m_yNum;		
	m_bIsInitialized=false;

	//ファイルパスのリセット
	for(int i=0;i<FILE_PATH_LENGTH;i++)
	{
		m_filePath[i]='\0';
	}
}

//----------------------------------------------------------------------

void Graphics2D::initialize(const char *filePath, int max, int xSize, int ySize, int xNum, int yNum)
{
	//初期化関数 DxLibのLoadDivGraph関数を使用する場合

	//cout<<"2DGraphInitialize in "<<filePath<<endl;
	if(!m_bIsInitialized)
	{
		strcpy_s(m_filePath,filePath);

		m_max=max;

		m_xSize=xSize;
		m_ySize=ySize;

		m_xNum=xNum;
		m_yNum=yNum;

		m_pHandleBuff=new int[m_max];//メモリ割り当
	
		if(!m_pHandleBuff)//メモリ割り当てに失敗した場合
		{
			m_max=0;//リセット関数で誤って画像削除部分に入らないようにするための処理
			//cout<<"メモリ割り当て失敗しました(loadDivGraph)"<<endl<<filePath<<endl;
			reset();
			return;
			//データリセットしリターン
		}

		//画像のロード
		int isLoaded=LoadDivGraph(m_filePath,m_max,m_xNum,m_yNum,m_xSize,m_ySize,m_pHandleBuff);

		if(isLoaded==-1)//エラー発生なら
		{
			//cout<<"画像読み込みに失敗しました(loadDivGraph)"<<endl<<filePath<<endl;
			reset();
			return;
			//データリセットしリターン
		}

		m_bIsInitialized=true;
	}
	else
	{
		//cout<<"すでに初期化されているインスタンスを初期化しようとしました(div)-"<<filePath<<endl;
	}
	//cout<<"2DGraphInitialize out "<<endl<<endl;
}

//----------------------------------------------------------------------

void Graphics2D::initialize(const char *filePath)
{
	//初期化関数 DxLibのLoadGraph関数を使用する場合
	
	//cout<<"2DGraphInitialize in "<<filePath<<endl;

	if(!m_bIsInitialized)
	{
	strcpy_s(m_filePath,filePath);

	m_max=1;
	
	m_xNum=1;
	m_yNum=1;

	m_pHandleBuff=new int[m_max];//メモリ割り当

	if(!m_pHandleBuff)//メモリ割り当てに失敗した場合
	{
		m_max=0;//リセット関数で誤って画像削除部分に入らないようにするための処理
		//cout<<"メモリ割り当てに失敗しました(loadGraph)"<<endl<<filePath<<endl;
		reset();
		return;
		//データリセットしリターン
	}
	m_pHandleBuff[0]=LoadGraph(m_filePath);//画像のロード
	
	if(m_pHandleBuff[0]==-1)//エラー発生の場合
	{
		//cout<<"画像読み込みに失敗しました(loadGraph)"<<endl<<filePath<<endl;
		reset();
		return;
		//データリセットしリターン
	}

	GetGraphSize(m_pHandleBuff[0],&m_xSize,&m_ySize);
	m_bIsInitialized=true;
	}
	else
	{
		//cout<<"すでに初期化されているインスタンスを初期化しようとしました-"<<filePath<<endl;
	}

	//cout<<"2DGraphInitialize out "<<endl<<endl;
}

//----------------------------------------------------------------------


int Graphics2D::getHandle(int num)const
{
	//ハンドルを取得するための関数
	if(m_bIsInitialized)
	{
		if(num>=0&&num<m_max)
		{
			return m_pHandleBuff[num];
		}
	}	
	return -1;//DXLIBで失敗を示す戻り値　
}

