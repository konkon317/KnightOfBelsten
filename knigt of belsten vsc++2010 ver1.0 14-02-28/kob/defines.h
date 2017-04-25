

#ifndef SAFE_DELETE
#define SAFE_DELETE(p){		if(p!=NULL){delete(p);	(p)=NULL;}	}
#endif

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p){	if(p!=NULL){delete[](p);	(p)=NULL;}	}
#endif

#ifndef INCLUDES
#define INCLUDES

#include <iostream>
#include <boost\shared_ptr.hpp>
#include <string>
#include <list>
#include <windows.h>
using namespace std;

#endif


/*今回は使用しない
#ifndef GRAVITATIONAL_ACCELERATION
#define GRAVITATIONAL_ACCELERATION	10.0	//9.80655  //g=9.8 m/s^2
#endif
*/


#ifndef WINDOW_WIDTH
#define WINDOW_WIDTH 1024
#endif

#ifndef WINDOW_HEIGHT
#define WINDOW_HEIGHT 768
#endif


#ifndef FILE_PATH_LENGTH
#define FILE_PATH_LENGTH 128 //ファイルパスの長さ
#endif

#ifndef STRING_LENGTH
#define STRING_LENGTH 256
#endif


#ifndef ROAD_SIZE
#define ROAD_SIZE

#define ROAD_SIZE_X 512

#endif

#ifndef MOVE_MAX_AND_MIN
#define MOVE_MAX_AND_MIN

#define STAGE_SIZE_Z 310

#define MOVE_MAX_Z 280
#define MOVE_MIN_Z 40
#define MOVE_MAX_X 1024*5 -30
#define MOVE_MIN_X -512



#define BACK_GROUND_OBJECT_BASE_Y 458
#define FRONT_OBJECT_BASE_Y 768

#endif
