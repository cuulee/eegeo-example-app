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
#include "InteriorsExplorer.h"

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
                                       InteriorVisibilityUpdater& interiorVisibilityUpdater,
                                       MapMode::SdkModel::IMapModeModel& mapModeModel,
                                       ExampleAppMessaging::TMessageBus& messageBus,
                                       Metrics::IMetricsService& metricsService,
                                       ExampleAppMessaging::TSdkModelDomainEventBus& sdkDomainEventBus);
                ~InteriorsExplorerModel();
                
                void SelectFloor(int floor);
                
                void ShowInteriorExplorer();
                
                void HideInteriorExplorer();
                
                void InsertInteriorExplorerExitedCallback(Eegeo::Helpers::ICallback0& callback);
                void RemoveInteriorExplorerExitedCallback(Eegeo::Helpers::ICallback0& callback);

            private:
                
                void OnControllerStateChanged();
                void OnControllerVisibilityChanged();
                void OnControllerFloorChanged();
                
                void OnExit(const InteriorsExplorerExitMessage& message);
                void OnSelectFloor(const InteriorsExplorerSelectFloorMessage& message);
                
                void PublishInteriorExplorerStateChange();

                Eegeo::Resources::Interiors::InteriorController& m_controller;
                Eegeo::Resources::Interiors::InteriorSelectionModel& m_interiorSelectionModel;
                InteriorVisibilityUpdater& m_interiorVisibilityUpdater;
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
                
                ExampleAppMessaging::TSdkModelDomainEventBus& m_sdkDomainEventBus;
                Eegeo::Helpers::TCallback1<InteriorsExplorerModel, const ExampleApp::Tours::TourStateChangedMessage&> m_tourStateChangedBinding;
                void OnTourStateChanged(const Tours::TourStateChangedMessage& message);
                
                bool m_interiorExplorerEnabled;
                Eegeo::Helpers::CallbackCollection0 m_interiorExplorerExitedCallbacks;
            };
        }
    }
}