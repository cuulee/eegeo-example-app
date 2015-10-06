// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "InteriorsExplorer.h"
#include "Interiors.h"
#include "Types.h"
#include "IInteriorsExplorerModule.h"
#include "WorldPins.h"

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
                                        Eegeo::Resources::Interiors::Markers::InteriorMarkerModelRepository& markerRepository,
                                        WorldPins::SdkModel::IWorldPinsService& worldPinsService);

                ~InteriorsExplorerModule();
                
                View::InteriorsExplorerViewModel& GetInteriorsExplorerViewModel() const;
                
                ScreenControl::View::IScreenControlViewModel& GetScreenControlViewModel() const;

                IInteriorsExplorerInputDelegate& GetInputDelegate() const;
                
            private:
                
                InteriorsExplorerModel* m_pModel;
                View::InteriorsExplorerViewModel* m_pViewModel;
                InteriorsExitObserver* m_pInteriorExitObserver;
                IInteriorsExplorerInputDelegate* m_pInteriorsExplorerInputDelegate;
                InteriorsStreamingController* m_pInteriorsStreamingController;
                InteriorPinScaleController* m_pInteriorPinScaleController;
                
                InteriorWorldPinController* m_pWorldPinController;
            };
        }
    }
}