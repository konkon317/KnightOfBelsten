#include "gameState.h"
#include "actor/actorData.h"
#include "../sound/soundForDxLib.h"

GameState::GameState()
{
	m_bIsInitialized=false;

	m_sequence=SEQ_LOGO;

	m_tBlendPar=0;
}

//------------------------------------------------

GameState::~GameState()
{
	m_lSpActors.clear();
	m_lSpActorData.clear();
}

//------------------------------------------------

void GameState::update()
{
	//描画以外のすべてのゲーム処理を行います

	switch(m_sequence)
	{

	case SEQ_LOGO:
		{
			m_tBlendPar+=static_cast<int>(0.3*m_tBlendPar)+1;
				
			if(m_tBlendPar>255)
			{
				m_tBlendPar=255;
				static int count=0;
				count++;
				
				if(count>80)
				{
					m_tBlendPar=0;
					count=0;

					m_spDrawBufferInterface->resetCellBlend();
					m_sequence=SEQ_INIT;
				}			
			}
		}
		break;

	case SEQ_INIT:
		{
			setUpGame();
			m_sequence=SEQ_TITLE;
		}
		break;

	case SEQ_TITLE:
		{
			static bool flag=false;

			if(m_pInput->PadCt(0,PAD_BUTTON_START)==1)
			{
				m_spDrawBufferInterface->setCellBlend(BLEND_ALPHA,0);
				flag=true;
			}

			if(flag)
			{
				if(m_spPlayer->getX()<100)
				{
					m_spPlayer->move(1,0,&m_lSpActors);
				}
				else
				{
					m_spPlayer->move(0,0,&m_lSpActors);
					if(m_spMap->getScrolX()<0)
					{
						m_spMap->fixScrollPosition(0);
					}
					else
					{
						m_spMap->setScrollMinX(0);
						m_spPlayer->setMoveMaxAndMIN(-1,0);
						flag=false;
						m_spDrawBufferInterface->resetCellBlend();
						m_sequence=SEQ_GAME;
						changeBgm("gameBgm");
					}			
				}
			}
		}
		break;

	case SEQ_GAME:
		{
			updateGame();

			if(m_spPlayer->isDead())
			{
				m_tBlendPar=0;
			
				stopBgm();
				playSound("gameOver");	
			
				m_sequence=SEQ_OVER;
			}

			if(isCleared())
			{
				m_spPlayer->move(0,0,&m_lSpActors);
				m_tBlendPar=0;
				stopBgm();
				playSound("gameClear");
				m_sequence=SEQ_CLEAR;
			}
		}
		break;

	case SEQ_OVER:
		{
			m_tBlendPar+=static_cast<int>(0.2*(m_tBlendPar)+1);

			if(m_tBlendPar>230)
			{
				m_tBlendPar=230;
				if(m_pInput->PadCt(0,PAD_BUTTON_START)==1)
				{

					m_sequence=SEQ_TEAM_MORIMOTO;
				}
			}
		}
		break;

	case SEQ_CLEAR:
		{
			m_tBlendPar+=static_cast<int>(0.2*(m_tBlendPar)+1);
			if(m_tBlendPar>230)
			{
				m_tBlendPar=230;
				if(m_pInput->PadCt(0,PAD_BUTTON_START)==1)
				{
					m_sequence=SEQ_TEAM_MORIMOTO;
				}
			}	
		}		
		break;	

	case SEQ_TEAM_MORIMOTO:
		{
			if(m_pInput->PadCt(0,PAD_BUTTON_START)==1)
			{
				m_sequence=SEQ_INIT;
			}
		
		}
		break;
	}
		
	//すべてのキャラクターのアニメーションの更新 
	for(listSpActor::iterator itSpActor =m_lSpActors.begin();itSpActor!=m_lSpActors.end();itSpActor++)
	{
		if((*itSpActor).get()!=NULL)
		{
			(*itSpActor)->updateAnimation();
		}
	}
}

