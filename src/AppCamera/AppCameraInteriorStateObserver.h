// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "AppCamera.h"
#include "Interiors.h"
#include "ICallback.h"
#include "Tours.h"

namespace ExampleApp
{
    namespace AppCamera
    {
        // TODO: This type should go and the AppModeModel/statemachine should determine when to switch cameras.
        class AppCameraInteriorStateObserver :  private Eegeo::NonCopyable
        {
        public:
            
            AppCameraInteriorStateObserver(Eegeo::Resources::Interiors::InteriorController& interiorController,
                                           ExampleApp::Tours::SdkModel::ITourService& tourService,
                                           SdkModel::IAppCameraController& cameraController,
                                           const int worldCameraHandle,
                                           const int interiorCameraHandle,
                                           const int tourCameraHandle);
            ~AppCameraInteriorStateObserver();
            
        private:
            
            void OnControllerStateChanged();
            void OnTourStarted();
            void OnTourEnded();
            
            Eegeo::Resources::Interiors::InteriorController& m_interiorController;
            Eegeo::Helpers::TCallback0<AppCameraInteriorStateObserver> m_controllerStateChangedCallback;
            Eegeo::Helpers::TCallback0<AppCameraInteriorStateObserver> m_tourStartedCallback;
            Eegeo::Helpers::TCallback0<AppCameraInteriorStateObserver> m_tourEndedCallback;
            SdkModel::IAppCameraController& m_cameraController;
            Tours::SdkModel::ITourService& m_tourService;
            const int m_worldCameraHandle;
            const int m_interiorCameraHandle;
            const int m_tourCameraHandle;
        };
        
    }
}