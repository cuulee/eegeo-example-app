// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AppCameraInteriorStateObserver.h"
#include "InteriorController.h"
#include "IAppCameraController.h"
#include "ITourService.h"

namespace ExampleApp
{
    namespace AppCamera
    {
        AppCameraInteriorStateObserver::AppCameraInteriorStateObserver(Eegeo::Resources::Interiors::InteriorController& interiorController,
                                                                       Tours::SdkModel::ITourService& tourService,
                                                                       SdkModel::IAppCameraController& cameraController,
                                                                       const int worldCameraHandle,
                                                                       const int interiorCameraHandle,
                                                                       const int tourCameraHandle)
        : m_interiorController(interiorController)
        , m_tourService(tourService)
        , m_cameraController(cameraController)
        , m_worldCameraHandle(worldCameraHandle)
        , m_interiorCameraHandle(interiorCameraHandle)
        , m_tourCameraHandle(tourCameraHandle)
        , m_controllerStateChangedCallback(this, &AppCameraInteriorStateObserver::OnControllerStateChanged)
        , m_tourStartedCallback(this, &AppCameraInteriorStateObserver::OnTourStarted)
        , m_tourEndedCallback(this, &AppCameraInteriorStateObserver::OnTourEnded)
        {
            m_interiorController.RegisterStateChangedCallback(m_controllerStateChangedCallback);
            m_tourService.RegisterTourStartedCallback(m_tourStartedCallback);
            m_tourService.RegisterTourEndedCallback(m_tourEndedCallback);
        }
        
        AppCameraInteriorStateObserver::~AppCameraInteriorStateObserver()
        {
            m_tourService.UnregisterTourStartedCallback(m_tourStartedCallback);
            m_tourService.UnregisterTourEndedCallback(m_tourEndedCallback);
            m_interiorController.UnregisterStateChangedCallback(m_controllerStateChangedCallback);
        }
        
        void AppCameraInteriorStateObserver::OnControllerStateChanged()
        {
            if(m_tourService.IsTourActive())
            {
                return;
            }
            
            if(m_interiorController.GetCurrentState() == Eegeo::Resources::Interiors::InteriorViewState::NoInteriorSelected)
            {
                m_cameraController.TransitionToCameraWithHandle(m_worldCameraHandle);
            }
            else if(!m_cameraController.IsTransitionInFlight())
            {
                m_cameraController.TransitionToCameraWithHandle(m_interiorCameraHandle);
            }
        }
        
        void AppCameraInteriorStateObserver::OnTourStarted()
        {
            m_cameraController.TransitionToCameraWithHandle(m_tourCameraHandle);
        }
        
        void AppCameraInteriorStateObserver::OnTourEnded()
        {
            if(m_interiorController.GetCurrentState() == Eegeo::Resources::Interiors::InteriorViewState::NoInteriorSelected)
            {
                m_cameraController.TransitionToCameraWithHandle(m_worldCameraHandle);
            }
            else if(!m_cameraController.IsTransitionInFlight())
            {
                m_cameraController.TransitionToCameraWithHandle(m_interiorCameraHandle);
            }
        }
    }
}