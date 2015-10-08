// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorsExplorerModel.h"
#include "InteriorController.h"
#include "InteriorsExplorerStateChangedMessage.h"
#include "InteriorsExplorerFloorSelectedMessage.h"

#include "InteriorsModel.h"
#include "InteriorsFloorModel.h"
#include "InteriorSelectionModel.h"
#include "IMapModeModel.h"
#include "IMetricsService.h"
#include "IAppModeModel.h"
#include "InteriorsModel.h"
#include "InteriorId.h"
#include "InteriorsFloorModel.h"


namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            namespace
            {
            
                const std::string MetricEventInteriorsVisible = "TimedEvent: Interiors Visible";
                const std::string MetricEventInteriorSelected = "Interior Selected";
                const std::string MetricEventInteriorFloorSelected = "Interior Floor Selected";
                const std::string MetricEventInteriorExitPressed = "Interior Exit Pressed";
                
                std::string ToFloorName(const Eegeo::Resources::Interiors::InteriorsFloorModel* pFloorModel)
                {
                    return pFloorModel->GetFloorName();
                }
            }
            
            InteriorsExplorerModel::InteriorsExplorerModel(Eegeo::Resources::Interiors::InteriorController& controller,
                                                           Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                           MapMode::SdkModel::IMapModeModel& mapModeModel,
                                                           ExampleAppMessaging::TMessageBus& messageBus,
                                                           Metrics::IMetricsService& metricsService,
                                                           ExampleAppMessaging::TSdkModelDomainEventBus& sdkDomainEventBus)
            : m_controller(controller)
            , m_interiorSelectionModel(interiorSelectionModel)
            , m_mapModeModel(mapModeModel)
            , m_messageBus(messageBus)
            , m_metricsService(metricsService)
            , m_controllerStateChangedCallback(this, &InteriorsExplorerModel::OnControllerStateChanged)
            , m_controllerVisibilityChangedCallback(this, &InteriorsExplorerModel::OnControllerVisibilityChanged)
            , m_controllerFloorChangedCallback(this, &InteriorsExplorerModel::OnControllerFloorChanged)
            , m_exitCallback(this, &InteriorsExplorerModel::OnExit)
            , m_selectFloorCallback(this, &InteriorsExplorerModel::OnSelectFloor)
            , m_previouslyInMapMode(false)
            , m_tourIsActive(false)
            , m_sdkDomainEventBus(sdkDomainEventBus)
            , m_tourStateChangedBinding(this, &InteriorsExplorerModel::OnTourStateChanged)
            {
                m_controller.RegisterStateChangedCallback(m_controllerStateChangedCallback);
                m_controller.RegisterVisibilityChangedCallback(m_controllerVisibilityChangedCallback);
                m_controller.RegisterFloorChangedCallback(m_controllerFloorChangedCallback);
                
                m_messageBus.SubscribeNative(m_exitCallback);
                m_messageBus.SubscribeNative(m_selectFloorCallback);
                
                m_sdkDomainEventBus.Subscribe(m_tourStateChangedBinding);
            }
            
            InteriorsExplorerModel::~InteriorsExplorerModel()
            {
                m_sdkDomainEventBus.Unsubscribe(m_tourStateChangedBinding);
                
                m_messageBus.UnsubscribeNative(m_selectFloorCallback);
                m_messageBus.UnsubscribeNative(m_exitCallback);

                m_controller.UnregisterStateChangedCallback(m_controllerStateChangedCallback);
                m_controller.UnregisterVisibilityChangedCallback(m_controllerVisibilityChangedCallback);
                m_controller.UnregisterFloorChangedCallback(m_controllerFloorChangedCallback);
            }
            
            void InteriorsExplorerModel::OnControllerStateChanged()
            {
                if(m_tourIsActive)
                {
                    return;
                }
                
                if(m_controller.GetCurrentState() == Eegeo::Resources::Interiors::InteriorViewState::NoInteriorSelected)
                {
                    m_mapModeModel.SetInMapMode(m_previouslyInMapMode);
                    m_metricsService.EndTimedEvent(MetricEventInteriorsVisible);
                }
                else
                {
                    m_previouslyInMapMode = m_mapModeModel.IsInMapMode();
                    m_mapModeModel.SetInMapMode(false);
                    m_metricsService.BeginTimedEvent(MetricEventInteriorsVisible);
                    
                    const Eegeo::Resources::Interiors::InteriorId& interiorId = m_interiorSelectionModel.GetSelectedInteriorId();
                    m_metricsService.SetEvent(MetricEventInteriorSelected, "InteriorId", interiorId.Value());
                    
                    if(m_controller.InteriorInScene())
                    {
                        m_controller.SetExteriorToInteriorParam(1.0f);
                    }
                }
                
                PublishInteriorExplorerStateChange();
            }
            
            void InteriorsExplorerModel::OnControllerFloorChanged()
            {
                // nope.
            }
            
            void InteriorsExplorerModel::OnControllerVisibilityChanged()
            {
                // app change?
            }
        
            void InteriorsExplorerModel::OnExit(const InteriorsExplorerExitMessage& message)
            {
                m_metricsService.SetEvent(MetricEventInteriorExitPressed);
                m_controller.ClearSelectedInterior(); // How is transition out dealt with?
            }
            
            void InteriorsExplorerModel::OnSelectFloor(const InteriorsExplorerSelectFloorMessage &message)
            {
                SelectFloor(message.GetFloor());
            }

            void InteriorsExplorerModel::SelectFloor(int floor)
            {
                m_controller.SetCurrentFloor(floor);
                
                const Eegeo::Resources::Interiors::InteriorsFloorModel* pFloorModel = NULL;
                Eegeo_ASSERT(m_controller.TryGetCurrentFloorModel(pFloorModel), "Could not fetch current floor model");
                
                m_messageBus.Publish(InteriorsExplorerFloorSelectedMessage(m_controller.GetCurrentFloorIndex(), pFloorModel->GetFloorName()));

                m_metricsService.SetEvent(MetricEventInteriorFloorSelected, "InteriorId", m_interiorSelectionModel.GetSelectedInteriorId().Value(), "FloorName", pFloorModel->GetFloorName());
            }

            void InteriorsExplorerModel::PublishInteriorExplorerStateChange()
            {
                
                int floor = m_controller.InteriorIsVisible() ? m_controller.GetCurrentFloorIndex() : 0;
                
                std::string floorName;
                std::vector<std::string> floorShortNames;
                
                if (m_controller.InteriorIsVisible())
                {
                    const Eegeo::Resources::Interiors::InteriorsModel* pModel = NULL;
                    m_controller.TryGetCurrentModel(pModel);
                    
                    Eegeo_ASSERT(pModel != NULL, "Couldn't get current model for interior");
                    const Eegeo::Resources::Interiors::TFloorModelVector& floorModels = pModel->GetFloors();
                    
                    std::transform(floorModels.begin(), floorModels.end(), std::back_inserter(floorShortNames), ToFloorName);
                    
                    const Eegeo::Resources::Interiors::InteriorsFloorModel* pFloorModel = NULL;
                    Eegeo_ASSERT(m_controller.TryGetCurrentFloorModel(pFloorModel), "Could not fetch current floor model");
                    floorName = pFloorModel->GetFloorName();
                }
                
                m_messageBus.Publish(InteriorsExplorerStateChangedMessage(m_controller.InteriorIsVisible(),
                                                                          floor,
                                                                          floorName,
                                                                          floorShortNames));
            }
            
            void InteriorsExplorerModel::OnTourStateChanged(const Tours::TourStateChangedMessage& message)
            {
                m_tourIsActive = message.TourStarted();
                
                if(!message.TourStarted() && m_controller.InteriorIsVisible())
                {
                    PublishInteriorExplorerStateChange();
                }
            }
        }
    }
}