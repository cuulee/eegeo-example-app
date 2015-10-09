// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "InteriorsExplorer.h"
#include "Interiors.h"
#include "Types.h"
#include "IInteriorsExplorerModule.h"
#include "WorldPins.h"
#include "GlobeCamera.h"
#include "Rendering.h"
#include "MapMode.h"
#include "BidirectionalBus.h"
#include "SdkModelDomainEventBus.h"
#include "Metrics.h"
#include "Streaming.h"
#include "IIdentity.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            class InteriorsExplorerModule : public IInteriorsExplorerModule, private Eegeo::NonCopyable
            {
            public:
                InteriorsExplorerModule(Eegeo::Resources::Interiors::InteriorController& interiorController,
                                        Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                        Eegeo::Resources::Interiors::Markers::InteriorMarkerModelRepository& markerRepository,
                                        WorldPins::SdkModel::IWorldPinsService& worldPinsService,
                                        ExampleApp::MapMode::SdkModel::IMapModeModel& mapModeModel,
                                        Eegeo::Camera::GlobeCamera::GlobeCameraControllerFactory& globeCameraControllerFactory,
                                        Eegeo::Streaming::CameraFrustumStreamingVolume& cameraFrustumStreamingVolume,
                                        const Eegeo::Rendering::ScreenProperties& screenProperties,
                                        Eegeo::Helpers::IIdentityProvider& identityProvider,
                                        ExampleAppMessaging::TMessageBus& messageBus,
                                        ExampleAppMessaging::TSdkModelDomainEventBus& sdkDomainEventBus,
                                        Metrics::IMetricsService& metricsService);

                ~InteriorsExplorerModule();
                
                View::InteriorsExplorerViewModel& GetInteriorsExplorerViewModel() const;
                
                ScreenControl::View::IScreenControlViewModel& GetScreenControlViewModel() const;
                
                InteriorsExplorerCameraController& GetInteriorsCameraController() const;
                
                const bool InteriorCameraEnabled() const;
                
                void Update(float dt) const;
                
            private:
                
                InteriorsExplorerModel* m_pModel;
                View::InteriorsExplorerViewModel* m_pViewModel;
                //InteriorsExitObserver* m_pInteriorExitObserver;
                InteriorsStreamingController* m_pInteriorsStreamingController;
                
                InteriorWorldPinController* m_pWorldPinController;
                InteriorsExplorerCameraController* m_pInteriorsCameraController;
                Eegeo::Camera::GlobeCamera::GlobeCameraTouchController* m_pGlobeCameraTouchController;
                Eegeo::Camera::GlobeCamera::GlobeCameraController* m_pGlobeCameraController;
            };
        }
    }
}