// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "InteriorsStreamingController.h"
#include "InteriorController.h"
#include "CameraFrustumStreamingVolume.h"


namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            InteriorsStreamingController::InteriorsStreamingController(Eegeo::Resources::Interiors::InteriorController& interiorController,
                                                                       Eegeo::Streaming::CameraFrustumStreamingVolume& cameraFrustumStreamingVolume)
            : m_interiorController(interiorController)
            , m_cameraFrustumStreamingVolume(cameraFrustumStreamingVolume)
            , m_interiorStateChangedCallback(this, &InteriorsStreamingController::OnInteriorStateChanged)
            {
                m_interiorController.RegisterStateChangedCallback(m_interiorStateChangedCallback);
            }

            InteriorsStreamingController::~InteriorsStreamingController()
            {
                m_interiorController.UnregisterStateChangedCallback(m_interiorStateChangedCallback);
                
                m_cameraFrustumStreamingVolume.SetForceMaximumRefinement(false);
            }

            void InteriorsStreamingController::OnInteriorStateChanged()
            {
                if(m_interiorController.GetCurrentState() == Eegeo::Resources::Interiors::InteriorViewState::NoInteriorSelected)
                {
                    m_cameraFrustumStreamingVolume.SetForceMaximumRefinement(false);
                }
                else
                {
                    m_cameraFrustumStreamingVolume.SetForceMaximumRefinement(true);
                }
            }
        }
    }
}