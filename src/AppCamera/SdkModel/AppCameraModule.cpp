// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AppCameraModule.h"
#include "AppCameraController.h"
#include "AppGlobeCameraWrapper.h"
#include "InteriorsExplorerCameraController.h"
#include "IToursCameraController.h"

namespace ExampleApp
{
    namespace AppCamera
    {
        namespace SdkModel
        {
            AppCameraModule::AppCameraModule(Eegeo::Resources::Interiors::InteriorController& interiorController,
                                             ExampleApp::Tours::SdkModel::ITourService& tourService,
                                             Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& worldCameraController,
                                             InteriorsExplorer::SdkModel::InteriorsExplorerCameraController& interiorCameraController,
                                             ExampleApp::Tours::SdkModel::Camera::IToursCameraController& tourCameraController)
            {
                m_pAppCameraController = Eegeo_NEW(AppCameraController)();
                
                m_pAppGlobeCameraWrapper = Eegeo_NEW(AppGlobeCameraWrapper)(worldCameraController);
                
                int worldCameraHandle = m_pAppCameraController->CreateCameraHandleFromController(*m_pAppGlobeCameraWrapper);
                int interiorCameraHandle = m_pAppCameraController->CreateCameraHandleFromController(interiorCameraController);
                int tourCameraHandle = m_pAppCameraController->CreateCameraHandleFromController(tourCameraController);
                
                m_pInteriorStateOberver = Eegeo_NEW(AppCameraInteriorStateObserver)(interiorController,
                                                                                    tourService,
                                                                                    *m_pAppCameraController,
                                                                                    worldCameraHandle,
                                                                                    interiorCameraHandle,
                                                                                    tourCameraHandle);
            }
            
            AppCameraModule::~AppCameraModule()
            {
                Eegeo_DELETE m_pInteriorStateOberver;
                m_pInteriorStateOberver = NULL;
             
                Eegeo_DELETE m_pAppGlobeCameraWrapper;
                m_pAppGlobeCameraWrapper = NULL;
                
                Eegeo_DELETE m_pAppCameraController;
                m_pAppCameraController = NULL;
            }
            
            IAppCameraController& AppCameraModule::GetController()
            {
                return *m_pAppCameraController;
            }
            
        }
    }
}
