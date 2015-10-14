// Copyright eeGeo Ltd (2012-2015), All Rights Reserved


#include "AppModeModel.h"
#include "InteriorSelectionModel.h"
#include "AppModeChangedMessage.h"
#include "TourService.h"
#include "WorldState.h"
#include "InteriorExplorerState.h"

namespace ExampleApp
{
    namespace AppModes
    {
        namespace SdkModel
        {
            AppModeModel::AppModeModel(Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                       ExampleAppMessaging::TMessageBus& messageBus,
                                       ExampleAppMessaging::TSdkModelDomainEventBus& sdkDomainEventBus)
            : m_interiorSelectionModel(interiorSelectionModel)
            , m_messageBus(messageBus)
            , m_interiorSelectionModelChangedCallback(this, &AppModeModel::OnInteriorSelectionModelChanged)
            , m_appMode(WorldMode)
            , m_previousAppMode(WorldMode)
            , m_sdkDomainEventBus(sdkDomainEventBus)
            , m_tourStateChangedBinding(this, &AppModeModel::OnTourStateChanged)
            , m_pStateMachine(NULL)
            {
                m_interiorSelectionModel.RegisterSelectionChangedCallback(m_interiorSelectionModelChangedCallback);
                m_sdkDomainEventBus.Subscribe(m_tourStateChangedBinding);
            }

            AppModeModel::~AppModeModel()
            {
                m_interiorSelectionModel.UnregisterSelectionChangedCallback(m_interiorSelectionModelChangedCallback);
                m_sdkDomainEventBus.Unsubscribe(m_tourStateChangedBinding);
                
                if(m_pStateMachine != NULL)
                {
                    m_pStateMachine->StopStateMachine();
                    Eegeo_DELETE m_pStateMachine;
                    m_pStateMachine = NULL;
                    
                    for(int i = 0; i < m_appStates.size(); ++i)
                    {
                        Eegeo_DELETE m_appStates[i];
                    }
                }
                m_appStates.clear();
            }
            
            void AppModeModel::OnTourStateChanged(const Tours::TourStateChangedMessage& message)
            {
                if(message.TourStarted())
                {
                    SetAppMode(TourMode);
                }
                else
                {
                    SetAppMode(m_previousAppMode);
                }
            }

            void AppModeModel::OnInteriorSelectionModelChanged(const Eegeo::Resources::Interiors::InteriorId& interiorId)
            {
                if(m_appMode == TourMode)
                {
                    m_previousAppMode = m_interiorSelectionModel.IsInteriorSelected() ? InteriorMode : WorldMode;
                    return;
                }
                
                AppMode newAppMode = m_interiorSelectionModel.IsInteriorSelected() ? InteriorMode : WorldMode;
                SetAppMode(newAppMode);
            }

            void AppModeModel::RegisterAppModeChangedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_appModeChangedCallbacks.AddCallback(callback);
            }

            void AppModeModel::UnregisterAppModeChangedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_appModeChangedCallbacks.RemoveCallback(callback);
            }

            AppMode AppModeModel::GetAppMode() const
            {
                return m_appMode;
            }

            void AppModeModel::SetAppMode(AppMode appMode)
            {
                if (m_appMode != appMode)
                {
                    m_previousAppMode = m_appMode;
                    
                    m_appMode = appMode;
                    m_appModeChangedCallbacks.ExecuteCallbacks();
                    m_messageBus.Publish(AppModeChangedMessage(m_appMode));
                    m_pStateMachine->ChangeToState(m_appMode);
                }
            }
            
            void AppModeModel::Update(float dt)
            {
                Eegeo_ASSERT(m_pStateMachine != NULL, "State MAchine not initialised");
                m_pStateMachine->Update(dt);
            }
            
            void AppModeModel::InitialiseStateMachine(const std::vector<Helpers::IStateMachineState*>& appStates)
            {
                Eegeo_ASSERT(m_pStateMachine == NULL, "Cannot initialise the state machine twice");
                
                m_appStates = appStates;
                
                m_pStateMachine = Eegeo_NEW(Helpers::StateMachine)(m_appStates);
                
                m_pStateMachine->StartStateMachine(WorldMode);
            }
        }
    }
}