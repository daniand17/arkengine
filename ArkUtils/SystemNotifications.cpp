#include "SystemNotifications.h"
using namespace SystemNotifications;

void SystemNotificationBus::attachSubscriber(NotificationSubscriber * subscriber, ServiceTypes serviceType)
{
	if ( subscriber && serviceType > ServiceTypes::UndefinedService && serviceType < ServiceTypes::Num_Services )
	{
		for ( SubscriberList::iterator iter = m_subscribers[serviceType].begin() ; iter != m_subscribers[serviceType].end() ; iter++ )
		{
			if ( (*iter) == subscriber )
				return;
		}

		m_subscribers[serviceType].push_back(subscriber);
	}
}

void SystemNotificationBus::detachSubscriber(NotificationSubscriber * subscriber, ServiceTypes serviceType)
{
	if ( subscriber && serviceType > ServiceTypes::UndefinedService && serviceType < ServiceTypes::Num_Services )
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

void SystemNotificationBus::fireNotify(ServiceTypes serviceType)
{
	if ( serviceType > ServiceTypes::UndefinedService && serviceType < ServiceTypes::Num_Services )
	{
		for ( SubscriberList::iterator iter = m_subscribers[serviceType].begin() ; iter != m_subscribers[serviceType].end() ; iter++ )
		{
			(*iter)->onNotify(serviceType);
		}
	}
}
