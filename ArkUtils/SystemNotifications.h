#pragma once
#include <list>

namespace SystemNotifications
{
	enum ServiceTypes
	{
		UndefinedService = -1,
		OnUpdate,
		OnFixedUpdate,
		OnSceneChanged,
		OnRenderContextChanged,
		Num_Services
	};
}



class NotificationSubscriber
{
public:
	virtual void onNotify(SystemNotifications::ServiceTypes type) = 0;
};



class SystemNotificationBus
{
public:
	void attachSubscriber(NotificationSubscriber * subscriber, SystemNotifications::ServiceTypes serviceType);
	void detachSubscriber(NotificationSubscriber * subscriber, SystemNotifications::ServiceTypes serviceType);

	unsigned int numSubscribers(SystemNotifications::ServiceTypes service)
	{
		return
			service > SystemNotifications::ServiceTypes::UndefinedService
			&& service < SystemNotifications::ServiceTypes::Num_Services
			? m_subscribers[service].size()
			: 0;
	}

	void fireNotify(SystemNotifications::ServiceTypes serviceType);

private:
	typedef std::list<NotificationSubscriber *> SubscriberList;
	SubscriberList m_subscribers[SystemNotifications::ServiceTypes::Num_Services];
};



