#if !MANAGED
#pragma once
#endif

namespace LumXCommon
{
#if MANAGED
    public
#endif
        enum
#if !MANAGED
        class
#endif
        LumXCommands
    {
        /// <summary>
        /// Command sent automatically by LumXClient, <br/>
        /// ... as soon as it has IPC connection to LumXServer <br/>
        /// LumXClient sends all data it has along with this command <br/>
        /// LumXServer completes other data items that LumXClient has not <br/>
        /// ... and sends the command to cloud <br/><br/>
        /// Command sent only once through system lifetime
        /// </summary>
        startSystem,
        /// <summary>
        /// Sent by LumXClient to LumXServer <br/>
        /// Contains information about LumXClient Hosting Application
        /// </summary>
        LumXCmd_ClientHostStartInfo,
        /// <summary>
        /// Sent by LumXClient to LumXServer <br/>
        /// Allows to set LumXServer State to Idle
        /// </summary>
        LumXCmd_SetStateIdle,
        /// <summary>
        /// Sent by LumXClient to LumXServer <br/>
        /// Allows to set LumXServer State to Active
        /// </summary>
        LumXCmd_SetStateActive,
        /// <summary>
        /// Sent by LumXServer to LumXClient <br/>
        /// ... as soon as Server State changes <br/>
        /// ... in order to let LumXClient updating Lumenis application <br/>
        /// Sent along with current State and new State values
        /// </summary>
        LumXCmd_UpdateState,
        /// <summary>
        /// Sent by LumXClient to LumXServer <br/>
        /// Allows to add handler to Server Host application to restart it
        /// </summary>
        LumXCmd_RestartLumXServerHost,
        /// <summary>
        /// Sent by LumXClient to LumXServer <br/>
        /// Allows to add handler to Server Host application to shut it down
        /// </summary>
        LumXCmd_TerminateLumXServerHost,
        /// <summary>
        /// Sent by LumXClient to LumXServer <br/>
        /// ... after Lumenis application provides all data required for self-activation and <br/>
        /// ... initiates self-activation
        /// </summary>
        LumXCmd_SelfActivateDevice
    }
#if !MANAGED
;
#endif
}
