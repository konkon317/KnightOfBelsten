#include "actor.h"

#include "../../sound/soundForDxLib.h"

//---------------------------------------------
//�R���X�g���N�^
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
//�f�X�g���N�^
Actor::~Actor()
{
	cout<<"actor �f�X�g���N�^"<<endl;
}


//�ȉ��֐���`
//-----------------------------------------------------

void Actor::setPosition(double x,double y,double z)
{
	//�L�����N�^�[��C�ӂ̍��W�֐ݒ肷��
	
	Actor::setX(x);
	Actor::setY(y);
	Actor::setZ(z);
	updateOldPosition();
}

//--------------------------------------------------

void Actor::move(double x,double z,listSpActor* plspActors)
{
	//���͂ɑ΂��Ĉړ�������

	if(m_mode==ACT_MODE_WALK||m_mode==ACT_MODE_STAND)
	//�ړ��ł��邩�̔��f �U�����[�V�����@��_���[�W���[�V�����Ȃǂ̎��ɂ͈ړ����ł��Ȃ�
	{
		if(x!=0||z!=0)
		{
			//�ړ��̓��͂�����ꍇ�͕������[�V����
			m_mode=ACT_MODE_WALK;
		}
		else 
		{
			//�ړ��̓��͂������ꍇ�͗������[�V����
			m_mode=ACT_MODE_STAND;
		}

		if(m_spMap.get()!=NULL)
		{
			if(m_spActData.get()!=NULL)
			{
				//x���W�̈ړ�
				m_x+=x*m_spActData->getSpeedLR();
				
				//�X�e�[�W�ɐݒ肳�ꂽ���W��������𒴂��Ă��Ȃ����̔���
				if(m_x>MOVE_MAX_X)
				{
					m_x=MOVE_MAX_X;
				}
				if(m_x<MOVE_MIN_X)
				{
					m_x=MOVE_MIN_X;
				}

				//�����ɐݒ肳�ꂽ���W��������𒴂��Ă��Ȃ����̔���@x���W�̂݁@
				//�����Ă���Ȃ�x���W��O�̃t���[���̍��W��
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

				//�N���Ƒ̂��Ԃ����Ă��Ȃ����̔���
				if(isBrashedWithSomeOne(plspActors))
				{
					//�Ԃ����Ă�����x�͈ړ��O�Ƀ��Z�b�g
					setPositionXOld();
				}			

				//z���W�̈ړ�
				m_z+=z*m_spActData->getSpeedZ();

				//�X�e�[�W�ɐݒ肳�ꂽ���W��������𒴂��Ă��Ȃ����̔���
				if(m_z<MOVE_MIN_Z)
				{
					m_z=MOVE_MIN_Z;
				}
				if(m_z>MOVE_MAX_Z)
				{
					m_z=MOVE_MAX_Z;
				}

				//�N���Ƒ̂��Ԃ����Ă��Ȃ����̔���
				if(isBrashedWithSomeOne(plspActors))
				{
					//�Ԃ����Ă�����z�͈ړ��O�Ƀ��Z�b�g
					setPositionZOld();
				}
			}
		}
	}
}


//--------------------------------------------------

void Actor::setMode(ACTOR_MODE actMode)
{
	//���[�h�̕ύX

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
	//�L�����N�^�[�ɏ����|�W�V������ݒ肷��@
	//���enemy��ai�Ɏg�p����v���p�e�B
	
	m_firstX=static_cast<int>(x);
	m_firstZ=static_cast<int>(z);
}

//-------------------------------------------------

bool Actor::isBrashedWith(Actor* setActor)const
{
	//setActor�ƐڐG���Ă��Ȃ����̔���
	//�ڐG���Ă���Ȃ�true��Ԃ�

	ActorData * pActData=setActor->getActorData();

	if(pActData!=NULL)
	{
		//���f�ɕK�v�ȃf�[�^�����[�J���ϐ���
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

		//���f
		//x���W�ŐڐG����͈͓���
		bool checkX=((LowX<=setLowX&&HighX>=setLowX)||(LowX<=setHighX&&HighX>=setHighX)||(setLowX<=LowX&&setHighX>=HighX));
		
		//z���W�ŐڐG����͈͓���
		bool checkZ=((LowZ<=setLowZ&&HighZ>=setLowZ)||(LowZ<=setHighZ&&HighZ>=setHighZ)||(setLowZ<=LowZ&&setHighZ>=HighZ));

		if(checkX&&checkZ)
		{
			return true;//�ڐG���Ă���	
		}
	}

	return false;
}

