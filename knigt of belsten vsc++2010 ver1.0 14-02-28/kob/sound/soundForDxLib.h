#ifndef INCLUDE_SOUND_H
#define INCLUDE_SOUND_H

#include "..\defines.h"

class Sound;

//typedef
typedef boost::shared_ptr<Sound> sp_Sound;//スマートポインタ
typedef std::list<sp_Sound> list_sp_Sound;

//extern変数
extern list_sp_Sound g_SoundList;

//extern関数
extern void initializeSoundsList(const char* headerPath);
extern sp_Sound findSoundNamed(const char* Name);
extern void playSound(const char * name,bool useLoop=false);
extern void stopSound(const char * name);

//クラス
class Sound
{
	int m_handle;
	string m_name;
	string m_filePath;

public:
	Sound();
	~Sound();

	void initialize(const char* filePath,const char* name);

	const int getHandle()const{return m_handle;}
	const string getFilePath()const{return m_name;}
	const string getName()const{return m_name;}
};








#endif