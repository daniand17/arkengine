#pragma once
#include <list>

class NotificationEvent
{
public:
	enum EventType
	{
		UndefinedService = -1,
		Tick_Update,
		Tick_FixedUpdate,
		System_SceneChanged,
		OnRenderContextChanged,

		System_Startup,
		System_Shutdown,
		System_ProjectLoaded,

		Num_Services
	};

	NotificationEvent(EventType type) : m_type(type) {}
	EventType getType() const { return m_type; }

private:
	EventType m_type;
};

////////////////////////////////////////////////////////////////////////

class NotificationSubscriber
{
public:
	NotificationSubscriber();
	void subscribeToEvent(NotificationEvent::EventType eventType);
	virtual void onNotify(NotificationEvent const * type) = 0;
};

////////////////////////////////////////////////////////////////////////

#define eventSystem SystemNotificationBus::Instance()

class SystemNotificationBus
{
public:
	static SystemNotificationBus * Instance() { return sm_instance; }
	static void Initialize();
	void subscribeToEvent(NotificationSubscriber * subscriber, NotificationEvent::EventType serviceType);
	void unsubscribeFromEvent(NotificationSubscriber * subscriber, NotificationEvent::EventType serviceType);

	size_t numSubscribers(NotificationEvent::EventType service)
	{
		return service > NotificationEvent::UndefinedService
			&& service < NotificationEvent::Num_Services
			? m_subscribers[service].size()
			: 0;
	}
	void fireEvent(NotificationEvent::EventType serviceType);

private:
	typedef std::list<NotificationSubscriber *> SubscriberList;
	SubscriberList m_subscribers[NotificationEvent::Num_Services];

	static SystemNotificationBus * sm_instance;

};