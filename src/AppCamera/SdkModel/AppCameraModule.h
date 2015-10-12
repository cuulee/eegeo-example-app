// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IAppCameraModule.h"
#include "AppCamera.h"
#include "AppCameraInteriorStateObserver.h"
#include "Interiors.h"
#include "GlobeCamera.h"

namespace ExampleApp
{
    namespace AppCamera
    {
        namespace SdkModel
        {
            class AppCameraModule : public IAppCameraModule
            {
            public:
                
                AppCameraModule(Eegeo::Resources::Interiors::InteriorController& interiorController,
                                Eegeo::Camera::GlobeCamera::GlobeCameraController& worldCameraController,
                                Eegeo::Camera::GlobeCamera::GlobeCameraController& interiorCameraController);
                ~AppCameraModule();
                
                IAppCameraController& GetController();
                
            private:
                
                IAppCameraController* m_pAppCameraController;
                
                AppCameraInteriorStateObserver* m_pInteriorStateOberver;
            };
        }
    }
}