// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IStateMachineState.h"
#include "AppCamera.h"
#include "StateMachine.h"
#include "Interiors.h"
#include "Streaming.h"
#include "InteriorsExplorer.h"
#include "ICallback.h"
#include <vector>
#include "AppModes.h"
#include "GlobeCamera.h"

namespace ExampleApp
{
    namespace AppModes
    {
        namespace States
        {
            namespace SdkModel
            {
                namespace InteriorExplorerSubStates
                {
                    enum Values
                    {
                        Transition = 0,
                        Stream,
                        View,
                        Exit
                    };
                }
                
                class InteriorExplorerState : public Helpers::IStateMachineState
                {
                private:
                    
                    AppCamera::SdkModel::IAppCameraController& m_cameraController;
                    int m_interiorCameraHandle;
                    Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& m_worldCameraController;
                    ExampleApp::InteriorsExplorer::SdkModel::InteriorsExplorerCameraController& m_interiorsCameraController;
                    
                    Eegeo::Resources::Interiors::InteriorController& m_interiorController;
                    
                    
                    Helpers::StateMachine* m_pSubStateMachine;
                    std::vector<Helpers::IStateMachineState*> m_subStates;
                    
                    AppModes::SdkModel::IAppModeModel& m_appModeModel;
                    
                public:
                    
                    InteriorExplorerState(AppCamera::SdkModel::IAppCameraController& cameraController,
                                          Eegeo::Resources::Interiors::InteriorController& interiorController,
                                          int interiorCameraHandle,
                                          Eegeo::Streaming::CameraFrustumStreamingVolume& cameraFrustumStreamingVolume,
                                          InteriorsExplorer::SdkModel::InteriorVisibilityUpdater& interiorVisibilityUpdater,
                                          InteriorsExplorer::SdkModel::InteriorsExplorerModel& interiorsExplorerModel,
                                          AppModes::SdkModel::IAppModeModel& appModeModel,
                                          Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& worldCameraController,
                                          ExampleApp::InteriorsExplorer::SdkModel::InteriorsExplorerCameraController& interiorsCameraController);
                    
                    ~InteriorExplorerState();
                    
                    void Enter();
                    
                    void Update(float dt);
                    
                    void Exit();
                    
                    void SetSubState(InteriorExplorerSubStates::Values stateIndex);
                    
                    void ReturnToWorldMode();
                };
            }
        }
    }
}