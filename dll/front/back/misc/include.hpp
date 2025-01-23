
#pragma warning(disable:6011 28183 28251)

#include <windows.h>
#include <random>
#include <map>

#include <jni.h>
#include <jvmti.h>

struct _UNICODE_STRING
{
	unsigned __int16										Length;
	unsigned __int16										MaximumLength;
	wchar_t*												Buffer;
};

struct _PEB_LDR_DATA
{
	unsigned __int32										Length;
	unsigned __int8											Initialized;
	unsigned __int64										SsHandle;
	_LIST_ENTRY												InLoadOrderModuleList;
	_LIST_ENTRY												InMemoryOrderModuleList;
	_LIST_ENTRY												InInitializationOrderModuleList;
};

struct _LDR_DATA_TABLE_ENTRY
{
	unsigned __int64										Reserved1[2];
	_LIST_ENTRY												InMemoryOrderLinks;
	unsigned __int64										Reserved2[2];
	unsigned __int64										DllBase;
	unsigned __int64										Reserved3[2];
	_UNICODE_STRING											FullDllName;
	unsigned __int8											Reserved4[8];
	unsigned __int64										Reserved5[3];
	union
	{
		unsigned __int32									CheckSum;
		unsigned __int64									Reserved6;
	};
	unsigned __int32										TimeDateStamp;
};

struct _LDR_DLL_LOADED_NOTIFICATION_DATA
{
	unsigned __int32										Flags;
	_UNICODE_STRING*										FullDllName;
	_UNICODE_STRING*										BaseDllName;
	unsigned __int64										DllBase;
	unsigned __int32										SizeOfImage;
};

struct _LDR_DLL_UNLOADED_NOTIFICATION_DATA
{
	unsigned __int32										Flags;
	_UNICODE_STRING*										FullDllName;
	_UNICODE_STRING*										BaseDllName;
	unsigned __int64										DllBase;
	unsigned __int32										SizeOfImage;
};

union _LDR_DLL_NOTIFICATION_DATA
{
	_LDR_DLL_LOADED_NOTIFICATION_DATA						Loaded;
	_LDR_DLL_UNLOADED_NOTIFICATION_DATA						Unloaded;
};

struct _RTL_DRIVE_LETTER_CURRENT_DIRECTORY
{
	unsigned __int16										Flags;
	unsigned __int16										Length;
	unsigned __int32										TimeStamp;
	_UNICODE_STRING											DosPath;
};

struct _RTL_USER_PROCESS_PARAMETERS
{
	unsigned __int32										MaximumLength;
	unsigned __int32										Length;
	unsigned __int32										Flags;
	unsigned __int32										DebugFlags;
	unsigned __int64										ConsoleHandle;
	unsigned __int32										ConsoleFlags;
	unsigned __int64										StdInputHandle;
	unsigned __int64										StdOutputHandle;
	unsigned __int64										StdErrorHandle;
	_UNICODE_STRING											CurrentDirectoryPath;
	unsigned __int64										CurrentDirectoryHandle;
	_UNICODE_STRING											DllPath;
	_UNICODE_STRING											ImagePathName;
	_UNICODE_STRING											CommandLine;
	unsigned __int64										Environment;
	unsigned __int32										StartingPositionLeft;
	unsigned __int32										StartingPositionTop;
	unsigned __int32										Width;
	unsigned __int32										Height;
	unsigned __int32										CharWidth;
	unsigned __int32										CharHeight;
	unsigned __int32										ConsoleTextAttributes;
	unsigned __int32										WindowFlags;
	unsigned __int32										ShowWindowFlags;
	_UNICODE_STRING											WindowTitle;
	_UNICODE_STRING											DesktopName;
	_UNICODE_STRING											ShellInfo;
	_UNICODE_STRING											RuntimeData;
	_RTL_DRIVE_LETTER_CURRENT_DIRECTORY						DLCurrentDirectory[32];
};

struct _PEB
{
	unsigned __int8											Reserved1[2];
	unsigned __int8											BeingDebugged;
	unsigned __int8											Reserved2[1];
	unsigned __int64										Mutant;
	unsigned __int64										ImageBaseAddress;
	_PEB_LDR_DATA*											Ldr;
	_RTL_USER_PROCESS_PARAMETERS*							ProcessParameters;
	unsigned __int64										Reserved4[3];
	unsigned __int64										AtlThunkSListPtr;
	unsigned __int64										Reserved5;
	unsigned __int32										Reserved6;
	unsigned __int64										Reserved7;
	unsigned __int32										Reserved8;
	unsigned __int32										AtlThunkSListPtr32;
	unsigned __int64										Reserved9[45];
	unsigned __int8											Reserved10[96];
	unsigned __int64										PostProcessInitRoutine;
	unsigned __int8											Reserved11[128];
	unsigned __int64										Reserved12[1];
	unsigned __int32										SessionId;
};

