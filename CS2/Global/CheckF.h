#pragma once
#include <windows.h>
BOOL CheckMoudle() noexcept{
	if (ModuleInfo.ClientModuleAddress && ModuleInfo.Engine2ModuleAddress && ModuleInfo.MatchmakingModuleAddress && ModuleInfo.ServerModuleAddress && ModuleInfo.SDL3ModuleAddress&& ModuleInfo.SteamaudioModuleAddress) {
		return TRUE;
	}
	return FALSE;
};
BOOL CheckGaming() noexcept {
	if (GameProcessInfo.GameProcess && GameProcessInfo.GamePid && isCurrentVersionAvailable) {
		return TRUE;
	}
	return FALSE;
};

BOOL CheckGetPlayerTime() noexcept{

}