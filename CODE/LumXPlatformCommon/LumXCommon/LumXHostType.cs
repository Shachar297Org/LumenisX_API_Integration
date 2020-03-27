#if !MANAGED
#pragma once
#endif

namespace LumXCommon
{
    /// <summary>
    /// Allows to determine type of host using LumenisX platform
    /// </summary>
#if MANAGED
    public
#endif
        enum
#if !MANAGED
        class
#endif
        LumXHostType
    {
        /// <summary>
        /// Not set
        /// </summary>
        Unknown,
        /// <summary>
        /// Host is standalone application
        /// </summary>
        StandaloneApplication,
        /// <summary>
        /// Host is Client part of Client-Server pair
        /// </summary>
        Client,
        /// <summary>
        /// Host is Server part of Client-Server pair
        /// </summary>
        Server
    }
#if !MANAGED
;
#endif
}