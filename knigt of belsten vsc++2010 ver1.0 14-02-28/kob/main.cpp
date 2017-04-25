#include "DxLib.h"

#include "defines.h"


#include "2DGraph\2DGraphForDxLib.h"


#include "2DGraph\Draw2DForDxLib.h"
#include "2DGraph\2DGraphForDxLib.h"

#include "sound\soundForDxLib.h"

#include "input\InputForDxLib.h"

#include "gameObject/gameState.h"

#include <iostream>
using namespace std;

sp_DrawBuffer g_spDrawBufferBackGroundFarEnd;
sp_DrawBuffer g_spDrawBufferBackGround;
sp_DrawBuffer g_spDrawBufferBackGroundFront;

sp_DrawBuffer g_spDrawBufferShadow;
sp_DrawBuffer g_spDrawBufferGameObject;

sp_DrawBuffer g_spDrawBufferInterface;

int x=0;

GameState* g_pGameState=NULL;
Input* g_pInput=NULL;


int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int)
{

	AllocConsole();
    freopen("CONOUT$", "w", stdout);
    freopen("CONIN$", "r", stdin);	

	ChangeWindowMode(true);
	SetGraphMode(WINDOW_WIDTH,WINDOW_HEIGHT,16);

	SetMainWindowText( "knight of belsten") ;
	
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);	
	
	g_pInput =new Input(1,true);//インプットインスタンス
	g_pGameState=new GameState();


	//描画する情報を一時保存しておくためのバッファ
	g_spDrawBufferBackGroundFarEnd	=sp_DrawBuffer(new DrawBuffer());
	g_spDrawBufferBackGround		=sp_DrawBuffer(new DrawBuffer());
	g_spDrawBufferBackGroundFront	=sp_DrawBuffer(new DrawBuffer());
	g_spDrawBufferShadow			=sp_DrawBuffer(new DrawBuffer());
	g_spDrawBufferGameObject		=sp_DrawBuffer(new DrawBuffer());	
	g_spDrawBufferInterface			=sp_DrawBuffer(new DrawBuffer());

	//サウンドを読み込みます
	initializeSoundsList("soundFile/header.csv");
	
	
	if(g_pGameState!=NULL&&g_pInput!=NULL)
	{

	while(ScreenFlip()==0&&ProcessMessage()==0&&ClearDrawScreen()==0)//メインループ
	{		
		g_pInput->scan();

		//ボタンが押されていれば終了する
		if(g_pInput->keyCt(KEY_INPUT_ESCAPE)>=30)
		{
			break;
		}
		if(g_pInput->PadCt(0,PAD_BUTTON_BACK)>=30)
		{
			break;
		}
			
	
		if(g_pGameState->isInitialized()==false)
		{
			//ゲーム状態の初期化
			g_pGameState->setDrawBuffer(g_spDrawBufferBackGroundFarEnd	,g_spDrawBufferBackGround,
										g_spDrawBufferBackGroundFront	,g_spDrawBufferGameObject,
										g_spDrawBufferShadow			,g_spDrawBufferInterface	
										);
			g_pGameState->initialize(g_pInput);
		}
		else
		{
			//ゲームのアップデート
			g_pGameState->update();

			//描画
			//バッファに描画用データを保存しまうす
			g_pGameState->drawSet();

			//ソートをするべきバッファはソートする
			g_spDrawBufferBackGroundFarEnd	->sortZ();
			g_spDrawBufferShadow			->sortZ();
			g_spDrawBufferGameObject		->sortZ();
			g_spDrawBufferBackGround		->sortZ();
			g_spDrawBufferBackGroundFront	->sortZ();

			//各バッファに保存された描画データをもとに描画する
			g_spDrawBufferBackGroundFarEnd	->DrawAll();	
			g_spDrawBufferBackGround		->DrawAll();
			g_spDrawBufferShadow			->DrawAll();
			g_spDrawBufferGameObject		->DrawAll();
			g_spDrawBufferBackGroundFront	->DrawAll();
			g_spDrawBufferInterface			->DrawAll();
				
			//描画後に各バッファの内容をリセットする
			g_spDrawBufferBackGroundFarEnd	->resetVCell();
			g_spDrawBufferBackGround		->resetVCell();
			g_spDrawBufferBackGroundFront	->resetVCell();
			g_spDrawBufferShadow			->resetVCell();
			g_spDrawBufferGameObject		->resetVCell();		
			g_spDrawBufferInterface			->resetVCell();
		}

	}
	}

	//クラスの削除（メモリの解放）インスタンス化したのとは逆の順番で解放
	SAFE_DELETE(g_pGameState);
	SAFE_DELETE(g_pInput);

	g_spDrawBufferBackGroundFarEnd	.reset();
	g_spDrawBufferBackGround		.reset();
	g_spDrawBufferBackGroundFront	.reset();
	g_spDrawBufferShadow			.reset();
	g_spDrawBufferGameObject		.reset();	
	g_spDrawBufferInterface			.reset();	

	//dxLibを終了する
	DxLib_End();

	//EndLog_sharedPtr();

return 0;

}