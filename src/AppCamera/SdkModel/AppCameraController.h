// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IAppCameraController.h"
#include "Camera.h"
#include <vector>
#include "GlobeCameraController.h"
#include "VectorMathDecl.h"

namespace ExampleApp
{
    namespace AppCamera
    {
        namespace SdkModel
        {
            class AppCameraController : public IAppCameraController
            {
            private:
                
                std::vector<Eegeo::Camera::GlobeCamera::GlobeCameraController*> m_cameras;
                
                Eegeo::Camera::RenderCamera m_renderCamera;
                
                int m_currentCameraIndex;
                int m_previousCameraIndex;
                bool m_isTransitionInFlight;
                float m_transitionTimer;
                
                Eegeo::dv3 m_currentPosition;
                Eegeo::m33 m_currentOrientation;
                
            public:
                
                AppCameraController(const std::vector<Eegeo::Camera::GlobeCamera::GlobeCameraController*>& cameras);
                ~AppCameraController();
                
                void TransitionToNextCamera();
                
                const bool IsTransitionInFlight() const;
                
                const Eegeo::Camera::CameraState GetCameraState();
                
                const Eegeo::Camera::RenderCamera& GetRenderCamera();
                
                void Update(float dt);
            };
        }
    }
}
