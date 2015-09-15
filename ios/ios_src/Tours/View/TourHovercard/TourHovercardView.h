// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include <string>
#include "AppRunner.h"
#include "TourHovercardViewIncludes.h"
#include "ColorHelpers.h"
#include "FXImageView.h"

@class TourHovercardView;
@class ImageStore;

@interface TourHovercardView : UIView <UIGestureRecognizerDelegate>
{
    UIImage* m_pPlayIconImage;
}

- (id) initWithParams:(float)pinDiameter :(float)pixelScale :(ImageStore*)pImageStore;

- (ExampleApp::Tours::View::TourHovercard::TourHovercardViewInterop*) getInterop;

- (BOOL) consumesTouch:(UITouch *)touch;

- (void) setContent:(const std::string&)name :(const std::string&)data;

- (void) setFullyActive :(float)modality;

- (void) setFullyInactive;

- (void) updatePosition:(float)x :(float)y;

- (CAShapeLayer*) createBubbleLayer:(float)width :(float)height :(float)arrowSize :(float)cornerRadius;

- (void) setPresentationColors :(ExampleApp::Helpers::ColorHelpers::Color)baseColor :(ExampleApp::Helpers::ColorHelpers::Color)textColor;

- (void) clear;

@property (nonatomic, retain) UIView* pMainControlContainer;
@property (nonatomic, retain) UIView* pMainShape;
@property (nonatomic, retain) FXImageView* pBackgroundImage;
@property (nonatomic, retain) FXImageView* pBackgroundSubImage;
@property (nonatomic, retain) UILabel* pNameLabel;
@property (nonatomic, retain) UIView* pNameLabelBackground;

@end