struct _CLIENT_IDENTIFIER
{
	unsigned __int64										UniqueProcess;
	unsigned __int64										UniqueThread;
};

struct _TEB_ACTIVE_FRAME_CONTEXT
{
	unsigned __int32										Flags;
	unsigned __int8*										FrameName;
};

struct _TEB_ACTIVE_FRAME
{
	unsigned __int32										Flags;
	_TEB_ACTIVE_FRAME*										Previous;
	_TEB_ACTIVE_FRAME_CONTEXT*								Context;
};

struct _RTL_ACTIVATION_CONTEXT_STACK_FRAME
{
	_RTL_ACTIVATION_CONTEXT_STACK_FRAME*					Previous;
	_ACTIVATION_CONTEXT*									ActivationContext;
	unsigned __int32										Flags;
};

struct _ACTIVATION_CONTEXT_STACK
{
	_RTL_ACTIVATION_CONTEXT_STACK_FRAME*					ActiveFrame;
	_LIST_ENTRY												FrameListCache;
	unsigned __int32										Flags;
	unsigned __int32										NextCookieSequenceNumber;
	unsigned __int32										StackId;
};

struct _GDI_TEB_BATCH
{
	unsigned __int32										Offset;
	unsigned __int32										HDC;
	unsigned __int32										Buffer[310];
};

struct _TEB
{
	_NT_TIB													NtTib;
	unsigned __int64										EnvironmentPointer;
	_CLIENT_IDENTIFIER										ClientId;
	unsigned __int64										ActiveRpcHandle;
	unsigned __int64										ThreadLocalStoragePointer;
	_PEB*													ProcessEnvironmentBlock;
	unsigned __int32										LastErrorValue;
	unsigned __int32										CountOfOwnedCriticalSections;
	unsigned __int64										CsrClientThread;
	unsigned __int64										Win32ThreadInfo;
	unsigned __int32										User32Reserved[26];
	unsigned __int32										UserReserved[5];
	unsigned __int64										WOW32Reserved;
	unsigned __int32										CurrentLocale;
	unsigned __int32										FpSoftwareStatusRegister;
	unsigned __int64										SystemReserved1[54];
	__int32													ExceptionCode;
	_ACTIVATION_CONTEXT_STACK*								ActivationContextStackPointer;
	unsigned __int8											SpareBytes1[36];
	unsigned __int32										TxFsContext;
	_GDI_TEB_BATCH*											GdiTebBatch;
	_CLIENT_IDENTIFIER										RealClientId;
	unsigned __int64										GdiCachedProcessHandle;
	unsigned __int32										GdiClientPID;
	unsigned __int32										GdiClientTID;
	unsigned __int64										GdiThreadLocalInfo;
	unsigned __int32										Win32ClientInfo[62];
	unsigned __int64										glDispatchTable[233];
	unsigned __int32										glReserved1[29];
	unsigned __int64										glReserved2;
	unsigned __int64										glSectionInfo;
	unsigned __int64										glSection;
	unsigned __int64										glTable;
	unsigned __int64										glCurrentRC;
	unsigned __int64										glContext;
	unsigned __int32										LastStatusValue;
	_UNICODE_STRING											StaticUnicodeString;
	wchar_t													StaticUnicodeBuffer[261];
	unsigned __int64										DeallocationStack;
	unsigned __int64										TlsSlots[64];
	_LIST_ENTRY												TlsLinks;
	unsigned __int64										Vdm;
	unsigned __int64										ReservedForNtRpc;
	unsigned __int64										DbgSsReserved[2];
	unsigned __int32										HardErrorMode;
	unsigned __int64										Instrumentation[9];
	_GUID													ActivityId;
	unsigned __int64										SubProcessTag;
	unsigned __int64										EtwLocalData;
	unsigned __int64										EtwTraceData;
	unsigned __int64										WinSockData;
	unsigned __int32										GdiBatchCount;
	unsigned __int8											SpareBool0;
	unsigned __int8											SpareBool1;
	unsigned __int8											SpareBool2;
	unsigned __int8											IdealProcessor;
	unsigned __int32										GuaranteedStackBytes;
	unsigned __int64										ReservedForPerf;
	unsigned __int64										ReservedForOle;
	unsigned __int32										WaitingOnLoaderLock;
	unsigned __int64										SavedPriorityState;
	unsigned __int32										SoftPatchPtr1;
	unsigned __int64										ThreadPoolData;
	unsigned __int64										TlsExpansionSlots;
	unsigned __int32										ImpersonationLocale;
	unsigned __int32										IsImpersonating;
	unsigned __int64										NlsCache;
	unsigned __int64										pShimData;
	unsigned __int32										HeapVirtualAffinity;
	unsigned __int64										CurrentTransactionHandle;
	_TEB_ACTIVE_FRAME*										ActiveFrame;
	unsigned __int64										FlsData;
	unsigned __int64										PreferredLanguages;
	unsigned __int64										UserPrefLanguages;
	unsigned __int64										MergedPrefLanguages;
	unsigned __int32										MuiImpersonation;
	unsigned __int16										CrossTebFlags;
	unsigned __int32										SpareCrossTebBits : 16;
	unsigned __int16										SameTebFlags;
	unsigned __int32										DbgSafeThunkCall : 1;
	unsigned __int32										DbgInDebugPrint : 1;
	unsigned __int32										DbgHasFiberData : 1;
	unsigned __int32										DbgSkipThreadAttach : 1;
	unsigned __int32										DbgWerInShipAssertCode : 1;
	unsigned __int32										DbgRanProcessInit : 1;
	unsigned __int32										DbgClonedThread : 1;
	unsigned __int32										DbgSuppressDebugMsg : 1;
	unsigned __int32										SpareSameTebBits : 8;
	unsigned __int64										TxnScopeEnterCallback;
	unsigned __int64										TxnScopeExitCallback;
	unsigned __int64										TxnScopeContext;
	unsigned __int32										LockCount;
	unsigned __int32										ProcessRundown;
	unsigned __int64										LastSwitchTime;
	unsigned __int64										TotalSwitchOutTime;
	_LARGE_INTEGER											WaitReasonBitMap;
};

