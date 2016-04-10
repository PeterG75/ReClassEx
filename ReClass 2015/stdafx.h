#pragma once

// Disable warnings for type casting from HANDLE to DWORD and vice versa
#pragma warning(disable : 4312 4311 4302 4099) 

#define WIN32_LEAN_AND_MEAN
#include "targetver.h"

#include <afx.h>

// turns off MFC's hiding of some common and often safely ignored warning messages
#define _AFX_ALL_WARNINGS
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

#include <afxwin.h>				// MFC core and standard components
#include <afxext.h>				// MFC extensions
#include <afxdisp.h>			// MFC Automation classes

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC support for Internet Explorer 4 Common Controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC support for ribbons and control bars

#include <vector>
#include <Shlwapi.h>
#include <Psapi.h>
#include <CommCtrl.h>
#include <memory>

// Include BeaEngine disassembler 
#define BEA_ENGINE_STATIC
#define BEA_USE_STDCALL
#include "..\\beaengine\\beaengine\\headers\\BeaEngine.h"

// Include Scintilla parser
#define PLAT_WIN 1
#include "..\\scintilla\\include\\SciLexer.h"
#include "..\\scintilla\\include\\Scintilla.h"

// A few basic colors for scintilla editor
const COLORREF black = RGB(0, 0, 0);
const COLORREF white = RGB(255, 255, 255);
const COLORREF green = RGB(0, 200, 0);
const COLORREF red = RGB(255, 0, 0);
const COLORREF lightred = RGB(255, 100, 100);
const COLORREF blue = RGB(0, 0, 255);
const COLORREF darkblue = RGB(0, 0, 100);
const COLORREF yellow = RGB(255, 255, 0);
const COLORREF orange = RGB(255, 175, 65);
const COLORREF magenta = RGB(255, 0, 255);
const COLORREF cyan = RGB(0, 255, 255);
const COLORREF purple = RGB(128, 0, 255);

// Scintilla Colors structure
struct SScintillaColors {
	int			iItem;
	COLORREF	rgb;
};

// Include TinyXml parser
//#include "tinyxml2_unicode.h"
#include "tinyxml2.h"
using namespace tinyxml2;

// Include SQL parser
#include "..\\SQLite\\CppSQLite3.h"

// Utilities
#include "Utils.h"

// Classes
#include "CMemory.h"

struct MemMapInfo
{
	size_t  Start;
	size_t  End;
	DWORD   Size;
	CString Name;
	CString Path;
	//bool IsModule;
};

struct AddressName
{
	CString Name;
	size_t Address;
};

// Max export entries allowed
#define MAX_EXPORTS 16384

// Globals
extern HANDLE g_hProcess;
extern DWORD g_ProcessID;
extern size_t g_AttachedProcessAddress;

extern std::vector<MemMapInfo> MemMap;
extern std::vector<MemMapInfo> MemMapCode;
extern std::vector<MemMapInfo> MemMapData;
extern std::vector<MemMapInfo> MemMapModule;
extern std::vector<AddressName> Exports;
extern std::vector<AddressName> CustomNames;

extern COLORREF crBackground;
extern COLORREF crSelect;
extern COLORREF crHidden;

extern COLORREF crOffset;
extern COLORREF crAddress;
extern COLORREF crType;
extern COLORREF crName;
extern COLORREF crIndex;
extern COLORREF crValue;
extern COLORREF crComment;

extern COLORREF crVTable;
extern COLORREF crFunction;
extern COLORREF crChar;
extern COLORREF crCustom;
extern COLORREF crHex;

extern CFont Font;
//extern CFont SmallFont;
extern int FontWidth;
extern int FontHeight;

extern bool gbAddress;
extern bool gbOffset;
extern bool gbText;
extern bool gbRTTI;

extern bool gbFloat;
extern bool gbInt;
extern bool gbString;
extern bool gbPointers;

extern bool gbTop;
extern bool gbClassBrowser;
extern bool gbFilterProcesses;

extern CString tdHex;
extern CString tdInt64;

extern CString tdInt32;
extern CString tdInt16;
extern CString tdInt8;
extern CString tdDWORD;
extern CString tdWORD;
extern CString tdBYTE;
extern CString tdFloat;
extern CString tdDouble;
extern CString tdVec2;
extern CString tdVec3;
extern CString tdQuat;
extern CString tdMatrix;
extern CString tdPChar;

#define WM_MAXITEMS 128

#define WM_CLASSMENU WM_USER
#define WM_PROCESSMENU (WM_USER+WM_MAXITEMS)
#define WM_CHANGECLASSMENU (WM_USER+WM_MAXITEMS+WM_MAXITEMS)
#define WM_DELETECLASSMENU (WM_USER+WM_MAXITEMS+WM_MAXITEMS+WM_MAXITEMS)

#define PrintOut(fmt, ...) { \
do { \
	static TCHAR s_logbuf[1024]; \
	if (fmt) { \
		_sntprintf(s_logbuf, 1024, fmt, ##__VA_ARGS__); \
		theApp.m_pConsole->SendMessage((WM_USER+WM_MAXITEMS+WM_MAXITEMS+WM_MAXITEMS+1), (WPARAM)s_logbuf, 0); \
	} \
} while (0);\
}

#define	NONE -1
#define	HS_NONE -1
#define HS_EDIT 0
#define HS_OPENCLOSE 1
#define HS_SELECT 2
#define HS_DROP 3
#define HS_CLICK 4
#define HS_CHANGE_A 5
#define HS_CHANGE_X 6
#define HS_DELETE 7
#define HS_RTTI 8
#define HS_ADDRESS 68
#define HS_NAME 69
#define HS_COMMENT 70

