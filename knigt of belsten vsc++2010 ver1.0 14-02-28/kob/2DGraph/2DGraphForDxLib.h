//////////////////////
//	2013/7/18-7/19
//	藤井 康輔
//	Kousuke Fujii
/////////////////////
#include "..\defines.h"
//#include "..\shared_ptr.h"

#ifndef FILE_PATH_LENGTH
#define FILE_PATH_LENGTH 128 //ファイルパスの長さ
#endif



#ifndef INCLUDE_GRAPHICS_2D
#define INCLUDE_GRAPHICS_2D

class Graphics2D;

typedef boost::shared_ptr<Graphics2D> sp_Graphics2D;//スマートポインタ

//initialize shared_ptr Graphics
//spGraphで宣言されたオブジェクトに対してnewでメモリ割り当て後、初期化関数を呼び出す
//メモリ割り当てから画像ロードまで同時に行いたい場合に使用
extern void initializeSpGraph(sp_Graphics2D* pSpGraph,char* filePath);
extern void initializeSpGraph(sp_Graphics2D* pSpGraph,char* filePath,int max,int xSize,int ySize,int xNum,int yNum);


class Graphics2D
{
private:

	//画像ハンドル配列の数
	int m_max;

	//loadDivGraphで分割読み込みするとき一つ当たりの画像サイズ
	int m_xSize;
	int m_ySize;

	//loadDivGraphで分割読み込みする時の縦横分割数
	int m_xNum;
	int m_yNum;

	//初期化されたかどうか
	bool m_bIsInitialized;

	//ファイルパス
	char m_filePath[FILE_PATH_LENGTH];

	//ハンドル配列格納用
	int * m_pHandleBuff;

	string m_name;

public :

	Graphics2D();
	~Graphics2D();

	void reset();//デフォルトコンストラクタで初期化された時と同じ状態にする

	//分割して読み込む場合
	void initialize(const char* filePath,int max,int xSize,int ySize,int xNum,int yNum);
	
	//分割読み込みを使用しない場合
	void initialize(const char* filePath);

	int getHandle(int num)const;//目的のハンドルを取得する
	
	void setName(const char *pC){m_name=pC;}
	string getName()const{return m_name;}


//以下インライン関数定義 単純に値を取得するためだけのもの
	int getMax()const{return m_max;}
	int getXSize()const{return m_xSize;}
	int getYSize()const{return m_ySize;}
	int getXNum()const{return m_xNum;}
	int getYNum()const{return m_yNum;}
	bool isInitialized()const{return m_bIsInitialized;}//初期化されているか


};

#endif