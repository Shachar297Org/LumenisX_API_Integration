#pragma once

// contains include directives to *.cs files
// these files are shared between .Net and Native code

// .Net code include these files through LumXCommon (LumXPlatformCommon namespace)
// only Native code should set include to current file

// following undef is required to "convert" C# declartions inside *.cs files into legal CPP
#undef MANAGED

#include "LumXErrorCode.cs"
#include "LumXPlatformState.cs"
#include "LumXStateUpdateSeverity.cs"
#include "DeviceActivationPropertyEnum.cs"
#include "LumXCommands.cs"
#include "LumXHostType.cs"

//Each *.cs file contains following blocks allowing to share enum declaration between C#and CPP:
/*
    #if !MANAGED
    #pragma once
    #endif
    
    namespace NamespaceName
    {
    #if MANAGED
        public
    #endif
            enum
    #if !MANAGED
            class
    #endif
            EnumClassName
        {
            EnumMember1,
            ...
        }
    #if !MANAGED
    ;
    #endif
}
*/