//------------------------------------------------------

bool Actor::isBrashedWithSomeOne(listSpActor* plSpActors)const
{
	//��ʏ�ɋ��鎩�����������ׂẴL�����N�^�[�ƕ����I�ɐڐG���Ă��邩
	//�N����l�ȏ�ƂԂ����Ă���Ȃ� true��Ԃ�
	// ���U�����q�b�g��������ł͂Ȃ��A�L�����N�^�[���m�̑̂��Ԃ����Ă��邩�̔���

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
	//�`��		
	//�L�����N�^�[�Ƃ��̉e��`�悷��
	
	if(m_spActData.get()!=NULL)
	{																		
		int patternNum	=static_cast<int>(m_mode);	
		int sheetNum	=m_spActData->getGraphPatternData(patternNum).m_sheetNum;
	
		if (patternNum>=0&&patternNum<ACT_MODE_MAX)				
		{
			bool turnFlag=(m_directionFacing==FACE_LEFT)?true:false;//�摜�̍��E���]�̔��f

			//�{�̂̕`��
			m_spDrawBuffer->DrawSetRota(m_spActData->getPGraph(sheetNum),m_spActData->getGraphPatternData(patternNum).m_index+m_animNum,
				static_cast<int>(m_x)-scrollX,458+static_cast<int>(STAGE_SIZE_Z-m_z),
				100,190,m_z,0.0,1.0-(0.1*(m_z/MOVE_MAX_Z)),turnFlag);
				
				/*
				3�s��100��190�ɂ���
				��_�̎w��ł�
				�摜���́i100,190�j���`����W�im_x-scrollX, 458+STAGE_SIZE_Z-m_z�j�Əd�Ȃ�悤�ɕ`�悵�܂�
				�e�̕`���3�s�ڂ�100,90�����l�ł�
				*/

			//�e�̕`��
			m_spDrawBufferShadow->DrawSetRota(m_spActData->getPGraphShadow(sheetNum),m_spActData->getGraphPatternData(patternNum).m_index+m_animNum,
				static_cast<int>(m_x)-scrollX,458+static_cast<int>(STAGE_SIZE_Z-m_z),
				100,90,m_z,0.0,1.0-(0.1*(m_z/MOVE_MAX_Z)),turnFlag);
		}
	}
}

//--------------------------------------------------

void Actor::setHp(int point)
{ 
	//hp��point�ɐݒ肷��
	//point��hp�ő�l�ȉ�����0�ȏ�,�łȂ��ꍇ�͕ύX����Ȃ��@
	
	if(point<=m_spActData->getMaxHp()&&point>=0)
	{
		cout<<"Actor::setHp "<<point<<endl;

		m_hitPoint=point;
	}
}

//-------------------------------------------------

void Actor::damage(int point)
{
	//point���̃_���[�W���󂯂�m_mode���_���[�W���[�h�ɕύX����
	//�܂��Am_hitPoint��0�ȉ��ɂȂ��m_mode��ACT_MODE_DIE�i���S��ԁj�֕ύX����

	if(m_countIntervalOfDamage==0)
	{
		cout<<"Actor::damage "<<point<<endl;
		if(point>=0)
		{
			m_hitPoint-=point;
		}

		setMode(ACT_MODE_DAMAGE);
		
		m_countIntervalOfDamage=INTERVAL_OF_DAMAGE_MAX;//���G���Ԃ�ݒ�

		if(m_hitPoint<=0)
		{
			setMode(ACT_MODE_DIE);
			m_hitPoint=0;
			cout<<"�q�b�g�|�C���g���[���ɂȂ�܂���"<<endl;
		}
	}
}

