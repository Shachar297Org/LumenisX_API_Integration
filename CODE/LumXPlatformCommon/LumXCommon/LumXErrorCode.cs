#if !MANAGED
#pragma once
#endif

namespace LumXCommon
{
    /// <summary>
    /// Defines ErrorCodes for LumenisX Platform
    /// This enum is share between .Net and CPP
    /// </summary>
#if MANAGED
    public
#endif
        enum
#if !MANAGED
        class
#endif
        LumXErrorCode
    {
        UNKNOWN,
        APIProviderInitializationException,
        CertificationFilesMissing,
        OpenSSLFilesMissing,
        BioTMissingSettings,
        BioTWrongSettings,
        UserWrongUserName,
        UserWrongPassword,
        DeviceNotActivated,
        DeviceNotRegisteredInCloud,
        DeviceWrongType,
        WrongEnvironment,
        EventWrongName,
        EventWrongParamType,
        EventMissingParam,
        EventExtraParam,
        EventsMissingSchemaFile,
        EventsMissingDictionary,
        EventsIllegalDictionary,
        CommandWrongName,
        CommandWrongSource,
        CommandWrongTarget,
        CommandWrongParamType,
        CommandMissingParam,
        CommandExtraParam,
        CommandsMissingSchemaFile,
        CommandsMissingDictionary,
        CommandsIllegalDictionary,
        NoInternet,
        NoServerPipe,
        NoClientPipe
    }
#if !MANAGED
;
#endif
}

