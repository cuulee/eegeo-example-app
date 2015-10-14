// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IAppCameraModule.h"
#include "AppCamera.h"
#include "AppCameraInteriorStateObserver.h"
#include "Interiors.h"
#include "GlobeCamera.h"
#include "InteriorsExplorer.h"
#include "Tours.h"

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
                                ExampleApp::Tours::SdkModel::ITourService& tourService,
                                Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& worldCameraController,
                                InteriorsExplorer::SdkModel::InteriorsExplorerCameraController& interiorCameraController,
                                ExampleApp::Tours::SdkModel::Camera::IToursCameraController& tourCameraController);
                ~AppCameraModule();
                
                IAppCameraController& GetController();
                
            private:
                
                IAppCameraController* m_pAppCameraController;
                
                AppGlobeCameraWrapper* m_pAppGlobeCameraWrapper;
                
                AppCameraInteriorStateObserver* m_pInteriorStateOberver;
            };
        }
    }
}