//-----------------------------------------------------

void Actor::updateAnimation()
{
	//�A�j���[�V�����̃A�b�v�f�[�g
	//�U�����[�V�����̏I������_���[�W���[�V�����̏I�����ɂ̓��[�h�̐ݒ��ύX����
	
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
				//�A�^�b�N���[�h
				//�_���[�W���[�h
				//�̃A�j���[�V�������Ō�܂ŕ\�����ꂽ�Ȃ痧�����[�h��

				setMode(ACT_MODE_STAND);
			}

			if(m_mode!=ACT_MODE_DIE)
			{
				m_animNum=0;
			}
			else
			{
				//���S�A�j���[�V�����̏ꍇ�͍Ō�̉摜�̂܂ܕύX����Ȃ��悤�ɂ���
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
	//m_spActData���玩���̔퓖��G���A�̏���Ԃ�
	//���s����null�|�C���^��Ԃ�
	//null�|�C���^�ɗ���̂͗ǂ��Ȃ��Ƃ̂��ƂȂ̂Ń��t�@�N�^�����O�\��
	
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
	//m_spActData���玩���̍U���G���A��Ԃ��@
	//�U�����[�V�����ɓ����Ă��Ȃ����A���s����null�|�C���^��Ԃ�
	//null�|�C���^�ɗ���̂͗ǂ��Ȃ��Ƃ̂��ƂȂ̂Ń��t�@�N�^�����O�\��
		
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
	//�A�b�v�f�[�g
	
	updateCountIntervalOfDamage();
}

//-----------------------------------------------------

void Actor::setActerData(spActorData spActData)
{
	//actorData�ւ̃|�C���^��ݒ肷�� 
	
	cout<<"actorSetActData"<<endl;
	m_spActData=spActData;
	cout<<"actorSetActData Out"<<endl;
}

//----------------------------------------------------

void Actor::setMap(sp_Map spMap)
{
	//�}�b�v�ւ̃|�C���^��ݒ肷��@
	
	m_spMap=spMap;
}

//-----------------------------------------------------

bool Actor::doseGetHit(sp_Actor spActor)const
{
	//pActor����̍U���������Ƀq�b�g������ 
	//���Ă����true��Ԃ�	
	
	bool r=false;
	
	//���f�ɕK�v�ȃf�[�^�����[�J���ϐ���
	int setX	=static_cast<int>(spActor->getX());
	int setY	=static_cast<int>(spActor->getY());
	int setZ	=static_cast<int>(spActor->getZ());

	int ArangeZ	=spActor->getActorData()->getAtackRangeZ();
	int SizeZ	=static_cast<int>(m_spActData->getSizeZ());

	bool useTurn=spActor->getTurnFlag();

	HitArea *pSetHitArea=spActor->getAtackArea_P();	

	if(pSetHitArea!=NULL)
	{
		//b1-b4�̂ǂꂩ��true�Ȃ��z���W��ł͐ڐG����͈͈ȓ�
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

				//���蔻����\�����Ă���~�̍ő吔�����ꂼ��ǂݏo��
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
							//�~���m���ڐG���Ă���
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
	//���G���ԉ����܂ł̃J�E���g�_�E��
	
	m_countIntervalOfDamage--;

	if(m_countIntervalOfDamage<0)
	{
		m_countIntervalOfDamage=0;
	}
}

//-----------------------------------------------------

void Actor::updateOldPosition()
{
	//1�t���[���O�̍��W�im_old�`�@x,y,z�j�̃A�b�v�f�[�g
	m_oldX=m_x;
	m_oldY=m_y;
	m_oldZ=m_z;
}

//------------------------------------------------------

bool Actor::isDead()const 
{
	//����ACTOR������ł���Ȃ�true��Ԃ�
	//���S���[�h�ł���@���@���S���[�V�������Ō�܂ŕ\�����ꂽ�Ȃ�true��Ԃ�

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
	//hp��hp�ő�l�ɐݒ肷��
	
	if(m_spActData.get()!=NULL)
	{
		setHp(m_spActData->getMaxHp());
	}
}
