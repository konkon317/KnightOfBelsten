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
	//�`��ȊO�̂��ׂẴQ�[���������s���܂�

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
		
	//���ׂẴL�����N�^�[�̃A�j���[�V�����̍X�V 
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
	//�Q�[���{�̂̏����ł�
	//�����Ƀv���C���[�̑���A�U��
	//�G�̎v�l�A�ړ��A�U��
	//�����蔻��A�_���[�W�����A���S����
	//�Ȃǁ@�Q�[���̑啔�������̊֐�����Ăяo���Ă��܂�

	//�@! �K��setDrawBuffer���Ăяo������ɂ��̊֐����Ăяo������

	//if(m_pInput->keyCt(KEY_INPUT_1)==1)m_spPlayer->kill();
	//if(m_pInput->keyCt(KEY_INPUT_2)==1)m_spPlayer->damage(1);
	
	//�v���C���[�̃A�b�v�f�[�g
	m_spPlayer->update(m_pInput,&m_lSpActors);
	
	//
	if(!(m_lSpActors.empty()))	
	{	
		listSpActor::iterator itSpActor =m_lSpActors.begin();

		while(itSpActor!=m_lSpActors.end())
		{
			//���ׂĂ̓G�L�����N�^�[�Ɉ�A�����������郋�[�v�ł�
			//for�����g�p���Ă��Ȃ��̂�erace���ĂԂ��Ƃ����邽��

			if((*itSpActor).get()!=NULL)
			{
				if(typeid(*(*itSpActor).get())==typeid(Enemy))
				{
					(*itSpActor)->update(m_spPlayer,&m_lSpActors);			
				
					if((*itSpActor)->isDead())
					{
						//����ł���Ƃ��̏���
					
						itSpActor=m_lSpActors.erase(itSpActor);		//.erace�͍폜�����v�f�̒���̗v�f�ւ̃C�e���[�^��Ԃ����߁@�C�e���[�^��++�@����K�v�Ȃ�
																	//�f�[�^����폜����
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

	{	//����'{'�̓��[�J���ϐ� flag���X�R�[�v�ɕ����߂邽�߂̂��̂ł�

		static bool flag=false;
	
		if(m_spPlayer->getX()>1024*4)//�v���C���[���{�X�����ɂ��邩�ǂ����̔���ł�
		{		
			//�{�X�����Ƀv���C���[������Ȃ�
			//�����I�ɃX�N���[�����W��1024*4�֎����Ă���
			m_spMap->fixScrollPosition(1024*4);

			if(flag==false)
			{
				changeBgm("bossBgm");

				flag=true;
				m_spPlayer->setMoveMaxAndMIN(-1,1024*4);//1024*4�����։�����Ȃ��悤�ɐݒ肵�v���C���[���{�X��������o���Ȃ��悤�ɂ��܂�

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
									//�{�X���v���C���[�Ɠ��l�Ƀ{�X��������o���Ȃ����܂�
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
	//�`��p�̃o�b�t�@��ݒ肷��
	//��R����̂̓��C���[���������ĕ`�揇�𐧌䂷�邽��
	//initialize������ɌĂяo������
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
	//�������̑Ώ�
	//input�ւ̃|�C���^
	//�}�b�v
	//�^�C�g���A�N���A�A���S�A�Ȃǂ̉摜
	//�v���C���[
	//���ׂĂ�ActorData (�L�����N�^�[�̂��ƂɂȂ�f�[�^ -�X�e�[�^�X�����l�Ɖ摜�Ƃ����蔻��f�[�^����܂Ƃ߂ɂ�������-)
	//�C���^�[�t�F�[�X�N���X�i����hp�\���̂݁j

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
	
	//�^�C�g����ʂȂǂɕ\������摜�̏�����
	//���Ԃ��󂢂����Ɋ֐������������
	//�u�摜�������I���v�Ƃ����R�����g�܂�
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

	//�摜�������I���


	//�v���C���[�����������܂�
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
				cout<<"player�̏������Ɏ��s���܂���"<<endl;
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
		cout<<"player�̏������Ɏ��s���܂���"<<endl;
		return;
	}
			
	cout<<"enemy�������I���"<<endl;		
	
	m_bIsInitialized=true;
}

//------------------------------------------------

void GameState::drawSet()
{	

	//���������������̓��S�\���̎��ȊO�ɍs���\���ł�
	//��ɔw�i�̕`��A�L�����N�^�[�̕`��A�e�̕`����s���܂�
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
	

	//���ꂼ��̃Q�[�����[�h�ŗL�̉摜�\�����s���܂�
	switch(m_sequence)
	{
		case SEQ_LOGO:
		{
			//���S��\�����܂�
			m_spDrawBufferInterface->setCellBlend(BLEND_ALPHA,m_tBlendPar);
			m_spDrawBufferInterface->DrawSetRota(m_spGraphLogo.get(),0,WINDOW_WIDTH/2,WINDOW_HEIGHT/2,0.0,1.0,false);
		}
		break;
		
		case SEQ_TITLE:
		{
			//�^�C�g����ʂ́u�x���X�e���̋R�m�v�̕�����`��
			m_spDrawBufferInterface->DrawSet(m_spGraphTitle.get(),0,0,0,false);
		}
		break;

		case SEQ_OVER:
		{
			//�Q�[���I�[�o�[�ɂȂ������ɔ������̍����摜��`��
			//�Q�[���I�[�o�[�̕�����`��
			m_spDrawBufferInterface->setCellBlend(BLEND_ALPHA,m_tBlendPar);
			m_spDrawBufferInterface->DrawSet(m_spGraphAllBlack.get(),0,0,0,false);
			m_spDrawBufferInterface->setCellBlend(BLEND_ALPHA,m_tBlendPar*2);
			m_spDrawBufferInterface->DrawSet(m_spGraphGameOver.get(),0,0,0,false);
			m_spDrawBufferInterface->resetCellBlend();
		}
		break;

		case SEQ_CLEAR:
		{
			//�N���A�̕����̕`��
			m_spDrawBufferInterface->setCellBlend(BLEND_ALPHA,m_tBlendPar);
			m_spDrawBufferInterface->DrawSet(m_spGraphClear.get(),0,0,0,false);		
			m_spDrawBufferInterface->resetCellBlend();
		}
		break;

		case SEQ_TEAM_MORIMOTO:
		{
			//����ҏ����������摜��`��
			m_spDrawBufferInterface->DrawSet(m_spGraphTeamMorimoto.get(),0,0,0,false);		
		}

		break;
	}
}

//------------------------------------------------

void GameState::initializeActorData(char *filePath)
{
	//���ׂĂ�acotrData�����������܂�
	//csv�t�@�C�����J���@�ő吔��ǂݏo�������������蓖�Ă��܂�
	//���̌�e���ڂ�ǂݏo���Ă͐ݒ�̌J��Ԃ��ł�
	//�₽�璷���͍̂��ڂ������ς����邩��ł�

	//�����̃R�����g��ǂ񂾕���
	//�����ł��X�}�[�g�ɂȂ鏑�����A�܂��A���S���Y���������m�ł����炲���󂭂�����

	TexRead texRead(filePath);

	if(texRead.isLoaded())
	{
		cout<<"�ǂݍ��ݐ��� GameState initializeActorData()"<<filePath<<endl;
	
		string str;

		char inputC[STRING_LENGTH];
		char* pLine;

		int pos=0;//���ǂ�ł���ʒu

//����ǂ݂���

		if(texRead.readLineSkipOverSolidus()==false)
		{
			cout<<"��蔭��"<<endl;	
		
			return;
		}
		pLine=texRead.getLine();
		pos=0;

		getNextStringToComma(inputC,pLine,&pos);//���̕������inputC�ɃR�s�[����@pLine[pos]����','�܂���'\n'�܂Ł@
	
		str=inputC;

		if(str!="<max>")//���e�ɊԈႢ������ꍇ
		{	
			return;	
		}

		getNextStringToComma(inputC,pLine,&pos);

		int max=atoi(inputC);

//���̓ǂݏo���I���

		if(max>0)
		{

			if(texRead.readLineSkipOverSolidus()==false)
			{
				cout<<"��蔭��"<<endl;	
				//reset();
				return;
			}
			
			pLine=texRead.getLine();
			pos=0;

			getNextStringToComma(inputC,pLine,&pos);
	
			str=inputC;

			if(str!="<path>")//���e�ɊԈႢ������ꍇ
			{	
				return;	
			}

			for(int i=0;i<max;i++)
			{
				if(texRead.readLineSkipOverSolidus()==false)
				{
					cout<<"��蔭��"<<endl;	
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
						cout<<"initialize���s�@�@"<<str.c_str()<<endl;
					}					
				}
				else 
				{	
					cout<<"initialize���s�@�@"<<str.c_str()<<endl;
				}			
			}
			cout<<"�ǂݍ��ݏI��"<<endl;
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
	//���ׂĂ�acotrData�����������܂�
	//csv�t�@�C�����J���@�ő吔��ǂݏo�����[�v�ɓ���܂�
	//�L�����N�^�[��1�΂��ƂɃ����������蓖�Ă��܂�
	//���̌�e���ڂ�ǂݏo���Ă͐ݒ�̌J��Ԃ��ł�
	//�₽�璷���̂͐ݒ荀�ڂ������ς����邩��ł�

	//�����̃R�����g��ǂ񂾕���
	//�����ł��X�}�[�g�ɂȂ鏑�����A�܂��A���S���Y���������m�ł����炲���󂭂�����

	TexRead texRead(filePath);

	if(texRead.isLoaded())
	{
		cout<<"�ǂݍ��ݐ��� GameState initializeActorData()"<<filePath<<endl;
	
		string str;

		char inputC[STRING_LENGTH];
		char* pLine;

		int pos=0;//���ǂ�ł���ʒu


//����ǂ݂���

		if(texRead.readLineSkipOverSolidus()==false)
		{
			cout<<"��蔭��"<<endl;	
		
			return;
		}
			pLine=texRead.getLine();
			pos=0;

		getNextStringToComma(inputC,pLine,&pos);//���̕������inputC�ɃR�s�[����@pLine[pos]����','�܂���'\n'�܂Ł@
	
		str=inputC;

		if(str!="<max>")//���e�ɊԈႢ������ꍇ
		{	
			return;	
		}

		getNextStringToComma(inputC,pLine,&pos);//���̕������inputC�ɃR�s�[����@pLine[pos]����','�܂���'\n'�܂Ł@

		int max=atoi(inputC);

		for(int i=0;i<max;i++)
		{
			double x;
			double z;
			string type;
			int aiType =0;

			if(texRead.readLineSkipOverSolidus()==false)
			{
				cout<<"��蔭��"<<endl;	
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
			
			
			cout<<"enemy������"<<endl;
			
			
			spActorData spActData;

			spActData=GameState::findSpActorDataNamed(type.c_str());
			
			if(spActData.get()!=NULL)
			{
				sp_Actor spAct;
				spAct=sp_Actor(new Enemy());//���������蓖��
			
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
	//�Q�[���̏��������s���܂�

	m_lSpActors.clear();	//���ׂẴL�����N�^�[�����X�g����폜 �f�X�g���N�^���Ă΂ꃁ��������������
							//���̎�m_spPlayer�����X�g�ɕۑ�����Ă��邪shared_ptr�̎Q�ƃJ�E���g���c���Ă��邽��
							//�v���C���[�̃f�[�^�����͗�O�Ń���������폜�͂���Ȃ�	���o�O�ł͂Ȃ�
	
	//�v���C���[�̍ď�����
	m_spPlayer->reset();
	m_spPlayer->setHpMax();
	m_spPlayer->setDrawBuffer(m_spDrawBufferGameObject,m_spDrawBufferShadow);
	m_spPlayer->setPosition(MOVE_MIN_X+50,0.0,(MOVE_MAX_Z-MOVE_MIN_Z)/2);
	m_spPlayer->setFirstPosition(MOVE_MIN_X,(MOVE_MAX_Z-MOVE_MIN_Z)/2);
	
	//�v���C���[�����X�g�ɒǉ�
	m_lSpActors.push_back(m_spPlayer);
	
	initializeEnemy("test.csv");


	m_spMap->setScrollMinX(MOVE_MIN_X);
	m_spMap->updateScroll(static_cast<int>(m_spPlayer->getX()));
}

//-------------------------------

bool GameState::isCleared()
{
	//�Q�[���N���A�������ǂ���
	//boss�t���O�����G�l�~�[�����݂��Ȃ��Ȃ�true��Ԃ� ��l�ł����݂��Ă���Ȃ�False
	
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