#include "actorData.h"


//---------------------------------------
ActorData::ActorData()
{
	//コンストラクタ
	//値を入れるだけの初期化をする
	//ゲーム用の初期化はinitializeで行う
	//initializeはやたら長いのでこのファイルの一番下に書いています

	m_pGraph2D_Arr=NULL;
	m_pGraph2D_Shadow_Arr=NULL;

	m_pFilePathForGraph_Arr=NULL;
	m_pFilePathForGraph_Shadow_Arr=NULL;

	m_pGraphPatternData_Arr=NULL;

	m_name="noName";

	m_filePathForHitArea="nodata";
	m_filePath="nodata";

	m_GraphMax=0;
	m_modeMax=0;

	m_sizeX=0;
	m_sizeZ=0;
	
	m_maxHp=0;
	m_speedLR=0;
	m_speedZ=0;

	m_atackRangeZ=0;
	m_atackPoint=0;
	m_defencePoint=0;
	
	m_bIsInitialized=false;		
}

//---------------------------------------

ActorData::~ActorData()
{
	//デストラクタ
	//メンバポインタ変数にnewで割り当てたメモリを開放する

	cout<<"デストラクタ ActorData,"<<m_name<<","<<m_filePath<<endl;

	SAFE_DELETE_ARRAY(m_pGraph2D_Arr);
	SAFE_DELETE_ARRAY(m_pFilePathForGraph_Arr);
	SAFE_DELETE_ARRAY(m_pGraphPatternData_Arr);
	
	m_hitAreaSet.reset();
	m_bIsInitialized=false;

	cout<<"-デストラクタ ActorData end,"<<m_name<<","<<m_filePath<<endl;
	m_name="noName";
	m_filePathForHitArea="nodata";
	m_filePath="nodata";
}

//----------------------------------

void ActorData::reset()
{	
	//メンバポインタ変数にnewで割り当てたメモリを開放し
	//コンストラクタで作られた時と同じ状態に戻す

	SAFE_DELETE_ARRAY(m_pGraph2D_Arr);
	SAFE_DELETE_ARRAY(m_pFilePathForGraph_Arr);
	SAFE_DELETE_ARRAY(m_pGraphPatternData_Arr);

	cout<<"reset,"<<m_name<<","<<m_filePath<<endl;

	m_name="noName";

	m_filePathForHitArea="nodata";
	m_filePath="nodata";

	m_GraphMax=0;
	m_modeMax=0;

	m_sizeX=0;
	m_sizeZ=0;
	
	m_maxHp=0;
	m_speedLR=0;
	m_speedZ=0;

	m_atackRangeZ=0;
	m_atackPoint=0;
	m_defencePoint=0;

	m_hitAreaSet.reset();

	m_bIsInitialized=false;
}

//---------------------------------------

GraphPatternData ActorData::getGraphPatternData(int i)const
{
	//グラフィックパターンデータを返します
	//グラフィックパターンデータには各アニメーションモードの画像を表示するための　
	//(何枚目のグラフィックシートを使用するか,画像インデックス,アニメーションの最大数)
	//の各項目が保存されています
	
	//失敗時にはすべて0の画像を返します

	GraphPatternData r;
	if(m_pGraphPatternData_Arr!=NULL)
	{
		if(i>=0&&i<m_modeMax)
		{
			r= m_pGraphPatternData_Arr[i];
		}
	}
	return r;	
}


//------------------------------------------

Graphics2D* ActorData::getPGraph(int i)
{
	//キャラクターの画像へのポインタを返します
	//引数のiはそのキャラクターで何枚目の画像かを指定します
	//失敗時にはnullポインタを返します
	//NULLポインタに頼るのはよくないとの話なので参照を返すようにリファクタリング予定
	
	if(m_pGraph2D_Arr!=NULL)
	{
		if(i>=0&&i<m_GraphMax)
		{
			return &m_pGraph2D_Arr[i];
		}
	}

	return NULL;
}

//--------------------------------------------

