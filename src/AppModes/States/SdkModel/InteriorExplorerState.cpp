// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorExplorerState.h"
#include "IAppCameraController.h"
#include "InteriorController.h"
#include "InteriorExplorerSetupState.h"
#include "InteriorExplorerStreamState.h"
#include "InteriorExplorerViewingState.h"
#include "InteriorExplorerExitingState.h"
#include "IAppModeModel.h"

namespace ExampleApp
{
    namespace AppModes
    {
        namespace States
        {
            namespace SdkModel
            {
                InteriorExplorerState::InteriorExplorerState(AppCamera::SdkModel::IAppCameraController& cameraController,
                                                             Eegeo::Resources::Interiors::InteriorController& interiorController,
                                                             int interiorCameraHandle,
                                                             Eegeo::Streaming::CameraFrustumStreamingVolume& cameraFrustumStreamingVolume,
                                                             InteriorsExplorer::SdkModel::InteriorVisibilityUpdater& interiorVisibilityUpdater,
                                                             InteriorsExplorer::SdkModel::InteriorsExplorerModel& interiorsExplorerModel,
                                                             AppModes::SdkModel::IAppModeModel& appModeModel)
                : m_cameraController(cameraController)
                , m_interiorController(interiorController)
                , m_interiorCameraHandle(interiorCameraHandle)
                , m_appModeModel(appModeModel)
                {
                    
                    m_subStates.push_back(Eegeo_NEW(InteriorsExplorer::SdkModel::States::InteriorExplorerSetupState)(*this, cameraController, interiorCameraHandle));
                    m_subStates.push_back(Eegeo_NEW(InteriorsExplorer::SdkModel::States::InteriorExplorerStreamState)(*this,
                                                                                                   interiorController,
                                                                                                   cameraFrustumStreamingVolume,
                                                                                                   interiorVisibilityUpdater));
                    
                    m_subStates.push_back(Eegeo_NEW(InteriorsExplorer::SdkModel::States::InteriorExplorerViewingState)(*this,
                                                                                                                       interiorsExplorerModel,
                                                                                                                       cameraFrustumStreamingVolume));
                    
                    m_subStates.push_back(Eegeo_NEW(InteriorsExplorer::SdkModel::States::InteriorExplorerExitingState)(*this,
                                                                                                                       interiorController,
                                                                                                                       cameraFrustumStreamingVolume,
                                                                                                                       interiorVisibilityUpdater));
                    
                    m_pSubStateMachine = Eegeo_NEW(Helpers::StateMachine)(m_subStates);
                }
                
                InteriorExplorerState::~InteriorExplorerState()
                {
                    if(m_pSubStateMachine->GetCurrentStateIndex() >= 0)
                    {
                        m_pSubStateMachine->StopStateMachine();
                    }
                    
                    Eegeo_DELETE m_pSubStateMachine;
                    m_pSubStateMachine = NULL;
                    
                    for(int i = 0; i < m_subStates.size(); ++i)
                    {
                        Eegeo_DELETE m_subStates[i];
                    }
                    
                    m_subStates.clear();
                }
                
                void InteriorExplorerState::Enter()
                {
                    m_pSubStateMachine->StartStateMachine(0);
                }
                
                void InteriorExplorerState::Update(float dt)
                {
                    if(m_pSubStateMachine->GetCurrentStateIndex() >= 0)
                    {
                        m_pSubStateMachine->Update(dt);
                    }
                }
                
                void InteriorExplorerState::Exit()
                {
                    if(m_pSubStateMachine->GetCurrentStateIndex() >= 0)
                    {
                        m_pSubStateMachine->StopStateMachine();
                    }
                }
                
                void InteriorExplorerState::SetSubState(InteriorExplorerSubStates::Values stateIndex)
                {
                    
                    m_pSubStateMachine->ChangeToState(stateIndex);
                }
                
                void InteriorExplorerState::ReturnToWorldMode()
                {
                    m_appModeModel.SetAppMode(AppModes::SdkModel::WorldMode);
                }
                
            }
        }
    }
}