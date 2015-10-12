// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AppCameraInteriorStateObserver.h"
#include "InteriorController.h"
#include "IAppCameraController.h"

namespace ExampleApp
{
    namespace AppCamera
    {
        AppCameraInteriorStateObserver::AppCameraInteriorStateObserver(Eegeo::Resources::Interiors::InteriorController& interiorController,
                                                                       SdkModel::IAppCameraController& cameraController,
                                                                       int worldCameraHandle,
                                                                       int interiorCameraHandle)
        : m_interiorController(interiorController)
        , m_controllerStateChangedCallback(this, &AppCameraInteriorStateObserver::OnControllerStateChanged)
        , m_cameraController(cameraController)
        , m_worldCameraHandle(worldCameraHandle)
        , m_interiorCameraHandle(interiorCameraHandle)
        {
            m_interiorController.RegisterStateChangedCallback(m_controllerStateChangedCallback);
        }
        
        AppCameraInteriorStateObserver::~AppCameraInteriorStateObserver()
        {
            m_interiorController.UnregisterStateChangedCallback(m_controllerStateChangedCallback);
        }
        
        void AppCameraInteriorStateObserver::OnControllerStateChanged()
        {
            if(m_interiorController.GetCurrentState() == Eegeo::Resources::Interiors::InteriorViewState::NoInteriorSelected)
            {
                m_cameraController.TransitionToCameraWithHandle(m_worldCameraHandle);
            }
            else if(m_interiorController.GetCurrentState() != Eegeo::Resources::Interiors::InteriorViewState::AwaitingInteriorResources &&
                    !m_cameraController.IsTransitionInFlight())
            {
                m_cameraController.TransitionToCameraWithHandle(m_interiorCameraHandle);
            }
        }
    }
}