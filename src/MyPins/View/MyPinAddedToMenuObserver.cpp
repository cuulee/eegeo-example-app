// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include <string>
#include "MyPinAddedToMenuObserver.h"
#include "MyPinsHelpers.h"
#include "IMenuOptionsModel.h"
#include "MyPinModel.h"
#include "MyPinMenuOption.h"
#include "MyPinMenuOptionFactory.h"
#include "ModalityIgnoredReactionModel.h"

namespace ExampleApp
{
    namespace MyPins
    {
        namespace View
        {
            MyPinAddedToMenuObserver::MyPinAddedToMenuObserver(const std::shared_ptr<SettingsMenu::View::SettingsMenuViewModel>& menuViewModel,
                                                               const std::shared_ptr<View::MyPinsMenuOptionsModel>& menuOptionsModel,
                                                               const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus,
                                                               const std::shared_ptr<Menu::View::IMenuReactionModel>& menuReaction,
                                                               const std::shared_ptr<Menu::View::IModalityIgnoredReactionModel>& ignoredMenuReaction)
                : m_menuViewModel(menuViewModel)
                , m_menuOptionsModel(menuOptionsModel)
                , m_messageBus(messageBus)
                , m_handlerBinding(this, &MyPinAddedToMenuObserver::OnMyPinAddedToMenuMessage)
                , m_menuReaction(menuReaction)
                , m_ignoredMenuReaction(ignoredMenuReaction)
            {
                Eegeo_ASSERT(m_menuViewModel != nullptr);
                Eegeo_ASSERT(m_menuOptionsModel != nullptr);
                Eegeo_ASSERT(m_messageBus != nullptr);
                Eegeo_ASSERT(m_menuReaction != nullptr);
                Eegeo_ASSERT(m_ignoredMenuReaction != nullptr);
                m_messageBus->SubscribeUi(m_handlerBinding);
            }

            MyPinAddedToMenuObserver::~MyPinAddedToMenuObserver()
            {
                m_messageBus->UnsubscribeUi(m_handlerBinding);
            }

            void MyPinAddedToMenuObserver::OnMyPinAddedToMenuMessage(const MyPinAddedToMenuMessage& message)
            {
                const std::string& myPinIcon(message.GetMyPinIcon());

                m_menuOptionsModel->AddItem(ConvertModelDetailToString(message.GetMyPinId()),
                                           message.GetMyPinTitle(),
                                           message.GetMyPinDetails(),
                                           myPinIcon,
                                           MyPinMenuOptionFactory::CreateMyPinMenuOption(message.GetMyPinId(),
                                                                      message.GetMyPinLocation(),
                                                                      message.GetMyPinInteriorId(),
                                                                      message.GetMyPinFloorIndex(),
                                                                      *m_menuViewModel,
                                                                      *m_messageBus,
                                                                      *m_menuReaction,
                                                                      *m_ignoredMenuReaction));
            }
        }
    }
}
