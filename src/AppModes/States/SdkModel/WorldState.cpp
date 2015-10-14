// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WorldState.h"
#include "IAppCameraController.h"

namespace ExampleApp
{
    namespace AppModes
    {
        namespace States
        {
            namespace SdkModel
            {
                WorldState::WorldState(AppCamera::SdkModel::IAppCameraController& cameraController, int worldCameraHandle)
                : m_cameraController(cameraController)
                , m_worldCameraHandle(worldCameraHandle)
                {
                    
                }
                
                WorldState::~WorldState()
                {
                    
                }
                
                void WorldState::Enter()
                {
                    m_cameraController.TransitionToCameraWithHandle(m_worldCameraHandle);
                }
                
                void WorldState::Update(float dt)
                {
                    
                }
                
                void WorldState::Exit()
                {
                    
                }
            }
        }
    }
}