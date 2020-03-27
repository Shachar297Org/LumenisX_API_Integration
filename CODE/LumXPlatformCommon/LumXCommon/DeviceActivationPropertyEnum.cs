#if !MANAGED
#pragma once
#endif

#if MANAGED
using System;
#endif

namespace LumXCommon
{
    /// <summary>
    /// Enum allowing to distinguish between DeviceSelfActivationData Public Properties <br/><br/>
    /// This enum is share between .Net and CPP
    /// </summary>
#if MANAGED
    [Flags]
    public
#endif
        enum
#if !MANAGED
        class
#endif
        DeviceActivationPropertyEnum
    {
        AllPropertiesOK =       0,
        DeviceType =            1 << 0,
        DeviceSerialNumber =    1 << 1,
        FirstName =             1 << 2,
        LastName =              1 << 3,
        EmailAddress =          1 << 4,
        PhoneNumber =           1 << 5,
        AddressStreet =         1 << 6,
        AddressNumber =         1 << 7,
        AddressCity =           1 << 8,
        AddressZip =            1 << 9,
        AddressCountry =        1 << 10,
        AddressRegion =         1 << 11,
        AddressState =          1 << 12
    }
#if !MANAGED
;
#endif
}

