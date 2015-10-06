// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorsExplorerModule.h"
#include "InteriorsExplorerViewModel.h"
#include "InteriorsExplorerModel.h"
#include "InteriorsExitObserver.h"
#include "InteriorsExplorerInputDelegate.h"
#include "InteriorsStreamingController.h"
#include "InteriorPinScaleController.h"
#include "InteriorWorldPinController.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            InteriorsExplorerModule::InteriorsExplorerModule(Eegeo::Resources::Interiors::InteriorController& interiorController,
                                                             Eegeo::Resources::Interiors::Markers::InteriorMarkerModelRepository& markerRepository,
                                                             WorldPins::SdkModel::IWorldPinsService& worldPinsService)
            {
                m_pWorldPinController = Eegeo_NEW(InteriorWorldPinController)(interiorController, markerRepository, worldPinsService);
                
                /*m_pModel = Eegeo_NEW(InteriorsExplorerModel)(interiorController,
                                                             interiorSelectionModel,
                                                             mapModeModel,
                                                             messageBus,
                                                             metricsService,
                                                             sdkDomainEventBus);
                
                m_pViewModel = Eegeo_NEW(View::InteriorsExplorerViewModel)(false, identityProvider.GetNextIdentity());
                m_pInteriorExitObserver = Eegeo_NEW(InteriorsExitObserver)(interiorController, globeCameraController, nativeUIFactories);
                m_pInteriorsExplorerInputDelegate = Eegeo_NEW(InteriorsExplorerInputDelegate)(interiorController, globeCameraController, messageBus);
                m_pInteriorsStreamingController = Eegeo_NEW(InteriorsStreamingController)(interiorSelectionController, cameraFrustumStreamingVolume);
                m_pInteriorPinScaleController = Eegeo_NEW(InteriorPinScaleController)(interiorsPinsController, appModeModel, messageBus);*/
            }
            
            InteriorsExplorerModule::~InteriorsExplorerModule()
            {
                Eegeo_DELETE m_pWorldPinController;
                
                /*Eegeo_DELETE m_pInteriorPinScaleController;
                Eegeo_DELETE m_pInteriorsExplorerInputDelegate;
                Eegeo_DELETE m_pInteriorExitObserver;
                Eegeo_DELETE m_pModel;
                Eegeo_DELETE m_pViewModel;
                Eegeo_DELETE m_pInteriorsStreamingController;*/
            }
            
            View::InteriorsExplorerViewModel& InteriorsExplorerModule::GetInteriorsExplorerViewModel() const
            {
                Eegeo_ASSERT(false);
                return *m_pViewModel;
            }
            
            ScreenControl::View::IScreenControlViewModel& InteriorsExplorerModule::GetScreenControlViewModel() const
            {
                Eegeo_ASSERT(false);
                return *m_pViewModel;
            }

            IInteriorsExplorerInputDelegate& InteriorsExplorerModule::GetInputDelegate() const
            {
                Eegeo_ASSERT(false);
                return *m_pInteriorsExplorerInputDelegate;
            }
        }
    }
}