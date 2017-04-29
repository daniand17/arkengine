#include "SystemNotifications.h"

SystemNotificationBus * SystemNotificationBus::sm_instance = NULL;

void SystemNotificationBus::Initialize()
{
	if ( !sm_instance )
	{
		sm_instance = new SystemNotificationBus();
	}
}



void SystemNotificationBus::subscribeToEvent(NotificationSubscriber * subscriber, NotificationEvent::EventType serviceType)
{
	if ( subscriber && serviceType > NotificationEvent::EventType::UndefinedService && serviceType < NotificationEvent::EventType::Num_Services )
	{
		for ( SubscriberList::iterator iter = m_subscribers[serviceType].begin() ; iter != m_subscribers[serviceType].end() ; iter++ )
		{
			if ( (*iter) == subscriber )
				return;
		}

		m_subscribers[serviceType].push_back(subscriber);
	}
}



void SystemNotificationBus::unsubscribeFromEvent(NotificationSubscriber * subscriber, NotificationEvent::EventType serviceType)
{
	if ( subscriber && serviceType > NotificationEvent::EventType::UndefinedService && serviceType < NotificationEvent::EventType::Num_Services )
	{
		for ( SubscriberList::iterator iter = m_subscribers[serviceType].begin() ; iter != m_subscribers[serviceType].end() ; iter++ )
		{
			if ( (*iter) == subscriber )
			{
				m_subscribers[serviceType].erase(iter);
				break;
			}
		}
	}
}



void SystemNotificationBus::fireEvent(NotificationEvent::EventType notifyType)
{
	if ( notifyType > NotificationEvent::EventType::UndefinedService && notifyType < NotificationEvent::EventType::Num_Services )
	{
		NotificationEvent * notificationEvent = new NotificationEvent(notifyType);

		for ( SubscriberList::iterator iter = m_subscribers[notifyType].begin() ; iter != m_subscribers[notifyType].end() ; iter++ )
		{
			(*iter)->onNotify(notificationEvent);
			delete notificationEvent;
		}
	}
}



NotificationSubscriber::NotificationSubscriber()
{
}



void NotificationSubscriber::subscribeToEvent(NotificationEvent::EventType eventType)
{
	eventSystem->subscribeToEvent(this, eventType);
}