//------------------------------------------------

void GameState::updateGame()
{
	//ゲーム本体の処理です
	//おもにプレイヤーの操作、攻撃
	//敵の思考、移動、攻撃
	//あたり判定、ダメージ処理、死亡判定
	//など　ゲームの大部分をこの関数から呼び出しています

	//　! 必ずsetDrawBufferを呼び出した後にこの関数を呼び出すこと

	//if(m_pInput->keyCt(KEY_INPUT_1)==1)m_spPlayer->kill();
	//if(m_pInput->keyCt(KEY_INPUT_2)==1)m_spPlayer->damage(1);
	
	//プレイヤーのアップデート
	m_spPlayer->update(m_pInput,&m_lSpActors);
	
	//
	if(!(m_lSpActors.empty()))	
	{	
		listSpActor::iterator itSpActor =m_lSpActors.begin();

		while(itSpActor!=m_lSpActors.end())
		{
			//すべての敵キャラクターに一連処理をさせるループです
			//for文を使用していないのはeraceを呼ぶことがあるため

			if((*itSpActor).get()!=NULL)
			{
				if(typeid(*(*itSpActor).get())==typeid(Enemy))
				{
					(*itSpActor)->update(m_spPlayer,&m_lSpActors);			
				
					if((*itSpActor)->isDead())
					{
						//死んでいるときの処理
					
						itSpActor=m_lSpActors.erase(itSpActor);		//.eraceは削除した要素の直後の要素へのイテレータを返すため　イテレータを++　する必要なし
																	//データから削除する
						if(m_lSpActors.empty())
						{
							break;
						}
						continue;
					}//else itSpActor++;	
				}
			}	
			itSpActor++;
		}
	}
	
	m_spPlayer->updateOldPosition();

	{	//この'{'はローカル変数 flagをスコープに閉じ込めるためのものです

		static bool flag=false;
	
		if(m_spPlayer->getX()>1024*4)//プレイヤーがボス部屋にいるかどうかの判定です
		{		
			//ボス部屋にプレイヤーがいるなら
			//強制的にスクロール座標を1024*4へ持っていく
			m_spMap->fixScrollPosition(1024*4);

			if(flag==false)
			{
				changeBgm("bossBgm");

				flag=true;
				m_spPlayer->setMoveMaxAndMIN(-1,1024*4);//1024*4より後ろへ下がれないように設定しプレイヤーをボス部屋から出られないようにします

				if(!(m_lSpActors.empty()))
				{
					for(listSpActor::iterator itSpActor=m_lSpActors.begin();itSpActor!=m_lSpActors.end();itSpActor++)
					{
						if((*itSpActor).get()!=NULL)
						{
							if(typeid(*(*itSpActor).get())==typeid(Enemy))
							{
								if((*itSpActor)->getBossFlag()==true)
								{
									//ボスもプレイヤーと同様にボス部屋から出られなくします
									(*itSpActor)->setMoveMaxAndMIN(-1,1024*4);
								}
							}
						}
					}
				}	
			}
		}
		else
		{
			flag=false;
			m_spMap->updateScroll(static_cast<int>(m_spPlayer->getX()));
		}
	}
}

//---------------------------------------------------

void GameState::setDrawBuffer(sp_DrawBuffer spDrawBufferFarEnd,
		sp_DrawBuffer spDrawBufferBackGround,
		sp_DrawBuffer spDrawBufferFront,
		sp_DrawBuffer spDrawBufferGameObject,
		sp_DrawBuffer spDrawBufferShadow,
		sp_DrawBuffer spDrawBufferInterface)
{
	//描画用のバッファを設定する
	//沢山あるのはレイヤー分けをして描画順を制御するため
	//initializeよりも先に呼び出すこと
	m_spDrawBufferFarEnd	=spDrawBufferFarEnd;
	m_spDrawBufferBackGround=spDrawBufferBackGround;
	m_spDrawBufferFront		=spDrawBufferFront;
	m_spDrawBufferGameObject=spDrawBufferGameObject;
	m_spDrawBufferShadow	=spDrawBufferShadow;
	m_spDrawBufferInterface	=spDrawBufferInterface;

}

