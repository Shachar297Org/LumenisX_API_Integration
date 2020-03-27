#if !MANAGED
#pragma once
#endif

namespace LumXCommon
{
    /// <summary>
    /// Indicates current State of LumenisX platform <br/>
    /// All states except <see cref="Idle"/> are automatic: <br/>
    /// - determined by inner processes in Client and Server <br/>
    /// - Idle state can be set by calling SetStateIdle() method at Client / Server <br/>
    /// In order to release from <see cref="Idle"/> call SetStateActive() at Client / Server <br/><br/>
    /// This enum is share between .Net and CPP
    /// </summary>
#if MANAGED
    public
#endif
        enum
#if !MANAGED
        class
#endif
        LumXPlatformState
    {
        /// <summary>
        /// Default LumXPlatformState value, before activation and initialization <br/>
        /// Any attempt to use LumenisX at this state is not allowed
        /// </summary>
        PlatformStateUNKNOWN,
        /// <summary>
        /// LumXServer has no internet connection and cannot send data to cloud <br/>
        /// Any data sent to LumXServer will be serialized until internet connection resumes <br/>
        /// </summary>
        NoInternetConnection,
        /// <summary>
        /// State of the platform before it activated <br/>
        /// Without activation no data is sent to cloud <br/>
        /// Data from LumXClient sent to LumXServer is not serialized
        /// </summary>
        NotActivated,
        /// <summary>
        /// SelfActivation was issued by LumXClient, but was not performed due internet problems <br/>
        /// As soon as internet resumes, LumXServer will retry to perform SelfActivation <br/>
        /// Depending on the result the state will be set to <see cref="NotActivated"/> or to <see cref="Active"/>
        /// </summary>
        SelfActivationPending,
        /// <summary>
        /// System State when self activation was attempted, but failed <br/>
        /// Failure may be caused by wrong data provided during self activation attempt <br/>
        /// Lumenis app may retry to perform self activation again
        /// </summary>
        SelfActivationFailed,
        /// <summary>
        /// Normal working stats of the platform. <br/>
        /// While in this state, LumXClient / LumXServer can send events and commands, and receive commands
        /// </summary>
        Active,
        /// <summary>
        /// <see cref="Active"/> sub-state indicating sending large bulks of data
        /// </summary>
        ActiveSendingData,
        /// <summary>
        /// <see cref="Active"/> sub-state indicating file upload by dedicated process
        /// </summary>
        ActiveUploading,
        /// <summary>
        /// <see cref="Active"/> sub-state indicating file download by dedicated process
        /// </summary>
        ActiveDownloading,
        /// <summary>
        /// In this state LumenisX can receive events and commands from Lumenis application <br/>
        /// ... without sending them into cloud. <br/>
        /// Instead it stores them in inner buffers until state is Active again
        /// </summary>
        Idle
    }
#if !MANAGED
;
#endif
}

