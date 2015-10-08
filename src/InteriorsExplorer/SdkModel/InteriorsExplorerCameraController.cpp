// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorsExplorerCameraController.h"

#include "CameraHelpers.h"
#include "EarthConstants.h"
#include "GpsGlobeCameraController.h"
#include "InteriorController.h"
#include "InteriorMarkerModel.h"
#include "InteriorMarkerModelRepository.h"
#include "InteriorsModel.h"
#include "InteriorSelectionModel.h"

#include "GlobeCameraController.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            InteriorsExplorerCameraController::InteriorsExplorerCameraController(
                                                                Eegeo::Resources::Interiors::InteriorController& interiorController,
                                                                Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                                Eegeo::Resources::Interiors::Markers::InteriorMarkerModelRepository& markerRepository,
                                                                Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& globeCameraController,
                                                                ExampleAppMessaging::TSdkModelDomainEventBus& sdkDomainEventBus)
            : m_interiorController(interiorController)
            , m_interiorSelectionModel(interiorSelectionModel)
            , m_markerRepository(markerRepository)
            , m_globeCameraController(globeCameraController)
            , m_sdkDomainEventBus(sdkDomainEventBus)
            , m_cameraEnabled(false)
            , m_tourIsActive(false)
            , m_tourStateChangedBinding(this, &InteriorsExplorerCameraController::OnTourStateChanged)
            {
                // Temp manually set initial cam pos.
                m_globeCameraController.SetView(0, 0, 0, 100);
                
                m_sdkDomainEventBus.Subscribe(m_tourStateChangedBinding);
            }
            
            InteriorsExplorerCameraController::~InteriorsExplorerCameraController()
            {
                m_sdkDomainEventBus.Unsubscribe(m_tourStateChangedBinding);
            }
            
            Eegeo::Camera::CameraState InteriorsExplorerCameraController::GetCameraState() const
            {
                return m_globeCameraController.GetCameraState();
            }
            
            Eegeo::Camera::RenderCamera InteriorsExplorerCameraController::GetRenderCamera() const
            {
                return m_globeCameraController.GetRenderCamera();
            }
            
            Eegeo::ITouchController& InteriorsExplorerCameraController::GetTouchController()
            {
                return m_globeCameraController.GetTouchController();
            }
            
            void InteriorsExplorerCameraController::Update(float dt)
            {
                m_cameraEnabled = m_interiorController.GetCurrentState() != Eegeo::Resources::Interiors::InteriorViewState::NoInteriorSelected && !m_tourIsActive;
                
                if(!m_cameraEnabled)
                {
                    return;
                }
                
                Eegeo_ASSERT(m_interiorSelectionModel.IsInteriorSelected());
                
                m_globeCameraController.Update(dt);
                
                
                if(m_interiorController.InteriorInScene())
                {
                    Eegeo::dv3 cameraInterestEcef = m_globeCameraController.GetInterestBasis().GetPointEcef();
                    cameraInterestEcef = cameraInterestEcef.Norm() * Eegeo::Space::EarthConstants::Radius;
                    
                    const Eegeo::Resources::Interiors::InteriorsModel* pModel = NULL;
                    Eegeo_ASSERT(m_interiorController.TryGetCurrentModel(pModel));
                    
                    Eegeo::v3 relativeCameraInterestEcef = (cameraInterestEcef - pModel->GetTangentBasis().GetPointEcef()).ToSingle();
                    
                    Eegeo::v3 cameraInterestTangentSpace = Eegeo::v3(Eegeo::v3::Dot(relativeCameraInterestEcef, pModel->GetTangentBasis().GetRight()),
                                                                     Eegeo::v3::Dot(relativeCameraInterestEcef, pModel->GetTangentBasis().GetUp()),
                                                                     Eegeo::v3::Dot(relativeCameraInterestEcef, pModel->GetTangentBasis().GetForward()));
                    
                    float tangentBoundsHalfWidth = (pModel->GetTangentSpaceBounds().GetMax().x - pModel->GetTangentSpaceBounds().GetMin().x)*0.5f;
                    float tangentBoundsHalfLength = (pModel->GetTangentSpaceBounds().GetMax().z - pModel->GetTangentSpaceBounds().GetMin().z)*0.5f;
                    
                    // TODO: Clamp to floor.
                    
                    if(cameraInterestTangentSpace.x < -tangentBoundsHalfWidth ||
                       cameraInterestTangentSpace.x > tangentBoundsHalfWidth ||
                       cameraInterestTangentSpace.z < -tangentBoundsHalfLength ||
                       cameraInterestTangentSpace.z > tangentBoundsHalfLength)
                    {
                        float newX = Eegeo::Math::Clamp(cameraInterestTangentSpace.x, -tangentBoundsHalfWidth, tangentBoundsHalfWidth);
                        float newZ = Eegeo::Math::Clamp(cameraInterestTangentSpace.z, -tangentBoundsHalfLength, tangentBoundsHalfLength);
                        cameraInterestTangentSpace.Set(newX, 0.0f, newZ);
                        
                        Eegeo::m33 tangentBasis;
                        pModel->GetTangentBasis().GetBasisOrientationAsMatrix(tangentBasis);
                        relativeCameraInterestEcef = Eegeo::v3::Mul(cameraInterestTangentSpace, tangentBasis);
                        
                        m_globeCameraController.SetInterestLocation(pModel->GetTangentBasis().GetPointEcef() + relativeCameraInterestEcef);
                    }
                }
                else
                {
                    Eegeo_ASSERT(m_markerRepository.Contains(m_interiorSelectionModel.GetSelectedInteriorId()));
                    
                    const Eegeo::Resources::Interiors::Markers::InteriorMarkerModel& marker = m_markerRepository.Get(m_interiorSelectionModel.GetSelectedInteriorId());
                    
                    Eegeo::Space::EcefTangentBasis basis;
                    Eegeo::Camera::CameraHelpers::EcefTangentBasisFromPointAndHeading(marker.GetMarkerLatLongAltitude().ToECEF(), 0.0f, basis);
                    m_globeCameraController.SetView(basis, 300.0f);
                }
            }
            
            void InteriorsExplorerCameraController::OnTourStateChanged(const Tours::TourStateChangedMessage& message)
            {
                m_tourIsActive = message.TourStarted();
            }
        }
    }
}