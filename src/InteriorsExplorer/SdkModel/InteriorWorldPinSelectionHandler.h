// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Interiors.h"
#include "IWorldPinSelectionHandler.h"
#include "InteriorController.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            class InteriorWorldPinSelectionHandler : public WorldPins::SdkModel::IWorldPinSelectionHandler
            {
            public:
                
                InteriorWorldPinSelectionHandler(const Eegeo::Resources::Interiors::InteriorId& interiorId,
                                                 Eegeo::Resources::Interiors::InteriorController& interiorController)
                : m_interiorId(interiorId)
                , m_interiorController(interiorController)
                {
                    
                }
                
                void SelectPin()
                {
                    Eegeo_TTY("Select Interior: %s", m_interiorId.Value().c_str());
                    //m_interiorController.SetSelectedInterior(m_interiorId);
                }
                
            private:
                
                Eegeo::Resources::Interiors::InteriorId m_interiorId;
                Eegeo::Resources::Interiors::InteriorController& m_interiorController;
            };
        }
    }
}