#include "actor.h"

#include "../../sound/soundForDxLib.h"

//---------------------------------------------
//コンストラクタ
Actor::Actor()
{
	m_animNum=m_animCount=0;
	m_mode=ACT_MODE_STAND;
	m_directionFacing=FACE_RIGHT;
	m_hitPoint=0;
	m_countIntervalOfDamage=0;

	m_firstX=0;
	m_firstZ=0;

	m_moveXMax=-1;
	m_moveXMin=-1;
}

//-----------------------------------------------------
//デストラクタ
Actor::~Actor()
{
	cout<<"actor デストラクタ"<<endl;
}


//以下関数定義
//-----------------------------------------------------

void Actor::setPosition(double x,double y,double z)
{
	//キャラクターを任意の座標へ設定する
	
	Actor::setX(x);
	Actor::setY(y);
	Actor::setZ(z);
	updateOldPosition();
}

//--------------------------------------------------

void Actor::move(double x,double z,listSpActor* plspActors)
{
	//入力に対して移動させる

	if(m_mode==ACT_MODE_WALK||m_mode==ACT_MODE_STAND)
	//移動できるかの判断 攻撃モーション　被ダメージモーションなどの時には移動ができない
	{
		if(x!=0||z!=0)
		{
			//移動の入力がある場合は歩きモーション
			m_mode=ACT_MODE_WALK;
		}
		else 
		{
			//移動の入力が無い場合は立ちモーション
			m_mode=ACT_MODE_STAND;
		}

		if(m_spMap.get()!=NULL)
		{
			if(m_spActData.get()!=NULL)
			{
				//x座標の移動
				m_x+=x*m_spActData->getSpeedLR();
				
				//ステージに設定された座標上限下限を超えていないかの判定
				if(m_x>MOVE_MAX_X)
				{
					m_x=MOVE_MAX_X;
				}
				if(m_x<MOVE_MIN_X)
				{
					m_x=MOVE_MIN_X;
				}

				//自分に設定された座標上限下限を超えていないかの判定　x座標のみ　
				//超えているならx座標を前のフレームの座標へ
				if(m_moveXMin>=0)
				{
					if(m_moveXMin>m_x)
					{
						setPositionXOld();
					}
				}
				if(m_moveXMax>=0)
				{
					if(m_moveXMax<m_x)
					{
						setPositionXOld();
					}
				}

				//誰かと体がぶつかっていないかの判定
				if(isBrashedWithSomeOne(plspActors))
				{
					//ぶつかっていたらxは移動前にリセット
					setPositionXOld();
				}			

				//z座標の移動
				m_z+=z*m_spActData->getSpeedZ();

				//ステージに設定された座標上限下限を超えていないかの判定
				if(m_z<MOVE_MIN_Z)
				{
					m_z=MOVE_MIN_Z;
				}
				if(m_z>MOVE_MAX_Z)
				{
					m_z=MOVE_MAX_Z;
				}

				//誰かと体がぶつかっていないかの判定
				if(isBrashedWithSomeOne(plspActors))
				{
					//ぶつかっていたらzは移動前にリセット
					setPositionZOld();
				}
			}
		}
	}
}


//--------------------------------------------------

void Actor::setMode(ACTOR_MODE actMode)
{
	//モードの変更

	if(m_mode!=actMode&&actMode<ACT_MODE_MAX)
	{
		m_mode=actMode;
		m_animNum=0;
		m_animCount=0;
	}
}
//---------------------------------------------------

void Actor::setFirstPosition(double x,double z)
{
	//キャラクターに初期ポジションを設定する　
	//主にenemyのaiに使用するプロパティ
	
	m_firstX=static_cast<int>(x);
	m_firstZ=static_cast<int>(z);
}

//-------------------------------------------------

