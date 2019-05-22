#pragma once

#define AV_TEST

#define HOOK_WSA32

#if defined(HOOK_WSA32)
#ifdef _DEBUG
#pragma comment(lib,"libgo_MDD_X64.lib")
#else
#pragma comment(lib,"libgo_MD_X64.lib")
#endif // _DEBUG
#else
#ifdef _DEBUG
#pragma comment(lib,"libgo_NoHook_MDD_X64.lib")
#else
#pragma comment(lib,"libgo_NoHook_MD_X64.lib")
#endif
#endif

#ifdef _DEBUG
#pragma comment(lib,"../thrty_party/ClamAv/win32/x64/debug/libclamav.lib")
#else
#pragma comment(lib,"../thrty_party/ClamAv/win32/x64/debug/libclamav.lib")
#endif