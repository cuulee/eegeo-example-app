// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"

#include "GlobeCamera.h"
#include "ICallback.h"
#include "Interiors.h"
#include "ITouchController.h"
#include "VectorMath.h"

#include "SdkModelDomainEventBus.h"
#include "TourStateChangedMessage.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            class InteriorsExplorerCameraController : public  Eegeo::NonCopyable
            {
            private:
                bool m_cameraEnabled;
                bool m_tourIsActive;
                Eegeo::Resources::Interiors::InteriorController& m_interiorController;
                Eegeo::Resources::Interiors::InteriorSelectionModel& m_interiorSelectionModel;
                Eegeo::Resources::Interiors::Markers::InteriorMarkerModelRepository& m_markerRepository;
                Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& m_globeCameraController;
                ExampleAppMessaging::TSdkModelDomainEventBus& m_sdkDomainEventBus;
                Eegeo::Helpers::TCallback1<InteriorsExplorerCameraController, const ExampleApp::Tours::TourStateChangedMessage&> m_tourStateChangedBinding;
                
            public:
                InteriorsExplorerCameraController(Eegeo::Resources::Interiors::InteriorController& interiorController,
                                                  Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                  Eegeo::Resources::Interiors::Markers::InteriorMarkerModelRepository& markerRepository,
                                                  Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& globeCameraController,
                                                  ExampleAppMessaging::TSdkModelDomainEventBus& sdkDomainEventBus);
                
                ~InteriorsExplorerCameraController();
                
                inline bool InteriorCameraEnabled() const { return m_cameraEnabled; }
                
                Eegeo::Camera::CameraState GetCameraState() const;
                
                Eegeo::Camera::RenderCamera GetRenderCamera() const;
                
                Eegeo::ITouchController& GetTouchController();
                
                void Update(float dt);
                
            private:
                void OnTourStateChanged(const Tours::TourStateChangedMessage& message);
            };
        }
    }
}