//---------------------------------------------

void GameState::initialize(Input* pInput)
{
	//初期化の対象
	//inputへのポインタ
	//マップ
	//タイトル、クリア、ロゴ、などの画像
	//プレイヤー
	//すべてのActorData (キャラクターのもとになるデータ -ステータス初期値と画像とあたり判定データを一まとめにしたもの-)
	//インターフェースクラス（現在hp表示のみ）

	m_pInput=pInput;	
	
	if(m_spMap.get()==NULL)
	{
		m_spMap= sp_Map(new Map());
	}

	if(m_spMap.get()==NULL)
	{
		return;
	}

	m_spMap->initialize();

	m_Interface.initialize(m_spDrawBufferInterface);
	
	m_spMap->initializeDrawBuffer(m_spDrawBufferFarEnd,m_spDrawBufferBackGround,m_spDrawBufferFront);

	initializeActorData("CSVActorData/actorDataHeader.csv");
	
	//タイトル画面などに表示する画像の初期化
	//時間が空いた時に関数化させるつもり
	//「画像初期化終わり」というコメントまで
	if(m_spGraphTitle.get()==NULL)
	{
		m_spGraphTitle=sp_Graphics2D(new Graphics2D());
		if(m_spGraphTitle.get()!=NULL)
		{
			m_spGraphTitle->initialize("images/title.png");
		}
	}
	
	if(m_spGraphLogo.get()==NULL)
	{
		m_spGraphLogo=sp_Graphics2D(new Graphics2D());
		if(m_spGraphLogo.get()!=NULL)
		{
			m_spGraphLogo->initialize("images/logo.png");
		}
	}
		
	if(m_spGraphGameOver.get()==NULL)
	{
		m_spGraphGameOver=sp_Graphics2D(new Graphics2D());
		if(m_spGraphGameOver.get()!=NULL)
		{
			m_spGraphGameOver->initialize("images/gameOver.png");
		}
	}

	if(m_spGraphAllBlack.get()==NULL)
	{
		m_spGraphAllBlack=sp_Graphics2D(new Graphics2D());
		if(m_spGraphAllBlack.get()!=NULL)
		{
			m_spGraphAllBlack->initialize("images/BLACK.png");
		}
	}

	if(m_spGraphClear.get()==NULL)
	{
		m_spGraphClear=sp_Graphics2D(new Graphics2D());
		if(m_spGraphClear.get()!=NULL)
		{
			m_spGraphClear->initialize("images/clear.png");
		}
	}

	if(m_spGraphTeamMorimoto.get()==NULL)
	{
		m_spGraphTeamMorimoto=sp_Graphics2D(new Graphics2D());
		if(m_spGraphTeamMorimoto.get()!=NULL)
		{
			m_spGraphTeamMorimoto->initialize("images/teamMorimoto.png");
		}
	}

	//画像初期化終わり


	//プレイヤーを初期化します
	if(m_spPlayer.get()==NULL)
	{
		m_spPlayer=sp_Actor(new Player());
		
		if(m_spPlayer.get()!=NULL)
		{		
			spActorData spActData;
			spActData=GameState::findSpActorDataNamed("act_player");
			
			if(spActData.get()!=NULL)
			{
				m_spPlayer->setActerData(spActData);
			}
			else
			{
				cout<<"playerの初期化に失敗しました"<<endl;
				return;
			}

			m_spPlayer->setMap(m_spMap);				
			m_spPlayer->setHpMax();
			m_spPlayer->setDrawBuffer(m_spDrawBufferGameObject,m_spDrawBufferShadow);
			m_spPlayer->setPosition(0.0,(MOVE_MAX_Z-MOVE_MIN_Z)/2,240.0);
			m_spPlayer->setFirstPosition(100.0,240.0);
		}
	}
	else
	{
		cout<<"playerの初期化に失敗しました"<<endl;
		return;
	}
			
	cout<<"enemy初期化終わり"<<endl;		
	
	m_bIsInitialized=true;
}

