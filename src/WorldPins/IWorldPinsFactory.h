// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Pins.h"
#include "WorldPins.h"
#include "Space.h"

namespace ExampleApp
{
	namespace WorldPins
	{
		class IWorldPinsFactory
		{
		public:
			virtual ~IWorldPinsFactory() { }

			virtual Eegeo::Pins::Pin* CreatePin(const Eegeo::Space::LatLong& location,
			                                    int iconIndex) = 0;
		};
	}
}
