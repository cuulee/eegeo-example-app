// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IAppModeModel.h"
#include "Interiors.h"
#include "BidirectionalBus.h"
#include "SdkModelDomainEventBus.h"
#include "TourStateChangedMessage.h"
#include "StateMachine.h"
#include "IStateMachineState.h"
#include "AppCamera.h"

namespace ExampleApp
{
    namespace AppModes
    {
        namespace SdkModel
        {
            class AppModeModel : public IAppModeModel
            {
            public:
                AppModeModel(Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                             ExampleAppMessaging::TMessageBus& messageBus,
                             ExampleAppMessaging::TSdkModelDomainEventBus& sdkDomainEventBus);
                ~AppModeModel();

                
                void InitialiseStateMachine(const std::vector<Helpers::IStateMachineState*>& appStates);
                
                AppMode GetAppMode() const;
                
                void SetAppMode(AppMode appMode);
                
                void Update(float dt);

                void RegisterAppModeChangedCallback(Eegeo::Helpers::ICallback0& callback);
                void UnregisterAppModeChangedCallback(Eegeo::Helpers::ICallback0& callback);

            private:

                Eegeo::Resources::Interiors::InteriorSelectionModel& m_interiorSelectionModel;

                void OnInteriorSelectionModelChanged(const Eegeo::Resources::Interiors::InteriorId& interiorId);
                Eegeo::Helpers::TCallback1<AppModeModel, const Eegeo::Resources::Interiors::InteriorId> m_interiorSelectionModelChangedCallback;
                
                void OnTourStateChanged(const Tours::TourStateChangedMessage& message);

                ExampleAppMessaging::TMessageBus& m_messageBus;
                Eegeo::Helpers::CallbackCollection0 m_appModeChangedCallbacks;
                
                AppMode m_appMode;
                AppMode m_previousAppMode;
                
                ExampleAppMessaging::TSdkModelDomainEventBus& m_sdkDomainEventBus;
                Eegeo::Helpers::TCallback1<AppModeModel, const ExampleApp::Tours::TourStateChangedMessage&> m_tourStateChangedBinding;
                
                Helpers::StateMachine* m_pStateMachine;
                std::vector<Helpers::IStateMachineState*> m_appStates;
            };
        }
    }
}