//------------------------------------------------

void GameState::drawSet()
{	

	//初期化中もしくはロゴ表示の時以外に行う表示です
	//主に背景の描画、キャラクターの描画、影の描画を行います
	if(m_sequence!=SEQ_LOGO&&m_sequence!=SEQ_INIT)
	{
		if(!(m_lSpActors.empty()))
		for(listSpActor::iterator itSpActor =m_lSpActors.begin();itSpActor!=m_lSpActors.end();itSpActor++)
		{
			if((*itSpActor).get()!=NULL)
			{
				(*itSpActor)->drawSet(m_spMap->getScrolX());
				(*itSpActor)->drawSetShadow(m_spMap->getScrolX());
			}
		}	

		m_spMap->drawSet();

		if(m_sequence!=SEQ_INIT&&m_sequence!=SEQ_TITLE)
		{
			m_Interface.DrawHpGauge(m_spPlayer->getHp(),m_spPlayer->getActorData()->getMaxHp());
		}
	}
	

	//それぞれのゲームモード固有の画像表示を行います
	switch(m_sequence)
	{
		case SEQ_LOGO:
		{
			//ロゴを表示します
			m_spDrawBufferInterface->setCellBlend(BLEND_ALPHA,m_tBlendPar);
			m_spDrawBufferInterface->DrawSetRota(m_spGraphLogo.get(),0,WINDOW_WIDTH/2,WINDOW_HEIGHT/2,0.0,1.0,false);
		}
		break;
		
		case SEQ_TITLE:
		{
			//タイトル画面の「ベルステンの騎士」の文字を描画
			m_spDrawBufferInterface->DrawSet(m_spGraphTitle.get(),0,0,0,false);
		}
		break;

		case SEQ_OVER:
		{
			//ゲームオーバーになった時に半透明の黒い画像を描画
			//ゲームオーバーの文字を描画
			m_spDrawBufferInterface->setCellBlend(BLEND_ALPHA,m_tBlendPar);
			m_spDrawBufferInterface->DrawSet(m_spGraphAllBlack.get(),0,0,0,false);
			m_spDrawBufferInterface->setCellBlend(BLEND_ALPHA,m_tBlendPar*2);
			m_spDrawBufferInterface->DrawSet(m_spGraphGameOver.get(),0,0,0,false);
			m_spDrawBufferInterface->resetCellBlend();
		}
		break;

		case SEQ_CLEAR:
		{
			//クリアの文字の描画
			m_spDrawBufferInterface->setCellBlend(BLEND_ALPHA,m_tBlendPar);
			m_spDrawBufferInterface->DrawSet(m_spGraphClear.get(),0,0,0,false);		
			m_spDrawBufferInterface->resetCellBlend();
		}
		break;

		case SEQ_TEAM_MORIMOTO:
		{
			//製作者情報を書いた画像を描画
			m_spDrawBufferInterface->DrawSet(m_spGraphTeamMorimoto.get(),0,0,0,false);		
		}

		break;
	}
}

//------------------------------------------------