class CNodeBase;

class HotSpot
{
public:
	CRect Rect;
	CString Text;
	size_t Address;
	int ID;
	int Type;
	UINT Level;
	CNodeBase* object;
};

#define ICON_OPEN 0
#define ICON_CLOSED 1
#define ICON_CLASS 2
#define ICON_METHOD 3
#define ICON_VTABLE 4
#define ICON_DELETE 5
#define ICON_ADD 6
#define ICON_RANDOM 7
#define ICON_DROPARROW 8
#define ICON_POINTER 9
#define ICON_ARRAY 10
#define ICON_CUSTOM 11
#define ICON_ENUM 12
#define ICON_FLOAT 13
#define ICON_LEFT 14
#define ICON_RIGHT 15
#define ICON_MATRIX 16
#define ICON_INTEGER 17
#define ICON_TEXT 18
#define ICON_UNSIGNED 19
#define ICON_VECTOR 20
#define ICON_CHANGE 21
#define ICON_CAMERA 22

extern std::vector<HICON> Icons;

enum NodeType
{
	nt_none = -1,
	nt_base,
	nt_instance,
	nt_struct,
	nt_hidden,
	nt_hex32,
	nt_hex64,
	nt_hex16,
	nt_hex8,
	nt_pointer,
	nt_int64,
	nt_int32,
	nt_int16,
	nt_int8,
	nt_float,
	nt_double,
	nt_uint32, // dword
	nt_uint16, // word
	nt_uint8, // byte
	nt_text,
	nt_unicode,
	nt_function,
	nt_custom,
	nt_vec2,
	nt_vec3,
	nt_quat,
	nt_matrix,
	nt_vtable,
	nt_array,
	nt_class,
	nt_pchar,
	nt_bits
};

#define ISHEXTYPE(type) (type == nt_hex64 || type == nt_hex32 || type == nt_hex16 || type == nt_hex8 || type == nt_bits)

__inline const TCHAR* NodeTypeToString(NodeType type)
{
	static const TCHAR* pszNodeTypes[] = {
		_T("nt_base"),
		_T("nt_instance"),
		_T("nt_struct"),
		_T("nt_hidden"),
		_T("nt_hex32"),
		_T("nt_hex64"),
		_T("nt_hex16"),
		_T("nt_hex8"),
		_T("nt_pointer"),
		_T("nt_int64"),
		_T("nt_int32"),
		_T("nt_int16"),
		_T("nt_int8"),
		_T("nt_float"),
		_T("nt_double"),
		_T("nt_uint32"),
		_T("nt_uint16"),
		_T("nt_uint8"),
		_T("nt_text"),
		_T("nt_unicode"),
		_T("nt_function"),
		_T("nt_custom"),
		_T("nt_vec2"),
		_T("nt_vec3"),
		_T("nt_quat"),
		_T("nt_matrix"),
		_T("nt_vtable"),
		_T("nt_array"),
		_T("nt_class"),
		_T("nt_pchar"),
		_T("nt_bits")
	};	
	return pszNodeTypes[type];
}

bool PauseResumeThreadList(bool bResumeThread);

bool UpdateMemoryMap();
bool UpdateExports();

size_t GetBase();
bool IsCode(size_t Address);
bool IsData(size_t Address);
bool IsMemory(size_t Address);
bool IsModule(size_t Address);

CString GetAddressName(size_t Address,bool bHEX);
CString GetModuleName(size_t Address);
size_t  GetAddressFromName(CString moduleName);

BOOL ReadMemory(LPVOID Address, LPVOID Buffer, SIZE_T Size, SIZE_T *num_read = nullptr);
BOOL WriteMemory(LPVOID Address, LPVOID Buffer, SIZE_T Size, SIZE_T *num_wrote = nullptr);
CStringA ReadMemoryStringA(size_t address, SIZE_T max = 40);
CStringW ReadMemoryStringW(size_t address, SIZE_T max = 40);

#include "Classes.h"

#ifdef _WIN64
#define CNodeHex CNodeHex64
#else
#define CNodeHex CNodeHex32
#endif

extern DWORD NodeCreateIndex;

__int64 StrToNum(const TCHAR *udata, int udatalen, int base);
int SplitString(const CString& input, const CString& delimiter, CStringArray& results);
size_t ConvertStrToAddress(CString str);

//Plugins
#define PLUGIN_EXPORT extern "C" __declspec( dllexport )

typedef bool( WINAPI *plugin_read_callback )( HANDLE *process_handle, uintptr_t *read_address, uint8_t *read_buffer_ptr, size_t *read_size );
typedef bool( WINAPI *plugin_write_callback )( HANDLE *process_handle, uintptr_t *write_address, const uint8_t *write_buffer_ptr, size_t *write_size );

typedef struct _RECLASS_PLUGIN_INFO
{
	plugin_read_callback read_callback;
	plugin_write_callback write_callback;
	std::string version, about;
} RECLASS_PLUGIN_INFO, *LPRECLASS_PLUGIN_INFO;

typedef struct _RECLASS_PROCESS_INFORMATION 
{
	DWORD ProcessID;
} RECLASS_PROCESS_INFORMATION, *LPRECLASS_PROCESS_INFORMATION;

PLUGIN_EXPORT DWORD WINAPI RegisterPlugin( const LPRECLASS_PLUGIN_INFO lpPlugin );
PLUGIN_EXPORT BOOL WINAPI GetAttatchedInfo( LPRECLASS_PROCESS_INFORMATION lpProcInfo );