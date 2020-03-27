#if !MANAGED
#pragma once
#endif

namespace LumXCommon
{
    /// <summary>
    /// Update source propagates update message to client <br/>
    /// (the message can follow catching exception by source) <br/>
    /// Update source determines severity of the update message <br/>
    /// This in order to allow the client receiveng update to examine the severity and <br/>
    /// ... to decide if it can proceede or should terminate
    /// </summary>
#if MANAGED
    public
#endif
        enum
#if !MANAGED
        class
#endif
        LumXStateUpdateSeverity
    {
        /// <summary>
        /// Some information message
        /// </summary>
        Information,
        /// <summary>
        /// An error occurred, was treated <br/>
        /// Client can proceed safely
        /// </summary>
        Warning,
        /// <summary>
        /// Serious error occurred, was treated <br/>
        /// Client can decide what to do
        /// </summary>
        Error,
        /// <summary>
        /// Critical error occurred <br/>
        /// Message source failed to treat it and cannot proceede<br/>
        /// Client should terminate as soon as possible
        /// </summary>
        Critical
    }
#if !MANAGED
;
#endif
}