bool Actor::isBrashedWith(Actor* setActor)const
{
	//setActorと接触していないかの判定
	//接触しているならtrueを返す

	ActorData * pActData=setActor->getActorData();

	if(pActData!=NULL)
	{
		//判断に必要なデータをローカル変数に
		int setSizeX=pActData->getSizeX();
		int setSizeZ=pActData->getSizeZ();

		int setLowX=static_cast<int>(setActor->getX()-(setSizeX/2));
		int setHighX=static_cast<int>(setActor->getX()+(setSizeX/2));
		int setLowZ=static_cast<int>(setActor->getZ()-(setSizeZ/2));
		int setHighZ=static_cast<int>(setActor->getZ()+(setSizeZ/2));

		int LowX=static_cast<int>(m_x)-(m_spActData->getSizeX()/2);
		int HighX=static_cast<int>(m_x)+(m_spActData->getSizeX()/2);	
		int LowZ=static_cast<int>(m_z)-(m_spActData->getSizeZ()/2);
		int HighZ=static_cast<int>(m_z)+(m_spActData->getSizeZ()/2);	

		//判断
		//x座標で接触する範囲内か
		bool checkX=((LowX<=setLowX&&HighX>=setLowX)||(LowX<=setHighX&&HighX>=setHighX)||(setLowX<=LowX&&setHighX>=HighX));
		
		//z座標で接触する範囲内か
		bool checkZ=((LowZ<=setLowZ&&HighZ>=setLowZ)||(LowZ<=setHighZ&&HighZ>=setHighZ)||(setLowZ<=LowZ&&setHighZ>=HighZ));

		if(checkX&&checkZ)
		{
			return true;//接触している	
		}
	}

	return false;
}

//------------------------------------------------------

bool Actor::isBrashedWithSomeOne(listSpActor* plSpActors)const
{
	//画面上に居る自分を除くすべてのキャラクターと物理的に接触しているか
	//誰か一人以上とぶつかっているなら trueを返す
	// ※攻撃がヒットした判定ではなく、キャラクター同士の体がぶつかっているかの判定

	if(!(plSpActors->empty()))
	for(listSpActor::iterator itr =plSpActors->begin();	itr!=plSpActors->end();	itr++)
	{
		if((*itr).get()!=NULL)
		{		
			if((*itr).get()!=this)
			{
				if(isBrashedWith((*itr).get()))
				{
					return true;
				}
			}
		}
	}
	return false;
}


//--------------------------------------------------

void Actor::drawSet(int scrollX)const										
{		
	//描画		
	//キャラクターとその影を描画する
	
	if(m_spActData.get()!=NULL)
	{																		
		int patternNum	=static_cast<int>(m_mode);	
		int sheetNum	=m_spActData->getGraphPatternData(patternNum).m_sheetNum;
	
		if (patternNum>=0&&patternNum<ACT_MODE_MAX)				
		{
			bool turnFlag=(m_directionFacing==FACE_LEFT)?true:false;//画像の左右反転の判断

			//本体の描画
			m_spDrawBuffer->DrawSetRota(m_spActData->getPGraph(sheetNum),m_spActData->getGraphPatternData(patternNum).m_index+m_animNum,
				static_cast<int>(m_x)-scrollX,458+static_cast<int>(STAGE_SIZE_Z-m_z),
				100,190,m_z,0.0,1.0-(0.1*(m_z/MOVE_MAX_Z)),turnFlag);
				
				/*
				3行目100と190について
				基準点の指定です
				画像中の（100,190）が描画座標（m_x-scrollX, 458+STAGE_SIZE_Z-m_z）と重なるように描画します
				影の描画の3行目の100,90も同様です
				*/

			//影の描画
			m_spDrawBufferShadow->DrawSetRota(m_spActData->getPGraphShadow(sheetNum),m_spActData->getGraphPatternData(patternNum).m_index+m_animNum,
				static_cast<int>(m_x)-scrollX,458+static_cast<int>(STAGE_SIZE_Z-m_z),
				100,90,m_z,0.0,1.0-(0.1*(m_z/MOVE_MAX_Z)),turnFlag);
		}
	}
}

//--------------------------------------------------

void Actor::setHp(int point)
{ 
	//hpをpointに設定する
	//pointがhp最大値以下かつ0以上,でない場合は変更されない　
	
	if(point<=m_spActData->getMaxHp()&&point>=0)
	{
		cout<<"Actor::setHp "<<point<<endl;

		m_hitPoint=point;
	}
}

//-------------------------------------------------

