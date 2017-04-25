#include "actorData.h"


//---------------------------------------
ActorData::ActorData()
{
	//�R���X�g���N�^
	//�l�����邾���̏�����������
	//�Q�[���p�̏�������initialize�ōs��
	//initialize�͂₽�璷���̂ł��̃t�@�C���̈�ԉ��ɏ����Ă��܂�

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
	//�f�X�g���N�^
	//�����o�|�C���^�ϐ���new�Ŋ��蓖�Ă����������J������

	cout<<"�f�X�g���N�^ ActorData,"<<m_name<<","<<m_filePath<<endl;

	SAFE_DELETE_ARRAY(m_pGraph2D_Arr);
	SAFE_DELETE_ARRAY(m_pFilePathForGraph_Arr);
	SAFE_DELETE_ARRAY(m_pGraphPatternData_Arr);
	
	m_hitAreaSet.reset();
	m_bIsInitialized=false;

	cout<<"-�f�X�g���N�^ ActorData end,"<<m_name<<","<<m_filePath<<endl;
	m_name="noName";
	m_filePathForHitArea="nodata";
	m_filePath="nodata";
}

//----------------------------------

void ActorData::reset()
{	
	//�����o�|�C���^�ϐ���new�Ŋ��蓖�Ă����������J����
	//�R���X�g���N�^�ō��ꂽ���Ɠ�����Ԃɖ߂�

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
	//�O���t�B�b�N�p�^�[���f�[�^��Ԃ��܂�
	//�O���t�B�b�N�p�^�[���f�[�^�ɂ͊e�A�j���[�V�������[�h�̉摜��\�����邽�߂́@
	//(�����ڂ̃O���t�B�b�N�V�[�g���g�p���邩,�摜�C���f�b�N�X,�A�j���[�V�����̍ő吔)
	//�̊e���ڂ��ۑ�����Ă��܂�
	
	//���s���ɂ͂��ׂ�0�̉摜��Ԃ��܂�

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
	//�L�����N�^�[�̉摜�ւ̃|�C���^��Ԃ��܂�
	//������i�͂��̃L�����N�^�[�ŉ����ڂ̉摜�����w�肵�܂�
	//���s���ɂ�null�|�C���^��Ԃ��܂�
	//NULL�|�C���^�ɗ���̂͂悭�Ȃ��Ƃ̘b�Ȃ̂ŎQ�Ƃ�Ԃ��悤�Ƀ��t�@�N�^�����O�\��
	
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
	//�e�̉摜�ւ̃|�C���^��Ԃ��܂�
	//������i�͂��̃L�����N�^�[�ŉ����ڂ̉摜�����w�肵�܂�
	//���s���ɂ�null�|�C���^��Ԃ��܂�
	//NULL�|�C���^�ɗ���̂͂悭�Ȃ��Ƃ̘b�Ȃ̂ŎQ�Ƃ�Ԃ��悤�Ƀ��t�@�N�^�����O�\��

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
	//�w�肵���ԍ��̃O���t�B�b�N�V�[�g��
	//���R�}���̃A�j���[�V�������L�^���Ă��邩��Ԃ��܂�
	//�͈͊O�Ȃ�0��Ԃ��܂�

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
	//�f�o�b�O�Ɏg�����֐��ł�
	//�R���\�[�����ɃI�u�W�F�N�g�̕ێ����Ă���f�[�^�����ׂď����o���܂�

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
	//���ׂẴ����o�ϐ������������܂�
	//csv�t�@�C�����J���e���ڂ�ǂݏo���Ă͐ݒ�̌J��Ԃ��ł�
	//�������̊��蓖�Ă��K�v�ȃ^�C�~���O�ɂ͊��蓖�Ă��s���܂�
	//�₽�璷���̂͐ݒ荀�ڂ������ς����邩��ł�

	//�����̃R�����g��ǂ񂾕���
	//�����ł��X�}�[�g�ɂȂ鏑�����A�܂��A���S���Y���������m�ł����炲���󂭂�����



	TexRead texRead(filePath);

	if(texRead.isLoaded())
	{
		m_filePath=filePath;
		cout<<"�ǂݍ��ݐ��� ActorData initialize()"<<m_filePath.c_str()<<endl;
	
		string str;

		char inputC[STRING_LENGTH];
		char* pLine;

		int pos=0;//���ǂ�ł���ʒu

//���O��ǂ݂���
		if(texRead.readLineSkipOverSolidus()==false)
		{
			cout<<"��蔭��"<<endl;	
			reset();
			return;
		}
			pLine=texRead.getLine();
			pos=0;

		getNextStringToComma(inputC,pLine,&pos);//���̕������inputC�ɃR�s�[����@pLine[pos]����','�܂���'\n'�܂Ł@
	
		str=inputC;

		if(str!="<name>")//���e�ɊԈႢ������ꍇ
		{	
			reset();
			return;	
		}

		getNextStringToComma(inputC,pLine,&pos);//���̕������inputC�ɃR�s�[����@pLine[pos]����','�܂���'\n'�܂Ł@

		m_name=inputC;

		cout<<m_name.c_str()<<endl;

//���O�̓ǂݏo���I��

//�O���t�B�b�N�̃V�[�g����ǂ݂���

//texRead��Line���X�V�@�ǂݏo���̉ߒ��Ńt�@�C�����I�����Ă��Ȃ����̃`�F�b�N
		if(texRead.readLineSkipOverSolidus()==false)
		{
			cout<<"��蔭��"<<endl;	
			reset();
			return;
		}
			pLine=texRead.getLine();
			pos=0;

		getNextStringToComma(inputC,pLine,&pos);//���̕������inputC�ɃR�s�[����@pLine[pos]����','�܂���'\n'�܂Ł@
	
		str=inputC;

		if(str!="<gMax>")//���e�ɊԈႢ������ꍇ
		{	
			reset();
			return;	
		}

		getNextStringToComma(inputC,pLine,&pos);//���̕������inputC�ɃR�s�[����@pLine[pos]����','�܂���'\n'�܂Ł@

		m_GraphMax=atoi(inputC);
//�O���t�B�b�N�V�[�g���̓ǂݏo���I��


//�g�p���郂�[�h���̓ǂݏo��

		//texRead��Line���X�V�@�ǂݏo���̉ߒ��Ńt�@�C�����I�����Ă��Ȃ����̃`�F�b�N
		if(texRead.readLineSkipOverSolidus()==false)
		{
			cout<<"��蔭��"<<endl;	
			reset();
			return;
		}
		pLine=texRead.getLine();
		pos=0;
		
		getNextStringToComma(inputC,pLine,&pos);//���̕������inputC�ɃR�s�[����@pLine[pos]����','�܂���'\n'�܂Ł@

		str=inputC;

		if(str!="<mMax>")//���e�ɊԈႢ������ꍇ
		{	
			reset();
			return;	
		}

		getNextStringToComma(inputC,pLine,&pos);//���̕������inputC�ɃR�s�[����@pLine[pos]����','�܂���'\n'�܂Ł@

		m_modeMax=atoi(inputC);

//�g�p���郂�[�h���̓ǂݏo���I��

//�ő�HP�̓ǂݏo��

		//texRead��Line���X�V�@�ǂݏo���̉ߒ��Ńt�@�C�����I�����Ă��Ȃ����̃`�F�b�N
		if(texRead.readLineSkipOverSolidus()==false)
		{
			cout<<"��蔭��"<<endl;	
			reset();
			return;
		}
		pLine=texRead.getLine();
		pos=0;
		
		getNextStringToComma(inputC,pLine,&pos);//���̕������inputC�ɃR�s�[����@pLine[pos]����','�܂���'\n'�܂Ł@

		str=inputC;

		if(str!="<maxHp>")//���e�ɊԈႢ������ꍇ
		{	
			reset();
			return;	
		}

		getNextStringToComma(inputC,pLine,&pos);//���̕������inputC�ɃR�s�[����@pLine[pos]����','�܂���'\n'�܂Ł@

		m_maxHp=atoi(inputC);

//�ő�HP�̓ǂݏo���I��


//�U���͈�x���@

		//texRead��Line���X�V�@�ǂݏo���̉ߒ��Ńt�@�C�����I�����Ă��Ȃ����̃`�F�b�N
		if(texRead.readLineSkipOverSolidus()==false)
		{
			cout<<"��蔭��"<<endl;	
			reset();
			return;
		}
		pLine=texRead.getLine();
		pos=0;
		
		getNextStringToComma(inputC,pLine,&pos);//���̕������inputC�ɃR�s�[����@pLine[pos]����','�܂���'\n'�܂Ł@

		str=inputC;

		if(str!="<atackRangeX>")//���e�ɊԈႢ������ꍇ
		{	
			reset();
			return;	
		}

		getNextStringToComma(inputC,pLine,&pos);//���̕������inputC�ɃR�s�[����@pLine[pos]����','�܂���'\n'�܂Ł@

		m_atackRangeX=atoi(inputC);

//�U���͈�x�̓ǂݏo���I��

//�U���͈�z���@

		//texRead��Line���X�V�@�ǂݏo���̉ߒ��Ńt�@�C�����I�����Ă��Ȃ����̃`�F�b�N
		if(texRead.readLineSkipOverSolidus()==false)
		{
			cout<<"��蔭��"<<endl;	
			reset();
			return;
		}
		pLine=texRead.getLine();
		pos=0;
		
		getNextStringToComma(inputC,pLine,&pos);//���̕������inputC�ɃR�s�[����@pLine[pos]����','�܂���'\n'�܂Ł@

		str=inputC;

		if(str!="<atackRangeZ>")//���e�ɊԈႢ������ꍇ
		{	
			reset();
			return;	
		}

		getNextStringToComma(inputC,pLine,&pos);//���̕������inputC�ɃR�s�[����@pLine[pos]����','�܂���'\n'�܂Ł@

		m_atackRangeZ=atoi(inputC);

//�U���͈͂��̓ǂݏo���I��

//�U��

		//texRead��Line���X�V�@�ǂݏo���̉ߒ��Ńt�@�C�����I�����Ă��Ȃ����̃`�F�b�N
		if(texRead.readLineSkipOverSolidus()==false)
		{
			cout<<"��蔭��"<<endl;	
			reset();
			return;
		}
		pLine=texRead.getLine();
		pos=0;
		
		getNextStringToComma(inputC,pLine,&pos);//���̕������inputC�ɃR�s�[����@pLine[pos]����','�܂���'\n'�܂Ł@

		str=inputC;

		if(str!="<atackPoint>")//���e�ɊԈႢ������ꍇ
		{	
			reset();
			return;	
		}

		getNextStringToComma(inputC,pLine,&pos);//���̕������inputC�ɃR�s�[����@pLine[pos]����','�܂���'\n'�܂Ł@

		m_atackPoint=atoi(inputC);

//�U��

//�h��
		//texRead��Line���X�V�@�ǂݏo���̉ߒ��Ńt�@�C�����I�����Ă��Ȃ����̃`�F�b�N
		if(texRead.readLineSkipOverSolidus()==false)
		{
			cout<<"��蔭��"<<endl;	
			reset();
			return;
		}
		pLine=texRead.getLine();
		pos=0;
		
		getNextStringToComma(inputC,pLine,&pos);//���̕������inputC�ɃR�s�[����@pLine[pos]����','�܂���'\n'�܂Ł@

		str=inputC;

		if(str!="<defencePoint>")//���e�ɊԈႢ������ꍇ
		{	
			reset();
			return;	
		}

		getNextStringToComma(inputC,pLine,&pos);//���̕������inputC�ɃR�s�[����@pLine[pos]����','�܂���'\n'�܂Ł@

		m_defencePoint=atoi(inputC);

//�h��

//�ړ��X�s�[�h�̓ǂݏo��

		//texRead��Line���X�V�@�ǂݏo���̉ߒ��Ńt�@�C�����I�����Ă��Ȃ����̃`�F�b�N
		if(texRead.readLineSkipOverSolidus()==false)
		{
			cout<<"��蔭��"<<endl;	
			reset();
			return;
		}
		pLine=texRead.getLine();
		pos=0;
		
		getNextStringToComma(inputC,pLine,&pos);//���̕������inputC�ɃR�s�[����@pLine[pos]����','�܂���'\n'�܂Ł@

		str=inputC;

		if(str!="<speedLR>")//���e�ɊԈႢ������ꍇ
		{	
			reset();
			return;	
		}

		getNextStringToComma(inputC,pLine,&pos);//���̕������inputC�ɃR�s�[����@pLine[pos]����','�܂���'\n'�܂Ł@

		m_speedLR=atof(inputC);

//�ړ��X�s�[�h�̓ǂݏo���I��

//�g�p���郂�[�h���̓ǂݏo��

//texRead��Line���X�V�@�ǂݏo���̉ߒ��Ńt�@�C�����I�����Ă��Ȃ����̃`�F�b�N
		if(texRead.readLineSkipOverSolidus()==false)
		{
			cout<<"��蔭��"<<endl;	
			reset();
			return;
		}
		pLine=texRead.getLine();
		pos=0;
		
		getNextStringToComma(inputC,pLine,&pos);//���̕������inputC�ɃR�s�[����@pLine[pos]����','�܂���'\n'�܂Ł@

		str=inputC;

		if(str!="<speedZ>")//���e�ɊԈႢ������ꍇ
		{	
			reset();
			return;	
		}

		getNextStringToComma(inputC,pLine,&pos);//���̕������inputC�ɃR�s�[����@pLine[pos]����','�܂���'\n'�܂Ł@

		m_speedZ=atof(inputC);

//�g�p���郂�[�h���̓ǂݏo���I��

//�����蔻��̃f�[�^�t�@�C���̃p�X�̓ǂݏo��

		//texRead��Line���X�V�@�ǂݏo���̉ߒ��Ńt�@�C�����I�����Ă��Ȃ����̃`�F�b�N
		if(texRead.readLineSkipOverSolidus()==false)
		{
			cout<<"��蔭��"<<endl;	
			reset();
			return;
		}
		pLine=texRead.getLine();
		pos=0;
		
		getNextStringToComma(inputC,pLine,&pos);

		str=inputC;

		if(str!="<hPath>")//���e�ɊԈႢ������ꍇ
		{	
			reset();
			return;	
		}

		getNextStringToComma(inputC,pLine,&pos);//���̕������inputC�ɃR�s�[����@pLine[pos]����','�܂���'\n'�܂Ł@

		m_filePathForHitArea=inputC;

//�����蔻��̃f�[�^�t�@�C���̃p�X�̓ǂݏo���I��

//�����蔻��(�U���G���A)�̃f�[�^�t�@�C���̃p�X�̓ǂݏo��

		//texRead��Line���X�V�@�ǂݏo���̉ߒ��Ńt�@�C�����I�����Ă��Ȃ����̃`�F�b�N
		if(texRead.readLineSkipOverSolidus()==false)
		{
			cout<<"��蔭��"<<endl;	
			reset();
			return;
		}
		pLine=texRead.getLine();
		pos=0;
		
		getNextStringToComma(inputC,pLine,&pos);

		str=inputC;

		if(str!="<aPath>")//���e�ɊԈႢ������ꍇ
		{	
			reset();
			return;	
		}

		getNextStringToComma(inputC,pLine,&pos);//���̕������inputC�ɃR�s�[����@pLine[pos]����','�܂���'\n'�܂Ł@

		m_filePathForAtackArea=inputC;

//�����蔻��(�U���G���A)�̃f�[�^�t�@�C���̃p�X�̓ǂݏo���I��

//�O���t�B�b�N�̃p�X�̓ǂݏo��
			
		//texRead��Line���X�V�@�ǂݏo���̉ߒ��Ńt�@�C�����I�����Ă��Ȃ����̃`�F�b�N
		if(texRead.readLineSkipOverSolidus()==false)
		{
			cout<<"��蔭��"<<endl;	
			reset();
			return;
		}
		pLine=texRead.getLine();
		pos=0;

		getNextStringToComma(inputC,pLine,&pos);//���̕������inputC�ɃR�s�[����@pLine[pos]����','�܂���'\n'�܂Ł@

		str=inputC;

		if(str!="<gPath>")//���e�ɊԈႢ������ꍇ
		{	
			reset();
			return;	
		}

		if(m_GraphMax>0&&m_pFilePathForGraph_Arr==NULL)//���������蓖��
		{
			m_pFilePathForGraph_Arr=new string[m_modeMax];
		}
		else 
		{
			reset();
			return;
		}

		if(m_pFilePathForGraph_Arr==NULL)//���������蓖�ĂɎ��s���Ă��Ȃ����̃`�F�b�N
		{
			reset();
			return;
		}

		for(int i=0;i<m_GraphMax;i++)
		{
			//texRead��Line���X�V�@�ǂݏo���̉ߒ��Ńt�@�C�����I�����Ă��Ȃ����̃`�F�b�N
			if(texRead.readLineSkipOverSolidus()==false)
			{
				cout<<"��蔭��"<<endl;	
				reset();
				return;
			}
			pLine=texRead.getLine();
			pos=0;

			getNextStringToComma(inputC,pLine,&pos);//���̕������inputC�ɃR�s�[����@pLine[pos]����','�܂���'\n'�܂Ł@
			
			m_pFilePathForGraph_Arr[i]=inputC;
		}


		//�e�̃f�[�^��ǂݏo��

		if(m_GraphMax>0&&m_pFilePathForGraph_Shadow_Arr==NULL)//���������蓖��
		{
			m_pFilePathForGraph_Shadow_Arr=new string[m_modeMax];
		}
		else 
		{
			reset();
			return;
		}

		if(m_pFilePathForGraph_Shadow_Arr==NULL)//���������蓖�ĂɎ��s���Ă��Ȃ����̃`�F�b�N
		{
			reset();
			return;
		}

		for(int i=0;i<m_GraphMax;i++)
		{
			//texRead��Line���X�V�@�ǂݏo���̉ߒ��Ńt�@�C�����I�����Ă��Ȃ����̃`�F�b�N
			if(texRead.readLineSkipOverSolidus()==false)
			{
				cout<<"��蔭��"<<endl;	
				reset();
				return;
			}
			pLine=texRead.getLine();
			pos=0;

			getNextStringToComma(inputC,pLine,&pos);//���̕������inputC�ɃR�s�[����@pLine[pos]����','�܂���'\n'�܂Ł@
			
			m_pFilePathForGraph_Shadow_Arr[i]=inputC;
		}


//�O���t�B�b�N�̃p�X�ǂݏo���I��

//���C���̓ǂݏo���y�ѓǂݔ�΂��s�̔��f
		//texRead��Line���X�V�@�ǂݏo���̉ߒ��Ńt�@�C�����I�����Ă��Ȃ����̃`�F�b�N
		if(texRead.readLineSkipOverSolidus()==false)
		{
			cout<<"��蔭��"<<endl;	
			reset();
			return;
		}
		pLine=texRead.getLine();
		pos=0;

		getNextStringToComma(inputC,pLine,&pos);//���̕������inputC�ɃR�s�[����@pLine[pos]����','�܂���'\n'�܂Ł@

		str=inputC;

		if(str!="<gpData>")//���e�ɊԈႢ������ꍇ
		{	
			reset();
			return;	
		}

		if(m_modeMax>0&&m_pGraphPatternData_Arr==NULL)//���������蓖��
		{
			m_pGraphPatternData_Arr=new GraphPatternData[m_modeMax];
		}
		else 
		{
			reset();
			return;
		}

		if(m_pGraphPatternData_Arr==NULL)//���������蓖�ĂɎ��s���Ă��Ȃ����̃`�F�b�N
		{
			reset();
			return;
		}

		for(int i=0;i<m_modeMax;i++)
		{
		//���C���̓ǂݏo���y�ѓǂݔ�΂��s�̔��f
			//texRead��Line���X�V�@�ǂݏo���̉ߒ��Ńt�@�C�����I�����Ă��Ȃ����̃`�F�b�N
			if(texRead.readLineSkipOverSolidus()==false)
			{
				cout<<"��蔭��"<<endl;	
				reset();
				return;
			}
			pLine=texRead.getLine();
			pos=0;
	
			int data[3];//sheetNum index max�̃f�[�^���i�[����


			for(int j=0;j<3;j++)
			{
				getNextStringToComma(inputC,pLine,&pos);//���̕������inputC�ɃR�s�[����@pLine[pos]����','�܂���'\n'�܂Ł@

				data[j]=atoi(inputC);
			}

			m_pGraphPatternData_Arr[i].m_sheetNum=data[0];
			m_pGraphPatternData_Arr[i].m_index=data[1];
			m_pGraphPatternData_Arr[i].m_max=data[2];
		}
//�摜�̃��[�h�ɕK�v�Ȓl��ǂ݂����ĉ摜�̃��[�h������ �͂���

		//texRead��Line���X�V�@�ǂݏo���̉ߒ��Ńt�@�C�����I�����Ă��Ȃ����̃`�F�b�N
		if(texRead.readLineSkipOverSolidus()==false)
		{
			cout<<"��蔭��"<<endl;	
			reset();
			return;
		}
		pLine=texRead.getLine();
		pos=0;

		getNextStringToComma(inputC,pLine,&pos);//���̕������inputC�ɃR�s�[����@pLine[pos]����','�܂���'\n'�܂Ł@

		str=inputC;

		if(str!="<grData>")//���e�ɊԈႢ������ꍇ
		{	
			reset();
			return;	
		}

		if(m_GraphMax>0&&m_pGraph2D_Arr==NULL)//���������蓖��
		{
			m_pGraph2D_Arr=new Graphics2D[m_GraphMax];
		}
		else 
		{
			reset();
			return;
		}

		if(m_pGraph2D_Arr==NULL)//���������蓖�ĂɎ��s���Ă��Ȃ����̃`�F�b�N
		{
			reset();
			return;
		}

		if(m_GraphMax>0&&m_pGraph2D_Shadow_Arr==NULL)//���������蓖��
		{
			m_pGraph2D_Shadow_Arr=new Graphics2D[m_GraphMax];
		}
		else 
		{
			reset();
			return;
		}

		if(m_pGraph2D_Shadow_Arr==NULL)//���������蓖�ĂɎ��s���Ă��Ȃ����̃`�F�b�N
		{
			reset();
			return;
		}

		for(int i=0;i<m_GraphMax;i++)
		{

			//texRead��Line���X�V�@�ǂݏo���̉ߒ��Ńt�@�C�����I�����Ă��Ȃ����̃`�F�b�N
			if(texRead.readLineSkipOverSolidus()==false)
			{
				cout<<"��蔭��"<<endl;	
				reset();
				return;
			}
			pLine=texRead.getLine();
			pos=0;
	
			int data[5];//max xSize ySize xNum yNum�̃f�[�^���i�[����

			for(int j=0;j<5;j++)
			{
				getNextStringToComma(inputC,pLine,&pos);//���̕������inputC�ɃR�s�[����@pLine[pos]����','�܂���'\n'�܂Ł@

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

//�摜�̃��[�h�ɕK�v�Ȓl��ǂ݂����ĉ摜�̃��[�h������ �I���

//�L�����N�^�[�̃T�C�Y�����[�h����@
	
		//texRead��Line���X�V�@�ǂݏo���̉ߒ��Ńt�@�C�����I�����Ă��Ȃ����̃`�F�b�N
		if(texRead.readLineSkipOverSolidus()==false)
		{
			cout<<"��蔭��"<<endl;	
			reset();
			return;
		}
		pLine=texRead.getLine();
		pos=0;

		getNextStringToComma(inputC,pLine,&pos);//���̕������inputC�ɃR�s�[����@pLine[pos]����','�܂���'\n'�܂Ł@

		str=inputC;

		if(str!="<size>")//���e�ɊԈႢ������ꍇ
		{	
			reset();
			return;	
		}

		//texRead��Line���X�V�@�ǂݏo���̉ߒ��Ńt�@�C�����I�����Ă��Ȃ����̃`�F�b�N
		if(texRead.readLineSkipOverSolidus()==false)
		{
			cout<<"��蔭��"<<endl;	
			reset();
			return;
		}
		pLine=texRead.getLine();
		pos=0;
		getNextStringToComma(inputC,pLine,&pos);//���̕������inputC�ɃR�s�[����@pLine[pos]����','�܂���'\n'�܂Ł@
		m_sizeX=atoi(inputC);
		getNextStringToComma(inputC,pLine,&pos);//���̕������inputC�ɃR�s�[����@pLine[pos]����','�܂���'\n'�܂Ł@
		m_sizeZ=atoi(inputC);

//�L�����N�^�[�̃T�C�Y�����[�h����I���

		//���蔻��̃f�[�^�����[�h����
		m_hitAreaSet.initialize(m_filePathForHitArea.c_str());
		if(!(m_hitAreaSet.isInitialized()))
		{
			reset();
			return;
		}
	
		if(m_filePathForAtackArea!="nodata")
		{
			m_atackAreaSet.initialize(m_filePathForAtackArea.c_str());//�U���͈͂̃��[�h
			m_atackAreaSet.show();
		}
		
		m_bIsInitialized=true;

	}
	else 
	{
		cout<<"�ǂݍ��݂Ɏ��s���܂��� ActorData initialize()"<<filePath<<endl;
	}

}
