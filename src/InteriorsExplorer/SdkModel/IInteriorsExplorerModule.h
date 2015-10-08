// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "ScreenControlViewModelIncludes.h"
#include "InteriorsExplorer.h"
#include "GlobeCamera.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            class IInteriorsExplorerModule
            {
            public:
                virtual ~IInteriorsExplorerModule() { }

                virtual View::InteriorsExplorerViewModel& GetInteriorsExplorerViewModel() const = 0;

                virtual ScreenControl::View::IScreenControlViewModel& GetScreenControlViewModel() const = 0;
                
                virtual Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& GetInteriorsCameraController() const = 0;
                
                virtual const bool InteriorCameraEnabled() const = 0;
                
                virtual void Update(float dt) const = 0;
            };
        }
    }
}