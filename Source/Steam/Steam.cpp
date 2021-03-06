/*
    Initial author: Convery (tcn@ayria.se)
    Started: 03-08-2017
    License: MIT
    Notes:
        Steam exports implementation.
*/

#include "../Stdinclude.hpp"

#if defined(_WIN32)
// Steam components.
constexpr const char *Gameoverlay = sizeof(void *) == sizeof(uint64_t) ? "gameoverlayrenderer64.dll" : "gameoverlayrenderer.dll";
constexpr const char *Clientlibrary = sizeof(void *) == sizeof(uint64_t) ? "steamclient64.dll" : "steamclient.dll";
constexpr const char *Steamregistry = sizeof(void *) == sizeof(uint64_t) ? "Software\\Wow6432Node\\Valve\\Steam" : "Software\\Valve\\Steam";
#endif

// Configuration.
namespace Steamconfig
{
    // Application info.
    char Language[32]{ "english" };
    uint32_t ApplicationID{ 0 };
    uint64_t Startuptimestamp{ uint64_t(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count()) };

    // Network access.
    bool LAN{ false };
    bool Server{ false };
    bool Offline{ true };

    // User information.
    char Path[260]{};
    uint64_t UserID{ 0x1100001DEADC0DE };
    char Username[17]{ "Ayria" };
}