Graphics2D* ActorData::getPGraphShadow(int i)
{
	//影の画像へのポインタを返します
	//引数のiはそのキャラクターで何枚目の画像かを指定します
	//失敗時にはnullポインタを返します
	//NULLポインタに頼るのはよくないとの話なので参照を返すようにリファクタリング予定

	if(m_pGraph2D_Shadow_Arr!=NULL)
	{
		if(i>=0&&i<m_GraphMax)
		{
			return &m_pGraph2D_Shadow_Arr[i];
		}
	}
	
	return NULL;
}

//--------------------------------------------


int ActorData::getGraphMaxInSheet(int i)const
{
	//指定した番号のグラフィックシートに
	//何コマ分のアニメーションが記録してあるかを返します
	//範囲外なら0を返します

	int r=0;

	if(i>=0&&i<m_GraphMax)
	{
		r=m_pGraph2D_Arr[i].getMax();
	}

return r;
}

//-----------------------------------
void ActorData::show()
{
	//デバッグに使った関数です
	//コンソール窓にオブジェクトの保持しているデータをすべて書き出します

	cout<<"actorData"<<endl;
	cout<<m_filePath<<endl;
	cout<<"g max :"<<m_GraphMax<<endl;

	if(m_pFilePathForGraph_Arr)
	{
		cout<<"graphPath"<<endl;
		for(int i=0;i<m_GraphMax;i++)
		{
			cout<<i<<" : "<<m_pFilePathForGraph_Arr[i]<<endl;
		}
	}
	cout<<"m max :"<<m_modeMax<<endl;

	if(m_pGraphPatternData_Arr)
	{
		cout<<"patternData"<<endl;
		for(int i=0;i<m_modeMax;i++)
		{
			cout<<i<<" : "<<m_pGraphPatternData_Arr[i].m_sheetNum<<",";
			cout<<m_pGraphPatternData_Arr[i].m_index<<",";
			cout<<m_pGraphPatternData_Arr[i].m_max<<endl;
		}
	}

}


//--------------------------------------------------------------------

