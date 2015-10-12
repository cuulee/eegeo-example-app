// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "AppCamera.h"
#include "Interiors.h"
#include "ICallback.h"

namespace ExampleApp
{
    namespace AppCamera
    {
        class AppCameraInteriorStateObserver :  private Eegeo::NonCopyable
        {
        public:
            
            AppCameraInteriorStateObserver(Eegeo::Resources::Interiors::InteriorController& interiorController,
                                           SdkModel::IAppCameraController& cameraController,
                                           int worldCameraHandle,
                                           int interiorCameraHandle);
            ~AppCameraInteriorStateObserver();
            
        private:
            
            void OnControllerStateChanged();
            
            Eegeo::Resources::Interiors::InteriorController& m_interiorController;
            Eegeo::Helpers::TCallback0<AppCameraInteriorStateObserver> m_controllerStateChangedCallback;
            
            SdkModel::IAppCameraController& m_cameraController;
            int m_worldCameraHandle;
            int m_interiorCameraHandle;
        };
        
    }
}