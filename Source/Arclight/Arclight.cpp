/*
    Initial author: Convery (tcn@hedgehogscience.com)
    Started: 03-02-2018
    License: MIT
    Notes:
        ARC exports implementation.
*/

#include "../Stdinclude.hpp"

namespace CC_SDK
{
    // Implemented like ArcSDK.
    class EXPORT_ATTR ArcID
    {
        wchar_t *Internalstring;

    public:
        wchar_t *Get()
        {
            return Internalstring;
        }
        void Set(const wchar_t *Input)
        {
            size_t Length = std::wcslen(Input);
            std::memcpy(Internalstring, Input, Length * 2);
        }

        ArcID()
        {
            Internalstring = new wchar_t[256]();
        };
        ArcID(ArcID &Parent)
        {
            Internalstring = new wchar_t[256]();
            Set(Parent.Internalstring);
        };
        ArcID(const wchar_t *Plaintext)
        {
            Internalstring = new wchar_t[256]();
            Set(Plaintext);
        };
        ~ArcID() 
        { 
            delete[] Internalstring; 
        };

        ArcID &operator = (const ArcID &Right) noexcept
        {
            Set(Right.Internalstring);
            return *this;
        }
        bool operator < (const ArcID &Right)
        {
            return wcscmp(Internalstring, Right.Internalstring) < 0;
        }
    };
    class EXPORT_ATTR LobbyID
    {
        wchar_t *Internalstring;

    public:
        wchar_t *Get()
        {
            return Internalstring;
        }
        void Set(const wchar_t *Input)
        {
            size_t Length = std::wcslen(Input);
            std::memcpy(Internalstring, Input, Length * 2);
        }

        LobbyID()
        {
            Internalstring = new wchar_t[256]();
        };
        LobbyID(LobbyID &Parent)
        {
            Internalstring = new wchar_t[256]();
            Set(Parent.Internalstring);
        };
        LobbyID(const wchar_t *Plaintext)
        {
            Internalstring = new wchar_t[256]();
            Set(Plaintext);
        };
        ~LobbyID() 
        { 
            delete[] Internalstring; 
        };

        LobbyID &operator = (const LobbyID &Right) noexcept
        {
            Set(Right.Internalstring);
            return *this;
        }
        bool operator < (const LobbyID &Right)
        {
            return wcscmp(Internalstring, Right.Internalstring) < 0;
        }
    };
}

// Interfaces.
extern "C"
{
    EXPORT_ATTR void *ArcFriends()
    {
        return nullptr;
    }
    EXPORT_ATTR void *Matchmaking()
    {
        return nullptr;
    }
    EXPORT_ATTR void *Networking()
    {
        return nullptr;
    }

    EXPORT_ATTR int64_t CC_GetAccountName(int64_t a1, int64_t a2, unsigned int *a3)
    {
        return 0;
    }
    EXPORT_ATTR int64_t CC_GetArcID(int64_t a1, int64_t a2)
    {
        return 0;
    }
    EXPORT_ATTR int64_t CC_GetArcRunningMode(int64_t a1)
    {
        return 0;
    }
    EXPORT_ATTR int64_t CC_GetLaunchedParameter(int16_t *a1, int a2, wchar_t *a3, signed int a4)
    {
        return 0;
    }
    EXPORT_ATTR int64_t CC_GetNickName(int64_t a1, wchar_t *a2, unsigned int *a3)
    {
        return 0;
    }
    EXPORT_ATTR int64_t CC_GetSteamTicket(int64_t a1, unsigned int *a2)
    {
        return 0;
    }
    EXPORT_ATTR int64_t CC_GetToken(int64_t a1, int64_t a2, int64_t a3, unsigned int *a4, unsigned int *a5)
    {
        return 0;
    }
    EXPORT_ATTR int64_t CC_GetTokenEx(int64_t a1, int *a2)
    {
        return 0;
    }
    EXPORT_ATTR int64_t CC_GetUserAvatarLink(int64_t a1, wchar_t *a2, unsigned int *a3, int a4)
    {
        return 0;
    }
    EXPORT_ATTR int64_t CC_GotoUrlInOverlay(int64_t a1, const wchar_t *a2)
    {
        return 0;
    }
    EXPORT_ATTR wchar_t *CC_Init(int64_t a1, int64_t a2, unsigned int *a3)
    {
        return nullptr;
    }
    EXPORT_ATTR char CC_InstalledFromArc(unsigned int a1, unsigned int a2)
    {
        return 0;
    }
    EXPORT_ATTR int64_t CC_InviteFriendInOverlay(int64_t a1, int64_t *a2)
    {
        return 0;
    }
    EXPORT_ATTR int64_t CC_LaunchClient(int16_t *a1, int a2, int64_t a3)
    {
        return 0;
    }
    EXPORT_ATTR int64_t CC_RegisterCallback(int16_t *a1, unsigned int a2)
    {
        return 0;
    }
    EXPORT_ATTR int64_t CC_RunCallbacks()
    {
        return 0;
    }
    EXPORT_ATTR int64_t CC_SetViewableRect(int16_t *a1, unsigned int a2, unsigned int a3, unsigned int a4, unsigned int a5)
    {
        return 0;
    }
    EXPORT_ATTR int64_t CC_ShowOverlay(int64_t a1, unsigned int a2)
    {
        return 0;
    }
    EXPORT_ATTR int64_t CC_UnInit(int64_t a1)
    {
        return 0;
    }
    EXPORT_ATTR int64_t CC_UnregisterCallback(int64_t a1)
    {
        return 0;
    }
}
