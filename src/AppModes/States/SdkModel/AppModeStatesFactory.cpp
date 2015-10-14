// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AppModeStatesFactory.h"
#include "IAppCameraController.h"
#include "WorldState.h"
#include "InteriorExplorerState.h"

namespace ExampleApp
{
    namespace AppModes
    {
        namespace States
        {
            namespace SdkModel
            {
                AppModeStatesFactory::AppModeStatesFactory(AppCamera::SdkModel::IAppCameraController& appCameraController,
                                                           Eegeo::Resources::Interiors::InteriorController& interiorController,
                                                           AppCamera::SdkModel::IAppCamera& worldCameraController,
                                                           AppCamera::SdkModel::IAppCamera& interiorCameraController,
                                                           Eegeo::Streaming::CameraFrustumStreamingVolume& cameraFrustumStreamingVolume,
                                                           InteriorsExplorer::SdkModel::InteriorVisibilityUpdater& interiorVisibilityUpdate,
                                                           InteriorsExplorer::SdkModel::InteriorsExplorerModel& interiorsExplorerModule,
                                                           AppModes::SdkModel::IAppModeModel& appModeModel)
                : m_appCameraController(appCameraController)
                , m_interiorController(interiorController)
                , m_worldCameraController(worldCameraController)
                , m_interiorCameraController(interiorCameraController)
                , m_cameraFrustumStreamingVolume(cameraFrustumStreamingVolume)
                , m_interiorVisibilityUpdate(interiorVisibilityUpdate)
                , m_interiorsExplorerModel(interiorsExplorerModule)
                , m_appModeModel(appModeModel)
                {
                    
                }
                
                const std::vector<Helpers::IStateMachineState*> AppModeStatesFactory::CreateStateMachineStates()
                {
                    std::vector<Helpers::IStateMachineState*> states;
                    
                    const int worldCameraHnadle = m_appCameraController.CreateCameraHandleFromController(m_worldCameraController);
                    const int interiorCameraHandle = m_appCameraController.CreateCameraHandleFromController(m_interiorCameraController);
                    
                    states.push_back(Eegeo_NEW(States::SdkModel::WorldState)(m_appCameraController, worldCameraHnadle));
                    states.push_back(Eegeo_NEW(States::SdkModel::InteriorExplorerState)(m_appCameraController,
                                                                                        m_interiorController,
                                                                                        interiorCameraHandle,
                                                                                        m_cameraFrustumStreamingVolume,
                                                                                        m_interiorVisibilityUpdate,
                                                                                        m_interiorsExplorerModel,
                                                                                        m_appModeModel));
                    
                    return states;
                }
            }
        }
    }
}