void Actor::damage(int point)
{
	//point分のダメージを受けるm_modeをダメージモードに変更する
	//また、m_hitPointが0以下になるとm_modeをACT_MODE_DIE（死亡状態）へ変更する

	if(m_countIntervalOfDamage==0)
	{
		cout<<"Actor::damage "<<point<<endl;
		if(point>=0)
		{
			m_hitPoint-=point;
		}

		setMode(ACT_MODE_DAMAGE);
		
		m_countIntervalOfDamage=INTERVAL_OF_DAMAGE_MAX;//無敵時間を設定

		if(m_hitPoint<=0)
		{
			setMode(ACT_MODE_DIE);
			m_hitPoint=0;
			cout<<"ヒットポイントがゼロになりました"<<endl;
		}
	}
}

//-----------------------------------------------------

void Actor::updateAnimation()
{
	//アニメーションのアップデート
	//攻撃モーションの終了時やダメージモーションの終了時にはモードの設定を変更する
	
	if(!(Actor::isDead()))
	{
		m_animCount++;
	}

	if(m_animCount==ANIM_COUNT_MAX)
	{
		m_animNum++;

		if(m_animNum  >=  m_spActData->getGraphPatternData(static_cast<int>(m_mode)).m_max)
		{			
			if(m_mode==ACT_MODE_ATTACK_1||m_mode==ACT_MODE_DAMAGE)
			{
				//アタックモード
				//ダメージモード
				//のアニメーションが最後まで表示されたなら立ちモードに

				setMode(ACT_MODE_STAND);
			}

			if(m_mode!=ACT_MODE_DIE)
			{
				m_animNum=0;
			}
			else
			{
				//死亡アニメーションの場合は最後の画像のまま変更されないようにする
				GraphPatternData gpd=m_spActData->getGraphPatternData(static_cast<int>(m_mode));
				m_animNum=gpd.m_max-1;
			}			
		}

		if(!(Actor::isDead()))
		{
			m_animCount=0;
		}
	}
}

//-----------------------------------------------------

HitArea* Actor::getHitAreaBody_P()const
{
	//m_spActDataから自分の被当りエリアの情報を返す
	//失敗時はnullポインタを返す
	//nullポインタに頼るのは良くないとのことなのでリファクタリング予定
	
	HitArea* pHitArea=NULL;
		
	int sheetNum=m_spActData->getGraphPatternData(static_cast<int>(m_mode)).m_sheetNum;

	int index=0;

	if(sheetNum >=0&&sheetNum<m_spActData->getGraphMax())
	{
		for(int i=0;i<sheetNum;i++)
		{
			index+=m_spActData->getGraphMaxInSheet(i);
		}

		index+=m_spActData->getGraphPatternData(static_cast<int>(m_mode)).m_index;
		index+=m_animNum;
	}	
	
	HitAreaSet* pHitAreaSet=m_spActData->getHitAreaSet_P();
		
	if(pHitAreaSet->isInitialized())
	{
		pHitArea=pHitAreaSet->getHitArea_P(index);
	}
	
	return pHitArea;
}


//---------------------------------------------------

HitArea* Actor::getAtackArea_P()const
{
	//m_spActDataから自分の攻撃エリアを返す　
	//攻撃モーションに入っていない等、失敗時はnullポインタを返す
	//nullポインタに頼るのは良くないとのことなのでリファクタリング予定
		
	HitArea * pHitArea=NULL;

	if(m_mode==ACT_MODE_ATTACK_1)
	{
		int sheetNum=m_spActData->getGraphPatternData(static_cast<int>(m_mode)).m_sheetNum;

		int index=0;

		if(sheetNum >= 0 && sheetNum < m_spActData->getGraphMax() )
		{
			for(int i=0;i<sheetNum;i++)
			{
				index+=m_spActData->getGraphMaxInSheet(i);
			}

			index+=m_spActData->getGraphPatternData(static_cast<int>(m_mode)).m_index;
			index+=m_animNum;
		}	
			
		HitAreaSet * pHitAreaSet=m_spActData->getAtackAreaSet_P();
				
		if(pHitAreaSet->isInitialized())
		{
			pHitArea=pHitAreaSet->getHitArea_P(index);
		}
	}

	return pHitArea;
}

//-----------------------------------------------------

void Actor::update()
{
	//アップデート
	
	updateCountIntervalOfDamage();
}

//-----------------------------------------------------

