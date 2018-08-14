// Copyright (c) Microsoft Corporation. All rights reserved.
//
// Licensed under the MIT License. See LICENSE.txt in the project root for license information.

// This file was automatically generated. Please do not edit it manually.

#include "pch.h"
#include "HDRToneMapEffect.h"

namespace ABI { namespace Microsoft { namespace Graphics { namespace Canvas { namespace Effects
{
    HDRToneMapEffect::HDRToneMapEffect(ICanvasDevice* device, ID2D1Effect* effect)
        : CanvasEffect(EffectId(), 3, 1, true, device, effect, static_cast<IHDRToneMapEffect*>(this))
    {
        if (!effect)
        {
            // Set default values
            SetBoxedProperty<float>(D2D1_HDRTONEMAP_PROP_INPUT_MAX_LUMINANCE, 4000.0f);
            SetBoxedProperty<float>(D2D1_HDRTONEMAP_PROP_OUTPUT_MAX_LUMINANCE, 300.0f);
            SetBoxedProperty<uint32_t>(D2D1_HDRTONEMAP_PROP_DISPLAY_MODE, HDRToneMapEffectDisplayMode::SDR);
        }
    }

    IMPLEMENT_EFFECT_PROPERTY(HDRToneMapEffect,
        InputMaxLuminance,
        float,
        float,
        D2D1_HDRTONEMAP_PROP_INPUT_MAX_LUMINANCE)

    IMPLEMENT_EFFECT_PROPERTY(HDRToneMapEffect,
        OutputMaxLuminance,
        float,
        float,
        D2D1_HDRTONEMAP_PROP_OUTPUT_MAX_LUMINANCE)

    IMPLEMENT_EFFECT_PROPERTY(HDRToneMapEffect,
        DisplayMode,
        uint32_t,
        HDRToneMapEffectDisplayMode,
        D2D1_HDRTONEMAP_PROP_DISPLAY_MODE)

    IMPLEMENT_EFFECT_SOURCE_PROPERTY(HDRToneMapEffect,
        Source,
        0)

    IMPLEMENT_EFFECT_PROPERTY_MAPPING(HDRToneMapEffect,
        { L"InputMaxLuminance",  D2D1_HDRTONEMAP_PROP_INPUT_MAX_LUMINANCE,  GRAPHICS_EFFECT_PROPERTY_MAPPING_DIRECT },
        { L"OutputMaxLuminance", D2D1_HDRTONEMAP_PROP_OUTPUT_MAX_LUMINANCE, GRAPHICS_EFFECT_PROPERTY_MAPPING_DIRECT },
        { L"DisplayMode",        D2D1_HDRTONEMAP_PROP_DISPLAY_MODE,         GRAPHICS_EFFECT_PROPERTY_MAPPING_DIRECT })

    ActivatableClassWithFactory(HDRToneMapEffect, SimpleAgileActivationFactory<HDRToneMapEffect>);
}}}}}