void GameState::initializeActorData(char *filePath)
{
	//すべてのacotrDataを初期化します
	//csvファイルを開き　最大数を読み出しメモリを割り当てします
	//その後各項目を読み出しては設定の繰り返しです
	//やたら長いのは項目がいっぱいあるからです

	//ここのコメントを読んだ方へ
	//少しでもスマートになる書き方、またアルゴリズムをご存知でしたらご享受ください

	TexRead texRead(filePath);

	if(texRead.isLoaded())
	{
		cout<<"読み込み成功 GameState initializeActorData()"<<filePath<<endl;
	
		string str;

		char inputC[STRING_LENGTH];
		char* pLine;

		int pos=0;//今読んでいる位置

//個数を読みだす

		if(texRead.readLineSkipOverSolidus()==false)
		{
			cout<<"問題発生"<<endl;	
		
			return;
		}
		pLine=texRead.getLine();
		pos=0;

		getNextStringToComma(inputC,pLine,&pos);//次の文字列をinputCにコピーする　pLine[pos]から','または'\n'まで　
	
		str=inputC;

		if(str!="<max>")//内容に間違いがある場合
		{	
			return;	
		}

		getNextStringToComma(inputC,pLine,&pos);

		int max=atoi(inputC);

//個数の読み出し終わり

		if(max>0)
		{

			if(texRead.readLineSkipOverSolidus()==false)
			{
				cout<<"問題発生"<<endl;	
				//reset();
				return;
			}
			
			pLine=texRead.getLine();
			pos=0;

			getNextStringToComma(inputC,pLine,&pos);
	
			str=inputC;

			if(str!="<path>")//内容に間違いがある場合
			{	
				return;	
			}

			for(int i=0;i<max;i++)
			{
				if(texRead.readLineSkipOverSolidus()==false)
				{
					cout<<"問題発生"<<endl;	
					return;
				}

				pLine=texRead.getLine();
				pos=0;

				getNextStringToComma(inputC,pLine,&pos);
	
				str=inputC;

				spActorData inputAc;
			
				inputAc=spActorData(new ActorData());			
				
				if(inputAc.get()!=NULL)
				{					
					inputAc->initialize(str.c_str());
					if(inputAc->isInitialized())
					{	
						m_lSpActorData.push_back(inputAc);	
					}
					else
					{
						cout<<"initialize失敗　　"<<str.c_str()<<endl;
					}					
				}
				else 
				{	
					cout<<"initialize失敗　　"<<str.c_str()<<endl;
				}			
			}
			cout<<"読み込み終了"<<endl;
		}
	}
}

//----------------------------------------------

spActorData GameState::findSpActorDataNamed(const char* name)
{
	cout<<"finedActorData"<<endl;

	spActorData r;	

	listSpActorData::iterator p=GameState::m_lSpActorData.begin();
	
	if(!(m_lSpActorData.empty()))
	while(p!=m_lSpActorData.end())
	{
		if ((*p)->getName()==name)
		{
			r= (*p);

			break;
		}
		else
		{
			p++;	
		}
	}

	cout<<"findActorData Out"<<endl;
	return r;
}

//----------------------------------------------

