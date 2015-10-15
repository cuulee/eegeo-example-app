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
#include "Tours.h"

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
                    AppCamera::SdkModel::IAppCamera& m_toursCameraController;
                    Eegeo::Streaming::CameraFrustumStreamingVolume& m_cameraFrustumStreamingVolume;
                    InteriorsExplorer::SdkModel::InteriorVisibilityUpdater& m_interiorVisibilityUpdate;
                    AppModes::SdkModel::IAppModeModel& m_appModeModel;
                    InteriorsExplorer::SdkModel::InteriorsExplorerModel& m_interiorsExplorerModel;
                    Tours::SdkModel::ITourService& m_tourService;
                    Eegeo::Resources::Interiors::InteriorSelectionModel& m_interiorSelectionModel;
                    
                public:
                    
                    AppModeStatesFactory(AppCamera::SdkModel::IAppCameraController& appCameraController,
                                         Eegeo::Resources::Interiors::InteriorController& interiorController,
                                         AppCamera::SdkModel::IAppCamera& worldCameraController,
                                         AppCamera::SdkModel::IAppCamera& interiorCameraController,
                                         AppCamera::SdkModel::IAppCamera& toursCameraController,
                                         Eegeo::Streaming::CameraFrustumStreamingVolume& cameraFrustumStreamingVolume,
                                         InteriorsExplorer::SdkModel::InteriorVisibilityUpdater& interiorVisibilityUpdater,
                                         InteriorsExplorer::SdkModel::InteriorsExplorerModel& interiorsExplorerModel,
                                         AppModes::SdkModel::IAppModeModel& appModeModel,
                                         Tours::SdkModel::ITourService& tourService,
                                         Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel);
                    
                    ~AppModeStatesFactory()
                    {
                        
                    }
                    
                    const std::vector<Helpers::IStateMachineState*> CreateStateMachineStates();
                };
            }
        }
    }
}
