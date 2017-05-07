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



void SystemNotificationBus::fireEvent(NotificationEvent::EventType notifyType, ArkString info)
{
	if ( notifyType > NotificationEvent::EventType::UndefinedService && notifyType < NotificationEvent::EventType::Num_Services )
	{
		NotificationEvent * notificationEvent = new NotificationEvent(notifyType);

		if ( info.length() > 0 )
		{
			notificationEvent->addInfo(info);
		}

		if ( m_queuedEvents.size() > 0 )
		{
			m_queuedEvents.push_back(notificationEvent);
		}
		else
		{
			m_queuedEvents.push_back(notificationEvent);
			while ( m_queuedEvents.size() > 0 )
			{
				NotificationEvent * ev = m_queuedEvents.front();
				executeEvent(m_queuedEvents.front());
				m_queuedEvents.pop_front();
				delete ev;
			}
		}

	}
}



void SystemNotificationBus::executeEvent(NotificationEvent * notificationEvent)
{
	std::list<NotificationSubscriber *> & sublist = m_subscribers[notificationEvent->getType()];

	for ( SubscriberList::iterator iter = sublist.begin() ; iter != sublist.end() ; iter++ )
	{
		(*iter)->onNotify(notificationEvent);
	}
}



NotificationSubscriber::NotificationSubscriber()
{
}



void NotificationSubscriber::subscribeToEvent(NotificationEvent::EventType eventType)
{
	eventSystem->subscribeToEvent(this, eventType);
}