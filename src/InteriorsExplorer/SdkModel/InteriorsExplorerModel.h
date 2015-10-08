// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Interiors.h"
#include "BidirectionalBus.h"
#include "ICallback.h"
#include "InteriorsExplorerExitMessage.h"
#include "InteriorsExplorerSelectFloorMessage.h"
#include "MapMode.h"
#include "InteriorId.h"
#include "Metrics.h"
#include "AppModes.h"
#include "SdkModelDomainEventBus.h"
#include "TourStateChangedMessage.h"
#include "GlobeCamera.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            class InteriorsExplorerModel : private Eegeo::NonCopyable
            {
            public:
                
                InteriorsExplorerModel(Eegeo::Resources::Interiors::InteriorController& controller,
                                       Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                       Eegeo::Resources::Interiors::Markers::InteriorMarkerModelRepository& markerRepository,
                                       Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& globeCameraController,
                                       MapMode::SdkModel::IMapModeModel& mapModeModel,
                                       ExampleAppMessaging::TMessageBus& messageBus,
                                       Metrics::IMetricsService& metricsService,
                                       ExampleAppMessaging::TSdkModelDomainEventBus& sdkDomainEventBus);
                ~InteriorsExplorerModel();
                
                void SelectFloor(int floor);
                
                const bool InteriorCameraEnabled() const { return m_cameraEnabled; }
                
                void Update(float dt);

            private:
                
                void OnControllerStateChanged();
                void OnControllerVisibilityChanged();
                void OnControllerFloorChanged();
                
                void OnExit(const InteriorsExplorerExitMessage& message);
                void OnSelectFloor(const InteriorsExplorerSelectFloorMessage& message);
                
                void PublishInteriorExplorerStateChange();

                Eegeo::Resources::Interiors::InteriorController& m_controller;
                Eegeo::Resources::Interiors::InteriorSelectionModel& m_interiorSelectionModel;
                Eegeo::Resources::Interiors::Markers::InteriorMarkerModelRepository& m_markerRepository;
                Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& m_globeCameraController;
                MapMode::SdkModel::IMapModeModel& m_mapModeModel;

                ExampleAppMessaging::TMessageBus& m_messageBus;
                Metrics::IMetricsService& m_metricsService;
                
                Eegeo::Helpers::TCallback0<InteriorsExplorerModel> m_controllerStateChangedCallback;
                Eegeo::Helpers::TCallback0<InteriorsExplorerModel> m_controllerVisibilityChangedCallback;
                Eegeo::Helpers::TCallback0<InteriorsExplorerModel> m_controllerFloorChangedCallback;
                
                Eegeo::Helpers::TCallback1<InteriorsExplorerModel, const InteriorsExplorerExitMessage&> m_exitCallback;
                Eegeo::Helpers::TCallback1<InteriorsExplorerModel, const InteriorsExplorerSelectFloorMessage&> m_selectFloorCallback;

                bool m_previouslyInMapMode;
                bool m_tourIsActive;
                bool m_cameraEnabled;
                
                ExampleAppMessaging::TSdkModelDomainEventBus& m_sdkDomainEventBus;
                Eegeo::Helpers::TCallback1<InteriorsExplorerModel, const ExampleApp::Tours::TourStateChangedMessage&> m_tourStateChangedBinding;
                void OnTourStateChanged(const Tours::TourStateChangedMessage& message);
            };
        }
    }
}