extern "C"
{
    // Interface access.
    EXPORT_ATTR void *SteamInternal_CreateInterface(const char *Interfacename)
    {
        /*
            NOTE(Convery):
            This export is generally only used by DRM/anti-tampering systems.
            As such this will likely cause a detection as they often check if
            the address returned resides in steamclient(64).dll.

            NOTE(Convery):
            The aforementioned issue can be solved via the "STMSIGBypass"
            plugin provided by Hedgehogscience on Github.
        */

        return Interfacemanager::Fetchinterface(Interfacename);
    }
    EXPORT_ATTR void *SteamAppList()
    {
        return Interfacemanager::Fetchinterface(STEAM_APPLIST);
    }
    EXPORT_ATTR void *SteamApps()
    {
        return Interfacemanager::Fetchinterface(STEAM_APPS);
    }
    EXPORT_ATTR void *SteamClient()
    {
        return Interfacemanager::Fetchinterface(STEAM_CLIENT);
    }
    EXPORT_ATTR void *SteamController()
    {
        return Interfacemanager::Fetchinterface(STEAM_CONTROLLER);
    }
    EXPORT_ATTR void *SteamFriends()
    {
        return Interfacemanager::Fetchinterface(STEAM_FRIENDS);
    }
    EXPORT_ATTR void *SteamGameServer()
    {
        return Interfacemanager::Fetchinterface(STEAM_GAMESERVER);
    }
    EXPORT_ATTR void *SteamGameServerHTTP()
    {
        return Interfacemanager::Fetchinterface(STEAM_HTTP);
    }
    EXPORT_ATTR void *SteamGameServerInventory()
    {
        return Interfacemanager::Fetchinterface(STEAM_INVENTORY);
    }
    EXPORT_ATTR void *SteamGameServerNetworking()
    {
        return Interfacemanager::Fetchinterface(STEAM_NETWORKING);
    }
    EXPORT_ATTR void *SteamGameServerStats()
    {
        return Interfacemanager::Fetchinterface(STEAM_GAMESERVERSTATS);
    }
    EXPORT_ATTR void *SteamGameServerUGC()
    {
        return Interfacemanager::Fetchinterface(STEAM_UGC);
    }
    EXPORT_ATTR void *SteamGameServerUtils()
    {
        return Interfacemanager::Fetchinterface(STEAM_UTILS);
    }
    EXPORT_ATTR void *SteamHTMLSurface()
    {
        return Interfacemanager::Fetchinterface(STEAM_HTMLSURFACE);
    }
    EXPORT_ATTR void *SteamHTTP()
    {
        return Interfacemanager::Fetchinterface(STEAM_HTTP);
    }
    EXPORT_ATTR void *SteamInventory()
    {
        return Interfacemanager::Fetchinterface(STEAM_INVENTORY);
    }
    EXPORT_ATTR void *SteamMatchmaking()
    {
        return Interfacemanager::Fetchinterface(STEAM_MATCHMAKING);
    }
    EXPORT_ATTR void *SteamMatchmakingServers()
    {
        return Interfacemanager::Fetchinterface(STEAM_MATCHMAKINGSERVERS);
    }
    EXPORT_ATTR void *SteamMusic()
    {
        return Interfacemanager::Fetchinterface(STEAM_MUSIC);
    }
    EXPORT_ATTR void *SteamMusicRemote()
    {
        return Interfacemanager::Fetchinterface(STEAM_MUSICREMOTE);
    }
    EXPORT_ATTR void *SteamNetworking()
    {
        return Interfacemanager::Fetchinterface(STEAM_NETWORKING);
    }
    EXPORT_ATTR void *SteamRemoteStorage()
    {
        return Interfacemanager::Fetchinterface(STEAM_REMOTESTORAGE);
    }
    EXPORT_ATTR void *SteamScreenshots()
    {
        return Interfacemanager::Fetchinterface(STEAM_SCREENSHOTS);
    }
    EXPORT_ATTR void *SteamUnifiedMessages()
    {
        return Interfacemanager::Fetchinterface(STEAM_UNIFIEDMESSAGES);
    }
    EXPORT_ATTR void *SteamUGC()
    {
        return Interfacemanager::Fetchinterface(STEAM_UGC);
    }
    EXPORT_ATTR void *SteamUser()
    {
        return Interfacemanager::Fetchinterface(STEAM_USER);
    }
    EXPORT_ATTR void *SteamUserStats()
    {
        return Interfacemanager::Fetchinterface(STEAM_USERSTATS);
    }
    EXPORT_ATTR void *SteamUtils()
    {
        return Interfacemanager::Fetchinterface(STEAM_UTILS);
    }
    EXPORT_ATTR void *SteamVideo()
    {
        return Interfacemanager::Fetchinterface(STEAM_VIDEO);
    }
    EXPORT_ATTR void *SteamMasterServerUpdater()
    {
        return Interfacemanager::Fetchinterface(STEAM_MASTERSERVERUPDATER);
    }

    // Initialization and shutdown.
    EXPORT_ATTR bool SteamAPI_Init()
    {
        Printfunction();

        auto Commandlinecontains = [](std::string_view Needle) -> bool
        {
            #if defined (_WIN32)
            return !!std::strstr(GetCommandLineA(), Needle.data());
            #else
            std::FILE *Filehandle = std::fopen("/proc/self/cmdline", "r");
            char Buffer[1024]{};
            if(Filehandle)
            {
                std::fgets(Buffer, 1024, Filehandle);
                std::fclose(Filehandle);
            }
            return !!std::strstr(Buffer, Needle.data());
            #endif
        };

        /*
            Some games are too old to use SteamAPI_RestartAppIfNecessary,
            or they are simple not started via Steam; like dedicated servers.
        */
        if (Steamconfig::ApplicationID == 0)
        {
            // Open the configuration file.
            std::FILE *Filehandle = std::fopen("steam_appid.txt", "r");
            if (!Filehandle) Filehandle = std::fopen("ayria_appid.txt", "r");

            // Read the uint32.
            if (Filehandle)
            {
                std::fscanf(Filehandle, "%u", &Steamconfig::ApplicationID);
                std::fclose(Filehandle);
            }
        }

        // We can't know which interface version to use, so we'll use the latest and pray.
        if (Steamconfig::ApplicationID == 0)
        {
            Infoprint("No application ID has been provided to the wrapper.");
            Infoprint("This will probably cause errors. Contact the developer.");
        }

        // Check if we should override the username (mainly for developers).
        {
            auto Filebuffer = Package::Readfile("Username.txt");
            if (Filebuffer.size())
            {
                std::memcpy(Steamconfig::Username, Filebuffer.c_str(), std::min(Filebuffer.size(), size_t(16)));
            }
        }

        // Set the environment variable for games that use it.
        SetEnvironmentVariableA("SteamAppId", va("%lu", Steamconfig::ApplicationID).c_str());
        SetEnvironmentVariableA("SteamGameId", va("%llu", Steamconfig::ApplicationID & 0xFFFFFF).c_str());

        // Set the registry variables as some games check that.
        {
            #if defined(_WIN32)
            HKEY Registrykey;

            // Get the steam path.
            if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, Steamregistry, 0, KEY_QUERY_VALUE, &Registrykey) == ERROR_SUCCESS)
            {
                unsigned long Size = 260;
                RegQueryValueExA(Registrykey, "InstallPath", NULL, NULL, (BYTE*)Steamconfig::Path, &Size);
                RegCloseKey(Registrykey);
            }

            // Add the active process to the registry.
            if (RegOpenKeyExA(HKEY_CURRENT_USER, "Software\\Valve\\Steam\\ActiveProcess", 0, KEY_QUERY_VALUE, &Registrykey) == ERROR_SUCCESS)
            {
                DWORD UserID = Steamconfig::UserID & 0xffffffff;
                DWORD ProcessID = GetCurrentProcessId();
                std::string Clientpath32 = va("%s\\steamclient.dll", Steamconfig::Path);
                std::string Clientpath64 = va("%s\\steamclient64.dll", Steamconfig::Path);

                RegSetValueExA(Registrykey, "ActiveUser", NULL, REG_DWORD, (LPBYTE)&UserID, sizeof(DWORD));
                RegSetValueExA(Registrykey, "pid", NULL, REG_DWORD, (LPBYTE)&ProcessID, sizeof(DWORD));
                RegSetValueExA(Registrykey, "SteamClientDll", NULL, REG_SZ, (LPBYTE)Clientpath32.c_str(), (DWORD)Clientpath32.length() + 1);
                RegSetValueExA(Registrykey, "SteamClientDll64", NULL, REG_SZ, (LPBYTE)Clientpath64.c_str(), (DWORD)Clientpath64.length() + 1);
                RegSetValueExA(Registrykey, "Universe", NULL, REG_SZ, (LPBYTE)"Public", (DWORD)std::strlen("Public") + 1);

                RegCloseKey(Registrykey);
            }

            // Set the game to active.
            DWORD Disposition;
            if (RegCreateKeyExA(HKEY_CURRENT_USER, va("Software\\Valve\\Steam\\Apps\\%i", Steamconfig::ApplicationID).c_str(), 0, NULL, 0, KEY_WRITE, NULL, &Registrykey, &Disposition) == ERROR_SUCCESS)
            {
                DWORD Running = TRUE;

                RegSetValueExA(Registrykey, "Installed", NULL, REG_DWORD, (LPBYTE)&Running, sizeof(DWORD));
                RegSetValueExA(Registrykey, "Running", NULL, REG_DWORD, (LPBYTE)&Running, sizeof(DWORD));

                RegCloseKey(Registrykey);
            }

            #else
            /*
                TODO(Convery):
                Investigate what Steam environment variables *nix platforms expect.
            */
            #endif
        }

        // See if we should disable networking.
        Steamconfig::Offline = Commandlinecontains("-no_net");

        // Load the overlay if not disabled.
        if (!Commandlinecontains("-no_overlay"))
        {
            #if defined(_WIN32)
            SetDllDirectoryA(Steamconfig::Path);
            LoadLibraryA(va("%s\\%s", Steamconfig::Path, Gameoverlay).c_str());
            LoadLibraryA(va("%s\\%s", Steamconfig::Path, Clientlibrary).c_str());
            #else
            /*
                TODO(Convery):
                Investigate what Steam calls the overlay on *nix platforms.
            */
            #endif
        }

        // Initialize the interface manager.
        Interfacemanager::Initialize();

        return true;
    }
    EXPORT_ATTR bool SteamAPI_InitSafe()
    {
        return SteamAPI_Init();
    }
    EXPORT_ATTR void SteamAPI_Shutdown()
    {
    }
    EXPORT_ATTR bool SteamAPI_IsSteamRunning()
    {
        return true;
    }
    EXPORT_ATTR const char *SteamAPI_GetSteamInstallPath()
    {
        return Steamconfig::Path;
    }
    EXPORT_ATTR bool SteamAPI_RestartAppIfNecessary(uint32_t unOwnAppID)
    {
        // The host application reports a ID on startup.
        Steamconfig::ApplicationID = unOwnAppID;

        // Usage information.
        Infoprint(va("Starting steamapp %i.", Steamconfig::ApplicationID));
        return false;
    }

    // Direct connections to Steam.
    EXPORT_ATTR int32_t SteamAPI_GetHSteamUser()
    {
        Printfunction();
        return 0;
    }
    EXPORT_ATTR int32_t SteamAPI_GetHSteamPipe()
    {
        Printfunction();
        return 0;
    }
    EXPORT_ATTR int32_t SteamGameServer_GetHSteamUser()
    {
        Printfunction();
        return 0;
    }
    EXPORT_ATTR int32_t SteamGameServer_GetHSteamPipe()
    {
        Printfunction();
        return 0;
    }

    // Callback management.
    EXPORT_ATTR void SteamAPI_RunCallbacks()
    {
        Steamcallback::Runcallbacks();
    }
    EXPORT_ATTR void SteamAPI_RegisterCallback(void *pCallback, int iCallback)
    {
        if (pCallback)
        {
            Steamcallback::Registercallback((Steamcallback::Valvecallback *)pCallback, iCallback);
        }
    }
    EXPORT_ATTR void SteamAPI_UnregisterCallback(void *pCallback, int iCallback)
    {
        if (pCallback)
        {
            Steamcallback::Removecallback((Steamcallback::Valvecallback *)pCallback, iCallback);
        }
    }
    EXPORT_ATTR void SteamAPI_RegisterCallResult(void *pCallback, uint64_t hAPICall)
    {
        if (pCallback)
        {
            Steamcallback::Registerresult((Steamcallback::Valvecallback *)pCallback, hAPICall);
        }
    }
    EXPORT_ATTR void SteamAPI_UnregisterCallResult(void *pCallback, uint64_t hAPICall)
    {
        if (pCallback)
        {
            Steamcallback::Removeresult((Steamcallback::Valvecallback *)pCallback, hAPICall);
        }
    }

    // Dedicated server mode.
    EXPORT_ATTR bool SteamGameServer_BSecure()
    {
        return true;
    }
    EXPORT_ATTR void SteamGameServer_Shutdown()
    {
        Steamconfig::Server = false;
    }
    EXPORT_ATTR void SteamGameServer_RunCallbacks()
    {
        Steamcallback::Runcallbacks();
    }
    EXPORT_ATTR uint64_t SteamGameServer_GetSteamID()
    {
        return Steamconfig::UserID;
    }
    EXPORT_ATTR bool SteamGameServer_Init(uint32_t unIP, uint16_t usSteamPort, uint16_t usGamePort, uint16_t usQueryPort, uint32_t eServerMode, const char *pchVersionString)
    {
        Steamconfig::Server = true;

        // Debug information about the servermode.
        Debugprint("Server startup:");
        Debugprint(va("IP: %u.%u.%u.%u", ((uint8_t *)&unIP)[0], ((uint8_t *)&unIP)[1], ((uint8_t *)&unIP)[2], ((uint8_t *)&unIP)[3]));
        Debugprint(va("Query port: %u", usQueryPort));
        Debugprint(va("Game port: %u", usGamePort));

        return true;
    }
    EXPORT_ATTR bool SteamGameServer_InitSafe(uint32_t unIP, uint16_t usSteamPort, uint16_t usGamePort, uint16_t usQueryPort, uint32_t eServerMode, const char *pchVersionString)
    {
        return SteamGameServer_Init(unIP, usSteamPort, usGamePort, usQueryPort, eServerMode, pchVersionString);
    }
    EXPORT_ATTR bool SteamInternal_GameServer_Init(uint32_t unIP, uint16_t usSteamPort, uint16_t usGamePort, uint16_t usQueryPort, uint32_t eServerMode, const char *pchVersionString)
    {
        return SteamGameServer_Init(unIP, usSteamPort, usGamePort, usQueryPort, eServerMode, pchVersionString);
    }
}