void ActorData::initialize(const char *filePath)
{
	//すべてのメンバ変数を初期化します
	//csvファイルを開き各項目を読み出しては設定の繰り返しです
	//メモリの割り当てが必要なタイミングには割り当てを行います
	//やたら長いのは設定項目がいっぱいあるからです

	//ここのコメントを読んだ方へ
	//少しでもスマートになる書き方、またアルゴリズムをご存知でしたらご享受ください



	TexRead texRead(filePath);

	if(texRead.isLoaded())
	{
		m_filePath=filePath;
		cout<<"読み込み成功 ActorData initialize()"<<m_filePath.c_str()<<endl;
	
		string str;

		char inputC[STRING_LENGTH];
		char* pLine;

		int pos=0;//今読んでいる位置

//名前を読みだす
		if(texRead.readLineSkipOverSolidus()==false)
		{
			cout<<"問題発生"<<endl;	
			reset();
			return;
		}
			pLine=texRead.getLine();
			pos=0;

		getNextStringToComma(inputC,pLine,&pos);//次の文字列をinputCにコピーする　pLine[pos]から','または'\n'まで　
	
		str=inputC;

		if(str!="<name>")//内容に間違いがある場合
		{	
			reset();
			return;	
		}

		getNextStringToComma(inputC,pLine,&pos);//次の文字列をinputCにコピーする　pLine[pos]から','または'\n'まで　

		m_name=inputC;

		cout<<m_name.c_str()<<endl;

//名前の読み出し終了

//グラフィックのシート数を読みだす

//texReadのLineを更新　読み出しの過程でファイルが終了していないかのチェック
		if(texRead.readLineSkipOverSolidus()==false)
		{
			cout<<"問題発生"<<endl;	
			reset();
			return;
		}
			pLine=texRead.getLine();
			pos=0;

		getNextStringToComma(inputC,pLine,&pos);//次の文字列をinputCにコピーする　pLine[pos]から','または'\n'まで　
	
		str=inputC;

		if(str!="<gMax>")//内容に間違いがある場合
		{	
			reset();
			return;	
		}

		getNextStringToComma(inputC,pLine,&pos);//次の文字列をinputCにコピーする　pLine[pos]から','または'\n'まで　

		m_GraphMax=atoi(inputC);
//グラフィックシート数の読み出し終了


//使用するモード数の読み出し

		//texReadのLineを更新　読み出しの過程でファイルが終了していないかのチェック
		if(texRead.readLineSkipOverSolidus()==false)
		{
			cout<<"問題発生"<<endl;	
			reset();
			return;
		}
		pLine=texRead.getLine();
		pos=0;
		
		getNextStringToComma(inputC,pLine,&pos);//次の文字列をinputCにコピーする　pLine[pos]から','または'\n'まで　

		str=inputC;

		if(str!="<mMax>")//内容に間違いがある場合
		{	
			reset();
			return;	
		}

		getNextStringToComma(inputC,pLine,&pos);//次の文字列をinputCにコピーする　pLine[pos]から','または'\n'まで　

		m_modeMax=atoi(inputC);

//使用するモード数の読み出し終了

//最大HPの読み出し

		//texReadのLineを更新　読み出しの過程でファイルが終了していないかのチェック
		if(texRead.readLineSkipOverSolidus()==false)
		{
			cout<<"問題発生"<<endl;	
			reset();
			return;
		}
		pLine=texRead.getLine();
		pos=0;
		
		getNextStringToComma(inputC,pLine,&pos);//次の文字列をinputCにコピーする　pLine[pos]から','または'\n'まで　

		str=inputC;

		if(str!="<maxHp>")//内容に間違いがある場合
		{	
			reset();
			return;	
		}

		getNextStringToComma(inputC,pLine,&pos);//次の文字列をinputCにコピーする　pLine[pos]から','または'\n'まで　

		m_maxHp=atoi(inputC);

//最大HPの読み出し終了


//攻撃範囲x軸　

		//texReadのLineを更新　読み出しの過程でファイルが終了していないかのチェック
		if(texRead.readLineSkipOverSolidus()==false)
		{
			cout<<"問題発生"<<endl;	
			reset();
			return;
		}
		pLine=texRead.getLine();
		pos=0;
		
		getNextStringToComma(inputC,pLine,&pos);//次の文字列をinputCにコピーする　pLine[pos]から','または'\n'まで　

		str=inputC;

		if(str!="<atackRangeX>")//内容に間違いがある場合
		{	
			reset();
			return;	
		}

		getNextStringToComma(inputC,pLine,&pos);//次の文字列をinputCにコピーする　pLine[pos]から','または'\n'まで　

		m_atackRangeX=atoi(inputC);

//攻撃範囲xの読み出し終了

//攻撃範囲z軸　

		//texReadのLineを更新　読み出しの過程でファイルが終了していないかのチェック
		if(texRead.readLineSkipOverSolidus()==false)
		{
			cout<<"問題発生"<<endl;	
			reset();
			return;
		}
		pLine=texRead.getLine();
		pos=0;
		
		getNextStringToComma(inputC,pLine,&pos);//次の文字列をinputCにコピーする　pLine[pos]から','または'\n'まで　

		str=inputC;

		if(str!="<atackRangeZ>")//内容に間違いがある場合
		{	
			reset();
			return;	
		}

		getNextStringToComma(inputC,pLine,&pos);//次の文字列をinputCにコピーする　pLine[pos]から','または'\n'まで　

		m_atackRangeZ=atoi(inputC);

//攻撃範囲ｚの読み出し終了

//攻撃

		//texReadのLineを更新　読み出しの過程でファイルが終了していないかのチェック
		if(texRead.readLineSkipOverSolidus()==false)
		{
			cout<<"問題発生"<<endl;	
			reset();
			return;
		}
		pLine=texRead.getLine();
		pos=0;
		
		getNextStringToComma(inputC,pLine,&pos);//次の文字列をinputCにコピーする　pLine[pos]から','または'\n'まで　

		str=inputC;

		if(str!="<atackPoint>")//内容に間違いがある場合
		{	
			reset();
			return;	
		}

		getNextStringToComma(inputC,pLine,&pos);//次の文字列をinputCにコピーする　pLine[pos]から','または'\n'まで　

		m_atackPoint=atoi(inputC);

//攻撃

//防御
		//texReadのLineを更新　読み出しの過程でファイルが終了していないかのチェック
		if(texRead.readLineSkipOverSolidus()==false)
		{
			cout<<"問題発生"<<endl;	
			reset();
			return;
		}
		pLine=texRead.getLine();
		pos=0;
		
		getNextStringToComma(inputC,pLine,&pos);//次の文字列をinputCにコピーする　pLine[pos]から','または'\n'まで　

		str=inputC;

		if(str!="<defencePoint>")//内容に間違いがある場合
		{	
			reset();
			return;	
		}

		getNextStringToComma(inputC,pLine,&pos);//次の文字列をinputCにコピーする　pLine[pos]から','または'\n'まで　

		m_defencePoint=atoi(inputC);

//防御

//移動スピードの読み出し

		//texReadのLineを更新　読み出しの過程でファイルが終了していないかのチェック
		if(texRead.readLineSkipOverSolidus()==false)
		{
			cout<<"問題発生"<<endl;	
			reset();
			return;
		}
		pLine=texRead.getLine();
		pos=0;
		
		getNextStringToComma(inputC,pLine,&pos);//次の文字列をinputCにコピーする　pLine[pos]から','または'\n'まで　

		str=inputC;

		if(str!="<speedLR>")//内容に間違いがある場合
		{	
			reset();
			return;	
		}

		getNextStringToComma(inputC,pLine,&pos);//次の文字列をinputCにコピーする　pLine[pos]から','または'\n'まで　

		m_speedLR=atof(inputC);

//移動スピードの読み出し終了

//使用するモード数の読み出し

//texReadのLineを更新　読み出しの過程でファイルが終了していないかのチェック
		if(texRead.readLineSkipOverSolidus()==false)
		{
			cout<<"問題発生"<<endl;	
			reset();
			return;
		}
		pLine=texRead.getLine();
		pos=0;
		
		getNextStringToComma(inputC,pLine,&pos);//次の文字列をinputCにコピーする　pLine[pos]から','または'\n'まで　

		str=inputC;

		if(str!="<speedZ>")//内容に間違いがある場合
		{	
			reset();
			return;	
		}

		getNextStringToComma(inputC,pLine,&pos);//次の文字列をinputCにコピーする　pLine[pos]から','または'\n'まで　

		m_speedZ=atof(inputC);

//使用するモード数の読み出し終了

//あたり判定のデータファイルのパスの読み出し

		//texReadのLineを更新　読み出しの過程でファイルが終了していないかのチェック
		if(texRead.readLineSkipOverSolidus()==false)
		{
			cout<<"問題発生"<<endl;	
			reset();
			return;
		}
		pLine=texRead.getLine();
		pos=0;
		
		getNextStringToComma(inputC,pLine,&pos);

		str=inputC;

		if(str!="<hPath>")//内容に間違いがある場合
		{	
			reset();
			return;	
		}

		getNextStringToComma(inputC,pLine,&pos);//次の文字列をinputCにコピーする　pLine[pos]から','または'\n'まで　

		m_filePathForHitArea=inputC;

//あたり判定のデータファイルのパスの読み出し終了

//あたり判定(攻撃エリア)のデータファイルのパスの読み出し

		//texReadのLineを更新　読み出しの過程でファイルが終了していないかのチェック
		if(texRead.readLineSkipOverSolidus()==false)
		{
			cout<<"問題発生"<<endl;	
			reset();
			return;
		}
		pLine=texRead.getLine();
		pos=0;
		
		getNextStringToComma(inputC,pLine,&pos);

		str=inputC;

		if(str!="<aPath>")//内容に間違いがある場合
		{	
			reset();
			return;	
		}

		getNextStringToComma(inputC,pLine,&pos);//次の文字列をinputCにコピーする　pLine[pos]から','または'\n'まで　

		m_filePathForAtackArea=inputC;

//あたり判定(攻撃エリア)のデータファイルのパスの読み出し終了

//グラフィックのパスの読み出し
			
		//texReadのLineを更新　読み出しの過程でファイルが終了していないかのチェック
		if(texRead.readLineSkipOverSolidus()==false)
		{
			cout<<"問題発生"<<endl;	
			reset();
			return;
		}
		pLine=texRead.getLine();
		pos=0;

		getNextStringToComma(inputC,pLine,&pos);//次の文字列をinputCにコピーする　pLine[pos]から','または'\n'まで　

		str=inputC;

		if(str!="<gPath>")//内容に間違いがある場合
		{	
			reset();
			return;	
		}

		if(m_GraphMax>0&&m_pFilePathForGraph_Arr==NULL)//メモリ割り当て
		{
			m_pFilePathForGraph_Arr=new string[m_modeMax];
		}
		else 
		{
			reset();
			return;
		}

		if(m_pFilePathForGraph_Arr==NULL)//メモリ割り当てに失敗していないかのチェック
		{
			reset();
			return;
		}

		for(int i=0;i<m_GraphMax;i++)
		{
			//texReadのLineを更新　読み出しの過程でファイルが終了していないかのチェック
			if(texRead.readLineSkipOverSolidus()==false)
			{
				cout<<"問題発生"<<endl;	
				reset();
				return;
			}
			pLine=texRead.getLine();
			pos=0;

			getNextStringToComma(inputC,pLine,&pos);//次の文字列をinputCにコピーする　pLine[pos]から','または'\n'まで　
			
			m_pFilePathForGraph_Arr[i]=inputC;
		}


		//影のデータを読み出す

		if(m_GraphMax>0&&m_pFilePathForGraph_Shadow_Arr==NULL)//メモリ割り当て
		{
			m_pFilePathForGraph_Shadow_Arr=new string[m_modeMax];
		}
		else 
		{
			reset();
			return;
		}

		if(m_pFilePathForGraph_Shadow_Arr==NULL)//メモリ割り当てに失敗していないかのチェック
		{
			reset();
			return;
		}

		for(int i=0;i<m_GraphMax;i++)
		{
			//texReadのLineを更新　読み出しの過程でファイルが終了していないかのチェック
			if(texRead.readLineSkipOverSolidus()==false)
			{
				cout<<"問題発生"<<endl;	
				reset();
				return;
			}
			pLine=texRead.getLine();
			pos=0;

			getNextStringToComma(inputC,pLine,&pos);//次の文字列をinputCにコピーする　pLine[pos]から','または'\n'まで　
			
			m_pFilePathForGraph_Shadow_Arr[i]=inputC;
		}


//グラフィックのパス読み出し終了

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

		getNextStringToComma(inputC,pLine,&pos);//次の文字列をinputCにコピーする　pLine[pos]から','または'\n'まで　

		str=inputC;

		if(str!="<gpData>")//内容に間違いがある場合
		{	
			reset();
			return;	
		}

		if(m_modeMax>0&&m_pGraphPatternData_Arr==NULL)//メモリ割り当て
		{
			m_pGraphPatternData_Arr=new GraphPatternData[m_modeMax];
		}
		else 
		{
			reset();
			return;
		}

		if(m_pGraphPatternData_Arr==NULL)//メモリ割り当てに失敗していないかのチェック
		{
			reset();
			return;
		}

		for(int i=0;i<m_modeMax;i++)
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
	
			int data[3];//sheetNum index maxのデータを格納する


			for(int j=0;j<3;j++)
			{
				getNextStringToComma(inputC,pLine,&pos);//次の文字列をinputCにコピーする　pLine[pos]から','または'\n'まで　

				data[j]=atoi(inputC);
			}

			m_pGraphPatternData_Arr[i].m_sheetNum=data[0];
			m_pGraphPatternData_Arr[i].m_index=data[1];
			m_pGraphPatternData_Arr[i].m_max=data[2];
		}
//画像のロードに必要な値を読みだして画像のロードをする はじめ

		//texReadのLineを更新　読み出しの過程でファイルが終了していないかのチェック
		if(texRead.readLineSkipOverSolidus()==false)
		{
			cout<<"問題発生"<<endl;	
			reset();
			return;
		}
		pLine=texRead.getLine();
		pos=0;

		getNextStringToComma(inputC,pLine,&pos);//次の文字列をinputCにコピーする　pLine[pos]から','または'\n'まで　

		str=inputC;

		if(str!="<grData>")//内容に間違いがある場合
		{	
			reset();
			return;	
		}

		if(m_GraphMax>0&&m_pGraph2D_Arr==NULL)//メモリ割り当て
		{
			m_pGraph2D_Arr=new Graphics2D[m_GraphMax];
		}
		else 
		{
			reset();
			return;
		}

		if(m_pGraph2D_Arr==NULL)//メモリ割り当てに失敗していないかのチェック
		{
			reset();
			return;
		}

		if(m_GraphMax>0&&m_pGraph2D_Shadow_Arr==NULL)//メモリ割り当て
		{
			m_pGraph2D_Shadow_Arr=new Graphics2D[m_GraphMax];
		}
		else 
		{
			reset();
			return;
		}

		if(m_pGraph2D_Shadow_Arr==NULL)//メモリ割り当てに失敗していないかのチェック
		{
			reset();
			return;
		}

		for(int i=0;i<m_GraphMax;i++)
		{

			//texReadのLineを更新　読み出しの過程でファイルが終了していないかのチェック
			if(texRead.readLineSkipOverSolidus()==false)
			{
				cout<<"問題発生"<<endl;	
				reset();
				return;
			}
			pLine=texRead.getLine();
			pos=0;
	
			int data[5];//max xSize ySize xNum yNumのデータを格納する

			for(int j=0;j<5;j++)
			{
				getNextStringToComma(inputC,pLine,&pos);//次の文字列をinputCにコピーする　pLine[pos]から','または'\n'まで　

				data[j]=atoi(inputC);
			}
			
			m_pGraph2D_Arr[i].initialize(m_pFilePathForGraph_Arr[i].c_str(),data[0],data[1],data[2],data[3],data[4]);
			m_pGraph2D_Shadow_Arr[i].initialize(m_pFilePathForGraph_Shadow_Arr[i].c_str(),data[0],data[1],data[2],data[3],data[4]);
			if(!(m_pGraph2D_Arr[i].isInitialized()&&m_pGraph2D_Shadow_Arr[i].isInitialized()))
			{
				cout<<m_pFilePathForGraph_Arr[i]<<endl;
				cout<<m_pFilePathForGraph_Shadow_Arr[i]<<endl;
				reset();
				return;
			}

		}

//画像のロードに必要な値を読みだして画像のロードをする 終わり

//キャラクターのサイズをロードする　
	
		//texReadのLineを更新　読み出しの過程でファイルが終了していないかのチェック
		if(texRead.readLineSkipOverSolidus()==false)
		{
			cout<<"問題発生"<<endl;	
			reset();
			return;
		}
		pLine=texRead.getLine();
		pos=0;

		getNextStringToComma(inputC,pLine,&pos);//次の文字列をinputCにコピーする　pLine[pos]から','または'\n'まで　

		str=inputC;

		if(str!="<size>")//内容に間違いがある場合
		{	
			reset();
			return;	
		}

		//texReadのLineを更新　読み出しの過程でファイルが終了していないかのチェック
		if(texRead.readLineSkipOverSolidus()==false)
		{
			cout<<"問題発生"<<endl;	
			reset();
			return;
		}
		pLine=texRead.getLine();
		pos=0;
		getNextStringToComma(inputC,pLine,&pos);//次の文字列をinputCにコピーする　pLine[pos]から','または'\n'まで　
		m_sizeX=atoi(inputC);
		getNextStringToComma(inputC,pLine,&pos);//次の文字列をinputCにコピーする　pLine[pos]から','または'\n'まで　
		m_sizeZ=atoi(inputC);

//キャラクターのサイズをロードする終わり

		//当り判定のデータをロードする
		m_hitAreaSet.initialize(m_filePathForHitArea.c_str());
		if(!(m_hitAreaSet.isInitialized()))
		{
			reset();
			return;
		}
	
		if(m_filePathForAtackArea!="nodata")
		{
			m_atackAreaSet.initialize(m_filePathForAtackArea.c_str());//攻撃範囲のロード
			m_atackAreaSet.show();
		}
		
		m_bIsInitialized=true;

	}
	else 
	{
		cout<<"読み込みに失敗しました ActorData initialize()"<<filePath<<endl;
	}

}
