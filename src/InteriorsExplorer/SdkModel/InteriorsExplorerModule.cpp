// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorsExplorerModule.h"
#include "InteriorsExplorerCameraController.h"
#include "InteriorsExplorerViewModel.h"
#include "InteriorsExplorerModel.h"
#include "InteriorsExitObserver.h"
#include "InteriorsStreamingController.h"
#include "InteriorWorldPinController.h"
#include "GpsGlobeCameraController.h"
#include "GpsGlobeCameraControllerFactory.h"
#include "GpsGlobeCameraComponentConfiguration.h"
#include "GlobeCameraTouchControllerConfiguration.h"
#include "GlobeCameraControllerConfiguration.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            InteriorsExplorerModule::InteriorsExplorerModule(Eegeo::Resources::Interiors::InteriorController& interiorController,
                                                             Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                             Eegeo::Resources::Interiors::Markers::InteriorMarkerModelRepository& markerRepository,
                                                             WorldPins::SdkModel::IWorldPinsService& worldPinsService,
                                                             ExampleApp::MapMode::SdkModel::IMapModeModel& mapModeModel,
                                                             Eegeo::Camera::GlobeCamera::GpsGlobeCameraControllerFactory& gpsGlobeCameraControllerFactory,
                                                             Eegeo::Streaming::CameraFrustumStreamingVolume& cameraFrustumStreamingVolume,
                                                             const Eegeo::Rendering::ScreenProperties& screenProperties,
                                                             Eegeo::Helpers::IIdentityProvider& identityProvider,
                                                             ExampleAppMessaging::TMessageBus& messageBus,
                                                             ExampleAppMessaging::TSdkModelDomainEventBus& sdkDomainEventBus,
                                                             Metrics::IMetricsService& metricsService)
            {
                m_pWorldPinController = Eegeo_NEW(InteriorWorldPinController)(interiorController, markerRepository, worldPinsService);
                
                Eegeo::Camera::GlobeCamera::GpsGlobeCameraComponentConfiguration gpsConfig = Eegeo::Camera::GlobeCamera::GpsGlobeCameraComponentConfiguration::CreateDefault();
                Eegeo::Camera::GlobeCamera::GlobeCameraTouchControllerConfiguration touchConfig = Eegeo::Camera::GlobeCamera::GlobeCameraTouchControllerConfiguration::CreateDefault();
                Eegeo::Camera::GlobeCamera::GlobeCameraControllerConfiguration globeCameraConfig = Eegeo::Camera::GlobeCamera::GlobeCameraControllerConfiguration::CreateDefault(false);
                
                globeCameraConfig.terrainFollowingEnabled = false;
                globeCameraConfig.zoomAltitudeLow = 100.0f; // Probably too low.
                globeCameraConfig.maxAltitude = 1000.0f;
                
                m_pGlobeCameraController = gpsGlobeCameraControllerFactory.Create(gpsConfig,
                                                                                  touchConfig,
                                                                                  globeCameraConfig,
                                                                                  screenProperties);
                
                m_pInteriorsCameraController = Eegeo_NEW(InteriorsExplorerCameraController)(interiorController,
                                                                                            interiorSelectionModel,
                                                                                            markerRepository,
                                                                                            *m_pGlobeCameraController,
                                                                                            sdkDomainEventBus);
                
                m_pInteriorsStreamingController = Eegeo_NEW(InteriorsStreamingController)(interiorController, cameraFrustumStreamingVolume);
                
                m_pModel = Eegeo_NEW(InteriorsExplorerModel)(interiorController,
                                                             interiorSelectionModel,
                                                             mapModeModel,
                                                             messageBus,
                                                             metricsService,
                                                             sdkDomainEventBus);
                
                m_pViewModel = Eegeo_NEW(View::InteriorsExplorerViewModel)(false, identityProvider.GetNextIdentity());
            }
            
            InteriorsExplorerModule::~InteriorsExplorerModule()
            {
                Eegeo_DELETE m_pViewModel;
                Eegeo_DELETE m_pModel;
                Eegeo_DELETE m_pInteriorsStreamingController;
                Eegeo_DELETE m_pInteriorsCameraController;
                Eegeo_DELETE m_pGlobeCameraController;
                Eegeo_DELETE m_pWorldPinController;
            }
            
            View::InteriorsExplorerViewModel& InteriorsExplorerModule::GetInteriorsExplorerViewModel() const
            {
                return *m_pViewModel;
            }
            
            ScreenControl::View::IScreenControlViewModel& InteriorsExplorerModule::GetScreenControlViewModel() const
            {
                return *m_pViewModel;
            }
            
            InteriorsExplorerCameraController& InteriorsExplorerModule::GetInteriorsCameraController() const
            {
                return *m_pInteriorsCameraController;
            }
            
            const bool InteriorsExplorerModule::InteriorCameraEnabled() const
            {
                return m_pInteriorsCameraController->InteriorCameraEnabled();
            }
            
            void InteriorsExplorerModule::Update(float dt) const
            {
                m_pInteriorsCameraController->Update(dt);
            }
        }
    }
}