void GameState::initializeEnemy(const char *filePath)
{
	//すべてのacotrDataを初期化します
	//csvファイルを開き　最大数を読み出しループに入ります
	//キャラクターを1対ごとにメモリを割り当てします
	//その後各項目を読み出しては設定の繰り返しです
	//やたら長いのは設定項目がいっぱいあるからです

	//ここのコメントを読んだ方へ
	//少しでもスマートになる書き方、またアルゴリズムをご存知でしたらご享受ください

	TexRead texRead(filePath);

	if(texRead.isLoaded())
	{
		cout<<"読み込み成功 GameState initializeActorData()"<<filePath<<endl;
	
		string str;

		char inputC[STRING_LENGTH];
		char* pLine;

		int pos=0;//今読んでいる位置


//個数を読みだす

		if(texRead.readLineSkipOverSolidus()==false)
		{
			cout<<"問題発生"<<endl;	
		
			return;
		}
			pLine=texRead.getLine();
			pos=0;

		getNextStringToComma(inputC,pLine,&pos);//次の文字列をinputCにコピーする　pLine[pos]から','または'\n'まで　
	
		str=inputC;

		if(str!="<max>")//内容に間違いがある場合
		{	
			return;	
		}

		getNextStringToComma(inputC,pLine,&pos);//次の文字列をinputCにコピーする　pLine[pos]から','または'\n'まで　

		int max=atoi(inputC);

		for(int i=0;i<max;i++)
		{
			double x;
			double z;
			string type;
			int aiType =0;

			if(texRead.readLineSkipOverSolidus()==false)
			{
				cout<<"問題発生"<<endl;	
				return;
			}

			pLine=texRead.getLine();
			pos=0;

			getNextStringToComma(inputC,pLine,&pos);
			type=inputC;

			getNextStringToComma(inputC,pLine,&pos);
			x=atof(inputC);

			getNextStringToComma(inputC,pLine,&pos);
			z=atof(inputC);

			getNextStringToComma(inputC,pLine,&pos);
			aiType=atoi(inputC);

			getNextStringToComma(inputC,pLine,&pos);
			int bossFlag=atoi(inputC);
			
			
			cout<<"enemy初期化"<<endl;
			
			
			spActorData spActData;

			spActData=GameState::findSpActorDataNamed(type.c_str());
			
			if(spActData.get()!=NULL)
			{
				sp_Actor spAct;
				spAct=sp_Actor(new Enemy());//メモリ割り当て
			
				string name ="spAct Enemy_";
				name+=('a'+i);			
				spAct->setActerData(spActData);
				spAct->setMap(m_spMap);
				spAct->setPosition(x,0.0,z);
				spAct->setFirstPosition(x,z);
				spAct->setHpMax();
				spAct->setDrawBuffer(m_spDrawBufferGameObject,m_spDrawBufferShadow);				
				spAct->setAiType(aiType);
				spAct->setBossFlag(bossFlag);

				spAct->setTarget(m_spPlayer);

				m_lSpActors.push_back(spAct);
			}			
		}
	}
}

//----------------------------------------------

void GameState::setUpGame()
{
	//ゲームの初期化を行います

	m_lSpActors.clear();	//すべてのキャラクターをリストから削除 デストラクタが呼ばれメモリが解放される
							//この時m_spPlayerがリストに保存されているがshared_ptrの参照カウントが残っているため
							//プレイヤーのデータだけは例外でメモリから削除はされない	※バグではない
	
	//プレイヤーの再初期化
	m_spPlayer->reset();
	m_spPlayer->setHpMax();
	m_spPlayer->setDrawBuffer(m_spDrawBufferGameObject,m_spDrawBufferShadow);
	m_spPlayer->setPosition(MOVE_MIN_X+50,0.0,(MOVE_MAX_Z-MOVE_MIN_Z)/2);
	m_spPlayer->setFirstPosition(MOVE_MIN_X,(MOVE_MAX_Z-MOVE_MIN_Z)/2);
	
	//プレイヤーをリストに追加
	m_lSpActors.push_back(m_spPlayer);
	
	initializeEnemy("test.csv");


	m_spMap->setScrollMinX(MOVE_MIN_X);
	m_spMap->updateScroll(static_cast<int>(m_spPlayer->getX()));
}

//-------------------------------

bool GameState::isCleared()
{
	//ゲームクリアしたかどうか
	//bossフラグを持つエネミーが存在しないならtrueを返す 一人でも存在しているならFalse
	
	if(!(m_lSpActors.empty()))
	{
		for(listSpActor::iterator itSpActor =m_lSpActors.begin();itSpActor!=m_lSpActors.end();itSpActor++)
		{
			if((*itSpActor).get()!=NULL)
			{
				if(typeid(*(*itSpActor).get())==typeid(Enemy))
				{
					if((*itSpActor)->getBossFlag()==true)
					{
						return false;
					}
				}
			}
		}
	}	
	return true;
}

//-------------------------------
void GameState::changeBgm(const char* name)
{
	stopSound(m_bgmName.c_str());
	m_bgmName=name;
	
	playSound(name,true);
}

//-------------------------------
void GameState::stopBgm()
{
	stopSound(m_bgmName.c_str());
	m_bgmName="no";	
}