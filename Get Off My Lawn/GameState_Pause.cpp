#include "GameState_Pause.h"
#include "LogicComponents.h"
#include "SystemComponents.h"
#include "RenderManager.h"

void GameState_Pause_Load()
{

}

void GameState_Pause_Update()
{
	if (AEInputCheckTriggered(AEVK_P) || AEInputCheckTriggered(AEVK_ESCAPE))
		gAEGameStateCurr = gAEGameStateNext;
}

void GameState_Pause_Draw()
{
	Print_Text(system_components.font_manager_->Get_Font(F_GAME_UI_TEXT), "PAUSED", (int)AEGfxGetWinMaxX() - 600, (int)AEGfxGetWinMaxY() - 300, 1.0f, 1.0f, 0);
}

void GameState_Pause_Unload()
{

}