void Actor::setActerData(spActorData spActData)
{
	//actorDataへのポインタを設定する 
	
	cout<<"actorSetActData"<<endl;
	m_spActData=spActData;
	cout<<"actorSetActData Out"<<endl;
}

//----------------------------------------------------

void Actor::setMap(sp_Map spMap)
{
	//マップへのポインタを設定する　
	
	m_spMap=spMap;
}

//-----------------------------------------------------

bool Actor::doseGetHit(sp_Actor spActor)const
{
	//pActorからの攻撃が自分にヒットしたか 
	//していればtrueを返す	
	
	bool r=false;
	
	//判断に必要なデータをローカル変数に
	int setX	=static_cast<int>(spActor->getX());
	int setY	=static_cast<int>(spActor->getY());
	int setZ	=static_cast<int>(spActor->getZ());

	int ArangeZ	=spActor->getActorData()->getAtackRangeZ();
	int SizeZ	=static_cast<int>(m_spActData->getSizeZ());

	bool useTurn=spActor->getTurnFlag();

	HitArea *pSetHitArea=spActor->getAtackArea_P();	

	if(pSetHitArea!=NULL)
	{
		//b1-b4のどれかがtrueならばz座標上では接触する範囲以内
		bool b1=m_z+(SizeZ/2)<=setZ+(ArangeZ/2) && m_z+(SizeZ/2)>=setZ-(ArangeZ/2);
		bool b2=m_z-(SizeZ/2)<=setZ+(ArangeZ/2) && m_z-(SizeZ/2)>=setZ-(ArangeZ/2);		
		bool b3=m_z+(SizeZ/2)<=setZ+(ArangeZ/2) && m_z-(SizeZ/2)>=setZ-(ArangeZ/2);		
		bool b4=m_z+(SizeZ/2)>=setZ+(ArangeZ/2) && m_z-(SizeZ/2)<=setZ-(ArangeZ/2);

		if(b1||b2||b3||b4)
		{
			HitArea* pHitArea=getHitAreaBody_P();

			/*ACTOR_MODE am=m_mode;
			int p=m_animNum;*/

			if(pHitArea!=NULL)
			{
				bool turnFlag=(m_directionFacing==FACE_LEFT)?true:false;
				int x=static_cast<int>(m_x);
				int y=static_cast<int>(m_y);

				//当り判定を構成している円の最大数をそれぞれ読み出す
				int max		=pHitArea	->getMax();
				int setMax	=pSetHitArea->getMax();
				
				for(int i=0;i<max;i++)
				{
					for(int j=0;j<setMax;j++)
					{						
						circle myCircle	=pHitArea	->getCircle(i);
						circle circle	=pSetHitArea->getCircle(j);
					
						if(CheckHit_Circle(x,y,myCircle,turnFlag,setX,setY,circle,useTurn))
						{	
							//円同士が接触している
							return true;
						}
					}
				}
			}
		}
	}

	return false;
}

//-----------------------------------------------------

void Actor::updateCountIntervalOfDamage()
{
	//無敵時間解除までのカウントダウン
	
	m_countIntervalOfDamage--;

	if(m_countIntervalOfDamage<0)
	{
		m_countIntervalOfDamage=0;
	}
}

//-----------------------------------------------------

void Actor::updateOldPosition()
{
	//1フレーム前の座標（m_old～　x,y,z）のアップデート
	m_oldX=m_x;
	m_oldY=m_y;
	m_oldZ=m_z;
}

//------------------------------------------------------

bool Actor::isDead()const 
{
	//このACTORが死んでいるならtrueを返す
	//死亡モードである　かつ　死亡モーションが最後まで表示されたならtrueを返す

	if(m_mode==ACT_MODE_DIE)
	{
 		if(m_animNum>=(m_spActData->getGraphPatternData(static_cast<int>(m_mode)).m_max)-1)
		{
 			if(m_animCount==ANIM_COUNT_MAX-1)
			{
				return true;
			}
		}	
	}
	return false;
}

//-------------------------------------------------------

void Actor::setHpMax()
{
	//hpをhp最大値に設定する
	
	if(m_spActData.get()!=NULL)
	{
		setHp(m_spActData->getMaxHp());
	}
}
