#include <Windows.h>
#include <iostream>

void Telekill()
{
	bool Ativar = false;
	float PosX, PosY, PosZ;
	DWORD BasePlayer = (*(DWORD*)((DWORD)(GetModuleHandleA("hw.dll")) + 0x7BBD9C));
	DWORD TotaldePlayers = (*(DWORD*)((DWORD)(GetModuleHandleA("steamclient_orig.dll")) + 0x30A988));
	while (TRUE)
	{
		if (GetAsyncKeyState(VK_INSERT) & 1)
			Ativar = !Ativar;

		if (Ativar)
		{
			for (int i = 0; i < *(BYTE*)(*(DWORD*)(TotaldePlayers + 0x30) + 0x428); i++)
			{
				if (*(float*)(BasePlayer + (i * 0x324) + 0x504) > 1.0f &&
					*(float*)(BasePlayer + (i * 0x324) + 0x504) <= 100.0f)
				{
					PosX = *(float*)(BasePlayer + (0x3AC + (i * 0x324)));
					PosZ = *(float*)(BasePlayer + (0x3B0 + (i * 0x324)));
					PosY = *(float*)(BasePlayer + (0x3B4 + (i * 0x324)));
					*(float*)(BasePlayer + 0x88) = PosX;
					*(float*)(BasePlayer + 0x8C) = PosZ;
					*(float*)(BasePlayer + 0x90) = PosY;
					break;
				}
			}
		}
	}
}

BOOL APIENTRY DllMain(HMODULE hmodule, DWORD dwReasonForCall, LPVOID lpReserved)
{
	if (dwReasonForCall == DLL_PROCESS_ATTACH)
	{
		CreateThread(0,0,(LPTHREAD_START_ROUTINE)Telekill,0,0,0);
	}
	return TRUE;
}
