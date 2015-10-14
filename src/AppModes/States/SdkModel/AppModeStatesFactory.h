// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IAppModeStatesFactory.h"
#include <vector>
#include "IStateMachineState.h"
#include "Interiors.h"
#include "Streaming.h"
#include "InteriorsExplorer.h"
#include "AppCamera.h"
#include "AppModes.h"

namespace ExampleApp
{
    namespace AppModes
    {
        namespace States
        {
            namespace SdkModel
            {
                class AppModeStatesFactory : public AppModes::SdkModel::IAppModeStatesFactory
                {
                private:
                    AppCamera::SdkModel::IAppCameraController& m_appCameraController;
                    Eegeo::Resources::Interiors::InteriorController& m_interiorController;
                    AppCamera::SdkModel::IAppCamera& m_worldCameraController;
                    AppCamera::SdkModel::IAppCamera& m_interiorCameraController;
                    Eegeo::Streaming::CameraFrustumStreamingVolume& m_cameraFrustumStreamingVolume;
                    InteriorsExplorer::SdkModel::InteriorVisibilityUpdater& m_interiorVisibilityUpdate;
                    AppModes::SdkModel::IAppModeModel& m_appModeModel;
                    InteriorsExplorer::SdkModel::InteriorsExplorerModel& m_interiorsExplorerModel;
                    
                public:
                    
                    AppModeStatesFactory(AppCamera::SdkModel::IAppCameraController& appCameraController,
                                         Eegeo::Resources::Interiors::InteriorController& interiorController,
                                         AppCamera::SdkModel::IAppCamera& worldCameraController,
                                         AppCamera::SdkModel::IAppCamera& interiorCameraController,
                                         Eegeo::Streaming::CameraFrustumStreamingVolume& cameraFrustumStreamingVolume,
                                         InteriorsExplorer::SdkModel::InteriorVisibilityUpdater& interiorVisibilityUpdater,
                                         InteriorsExplorer::SdkModel::InteriorsExplorerModel& interiorsExplorerModel,
                                         AppModes::SdkModel::IAppModeModel& appModeModel);
                    
                    ~AppModeStatesFactory()
                    {
                        
                    }
                    
                    const std::vector<Helpers::IStateMachineState*> CreateStateMachineStates();
                };
            }
        }
    }
}
