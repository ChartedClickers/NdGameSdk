#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::corelib::util {
#pragma pack(push, 1)
struct Err {
    enum ErrDomain : uint16_t {
        CRT = 0,
        AuxDefault = 1265,
        AuxEnvironment = 1266,
        AuxDatabase = 1267,
        AuxMessageIPC = 1268,
        CgfxCompiler = 1269,
        AuxGameContent = 1270,
        AuxAudio = 1271,
        AuxReserved = 1272,
        AuxUnknown = 1273,
        PosixSocket = 1793,
    };

    enum ErrAuxDefaultError : uint16_t {
        AuxDefault_GeneralError = 0,
        AuxDefault_WrongState = 1,
        AuxDefault_BadData = 2,
        AuxDefault_Abort = 3,
        AuxDefault_OutOfMemory = 4,
        AuxDefault_NotFound = 5,
        AuxDefault_NotInitialized = 6,
        AuxDefault_AlreadyInitialized = 7,
        AuxDefault_InvalidArgument = 8,
        AuxDefault_OutOfFios2FileHandles = 9,
        AuxDefault_OutOfFios2OpHandles = 10,
    };

    enum ErrAuxDefaultSuccess : uint16_t {
        AuxDefault_SuccessWithWarning = 0,
        AuxDefault_SuccessAuxDefault = 1,
        AuxDefault_InProgress = 2,
        AuxDefault_UnknownDefaultSuccess = 3,
    };

    enum ErrEnvSuccess : uint16_t {
        Env_Success = 0,
    };

    enum ErrEnvError : uint16_t {
        Env_UnknownError = 0,
    };

    enum ErrDBSuccess : uint16_t {
        DB_Success = 0,
    };

    enum ErrDBError : uint16_t {
        DB_GenericFailure = 0,
        DB_CannotConnect = 1,
        DB_TooManyRecords = 2,
        DB_UnknownError = 3,
    };

    enum ErrMsgIPCSuccess : uint16_t {
        MsgIPC_ResponseReceivedForMessage = 0,
    };

    enum ErrMsgIPCError : uint16_t {
        MsgIPC_SocketUnspecified = 0,
        MsgIPC_NoMessageAvailable = 1,
        MsgIPC_MustReplyBeforeMore = 2,
        MsgIPC_SpecialCharUnrecognized = 3,
        MsgIPC_ReplyTimeoutExceeded = 4,
        MsgIPC_OutgoingBufferFull = 5,
        MsgIPC_IncomingBufferUnderrun = 6,
        MsgIPC_ReadStringBufferTooSmall = 7,
        MsgIPC_DoubleResponseAttempt = 8,
        MsgIPC_InvalidMessageId = 9,
        MsgIPC_ResponseForOtherMessage = 10,
        MsgIPC_ExtraResponsesSent = 11,
    };

    enum ErrCgfxSuccess : uint16_t {
        Cgfx_Success = 0,
    };

    enum ErrCgfxError : uint16_t {
        Cgfx_GenericError = 0,
    };

    enum ErrGameSuccess : uint16_t {
        Game_Success = 0,
    };

    enum ErrGameError : uint16_t {
        Game_MissingLevelOrPackage = 0,
        Game_AnimActorSymbolNotFound = 1,
        Game_AnimActorLoginFailed = 2,
        Game_ArtGroupNotFound = 3,
        Game_ScriptIdNotFound = 4,
        Game_PhysicsInitNoCollision = 5,
        Game_MissingSpawner = 6,
        Game_MissingStateScript = 7,
        Game_MeshNotLoaded = 8,
        Game_SkeletonNotLoaded = 9,
        Game_SpawningSuppressed = 10,
    };

    enum ErrAudioSuccess : uint16_t {
        Audio_UnknownSuccess = 0,
    };

    enum ErrAudioError : uint16_t {
        Audio_UnknownError = 0,
        Audio_AudioNotEnabled = 1,
        Audio_SystemNotInitialized = 2,
        Audio_SystemAlreadyInitialized = 3,
        Audio_AudioSystemNotStarted = 4,
        Audio_OutOfSynths = 5,
        Audio_OutOfVoices = 6,
        Audio_InvalidVibrationHandle = 7,
        Audio_InvalidVoiceHandle = 8,
        Audio_InvalidPlugin = 9,
        Audio_InvalidOscillator = 10,
        Audio_InvalidArgument = 11,
    };

    uint32_t m_code; // 0x0
    uint32_t m_winCode; // 0x4
    void* m_payload; // 0x8
}; // Size: 0x10
#pragma pack(pop)
}