struct _PROCESS_BASIC_INFORMATION
{
	__int32													ExitStatus;
	_PEB*													PebBaseAddress;
	unsigned __int64										AffinityMask;
	__int32													BasePriority;
	unsigned __int64										UniqueProcessId;
	unsigned __int64										InheritedFromUniqueProcessId;
};

struct _SYSTEM_PROCESS_IMAGE_NAME_INFORMATION
{
	unsigned __int64										ProcessId;
	_UNICODE_STRING											ImageName;
};

struct _THREAD_BASIC_INFORMATION
{
	__int32													ExitStatus;
	unsigned __int64										TebBaseAddress;
	_CLIENT_IDENTIFIER										ClientId;
	unsigned __int64										AffinityMask;
	__int32													Priority;
	__int32													BasePriority;
};

struct _HV_DETAILS
{
	unsigned __int32										Data[4];
};

struct _SYSTEM_HYPERVISOR_DETAIL_INFORMATION
{
	_HV_DETAILS												HvVendorAndMaxFunction;
	_HV_DETAILS												HypervisorInterface;
	_HV_DETAILS												HypervisorVersion;
	_HV_DETAILS												HvFeatures;
	_HV_DETAILS												HwFeatures;
	_HV_DETAILS												EnlightenmentInfo;
	_HV_DETAILS												ImplementationLimits;
};

struct _PROCESS_INSTRUMENTATION_CALLBACK_INFORMATION
{
	unsigned __int32										Version;
	unsigned __int32										Reserved;
	unsigned __int64										Callback;
};

struct _SYSTEM_KERNEL_DEBUGGER_INFORMATION
{
	unsigned __int8											DebuggerEnabled;
	unsigned __int8											DebuggerNotPresent;
};

struct _SYSTEM_HANDLE_TABLE_ENTRY_INFORMATION
{
	unsigned __int16										UniqueProcessId;
	unsigned __int16										CreatorBackTraceIndex;
	unsigned __int8											ObjectTypeIndex;
	unsigned __int8											HandleAttributes;
	unsigned __int16										HandleValue;
	unsigned __int64										Object;
	unsigned __int32										GrantedAccess;
};

struct _SYSTEM_HANDLE_INFORMATION
{
	unsigned __int32										NumberOfHandles;
	_SYSTEM_HANDLE_TABLE_ENTRY_INFORMATION					Handles[1];
};

struct _OBJECT_ATTRIBUTES
{	
	unsigned __int32										Length;
	unsigned __int64										RootDirectory;
	_UNICODE_STRING*										ObjectName;
	unsigned __int32										Attributes;
	unsigned __int64										SecurityDescriptor;
	unsigned __int64										SecurityQualityOfService;
};

struct _IO_STATUS_BLOCK
{
	union
	{
		__int32												Status;
		unsigned __int64									Pointer;
	};
	unsigned __int32										Information;
};

struct _FILE_FS_VOLUME_INFORMATION
{
	_LARGE_INTEGER											VolumeCreationTime;
	unsigned __int32										VolumeSerialNumber;
	unsigned __int32										VolumeLabelLength;
	unsigned __int8											SupportsObjects;
	wchar_t													VolumeLabel[32];
};

struct _SYSTEM_PROCESS_INFORMATION
{
	unsigned __int32										NextEntryOffset;
	unsigned __int32										NumberOfThreads;
	LARGE_INTEGER											Reserved[3];
	LARGE_INTEGER											CreateTime;
	LARGE_INTEGER											UserTime;
	LARGE_INTEGER											KernelTime;
	_UNICODE_STRING											ImageName;
	unsigned __int32										BasePriority;
	unsigned __int64										ProcessId;
	unsigned __int64										InheritedFromProcessId;
};