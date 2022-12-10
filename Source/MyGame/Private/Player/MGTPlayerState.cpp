// MyGameTry, All Rights Reserved


#include "Player/MGTPlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LogMGTPlayerState, All, All);

  void AMGTPlayerState::LogInfo() 
  {
      UE_LOG(LogMGTPlayerState, Display, TEXT("TeamaID: %i, Kills: %i, Deaths: %i"), TeamID, KillsNum, DeathNum);
  }