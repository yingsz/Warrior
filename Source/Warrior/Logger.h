#pragma once
#include "UObject/ConstructorHelpers.h"  

DECLARE_LOG_CATEGORY_EXTERN(Game, Log, All)

#define LogDebug(format, ...) UE_LOG(Game, Display, TEXT("[Debug]" format), ##__VA_ARGS__ )
#define LoSys(format, ...) UE_LOG(Game, Display, TEXT("[Sys]" format), ##__VA_ARGS__ )
#define LogWarn(format, ...) UE_LOG(Game, Display, TEXT("[Warn]" format), ##__VA_ARGS__ )
#define LogFatal(format, ...) UE_LOG(Game, Display, TEXT("[Fatal]" format), ##__VA_ARGS__ )
#define LogError(format, ...) UE_LOG(Game, Display, TEXT("[Error]" format), ##__VA_ARGS__ )
#define LogAssert(b, ...) if(!(b))  LogError(__VA_ARGS__ )