// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AppCameraModule.h"
#include "AppCameraController.h"

namespace ExampleApp
{
    namespace AppCamera
    {
        namespace SdkModel
        {
            AppCameraModule::AppCameraModule(Eegeo::Resources::Interiors::InteriorController& interiorController,
                                             Eegeo::Camera::GlobeCamera::GlobeCameraController& worldCameraController,
                                             Eegeo::Camera::GlobeCamera::GlobeCameraController& interiorCameraController)
            {
                m_pAppCameraController = Eegeo_NEW(AppCameraController)();
                
                int worldCameraHandle = m_pAppCameraController->CreateCameraHandleFromController(&worldCameraController);
                int interiorCameraHandle = m_pAppCameraController->CreateCameraHandleFromController(&interiorCameraController);
                
                m_pInteriorStateOberver = Eegeo_NEW(AppCameraInteriorStateObserver)(interiorController,
                                                                                    *m_pAppCameraController,
                                                                                    worldCameraHandle,
                                                                                    interiorCameraHandle);
            }
            
            AppCameraModule::~AppCameraModule()
            {
                Eegeo_DELETE m_pInteriorStateOberver;
                m_pInteriorStateOberver = NULL;
                
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
