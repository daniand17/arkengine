#include "stdafx.h"
#include "CppUnitTest.h"

#include <exception>

#include "SystemNotifications.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
#define SIZE_T(exp) static_cast<unsigned int>(exp)
namespace Test_ArkUtils
{
	class MockSubscriber : public NotificationSubscriber
	{
	public:
		MockSubscriber() { for ( int i = 0 ; i < SystemNotifications::ServiceTypes::Num_Services ; i++ ) m_set[i] = false; }
		void onNotify(SystemNotifications::ServiceTypes notifyService) override { m_set[notifyService] = true; }
		bool m_set[SystemNotifications::ServiceTypes::Num_Services];
	};

	TEST_CLASS(SystemNotifiations_Test)
	{

		TEST_METHOD(SystemNotifierBus_Creation)
		{
			SystemNotificationBus bus;
			for ( unsigned int i = 0 ; i < SystemNotifications::ServiceTypes::Num_Services ; i++ )
				Assert::AreEqual(SIZE_T(0), bus.numSubscribers(static_cast<SystemNotifications::ServiceTypes>(i)));
		}

		TEST_METHOD(MockSubscriber_ShouldBeFalse)
		{
			MockSubscriber subscriber;
			for ( unsigned i = 0 ; i < SystemNotifications::Num_Services ; i++ ) Assert::IsFalse(subscriber.m_set[i]);
		}

		TEST_METHOD(SystemNotifierBus_AttachSubscriber)
		{
			SystemNotificationBus bus;
			NotificationSubscriber * sub = new MockSubscriber();
			bus.attachSubscriber(sub, SystemNotifications::OnFixedUpdate);

			Assert::AreEqual(SIZE_T(1), bus.numSubscribers(SystemNotifications::OnFixedUpdate));
		}

		TEST_METHOD(SystemNotifierBus_DetachSubscriber)
		{
			SystemNotificationBus bus;

			NotificationSubscriber * sub = new MockSubscriber();
			bus.attachSubscriber(sub, SystemNotifications::OnFixedUpdate);
			Assert::AreEqual(SIZE_T(1), bus.numSubscribers(SystemNotifications::OnFixedUpdate));
			bus.detachSubscriber(sub, SystemNotifications::OnFixedUpdate);
			Assert::AreEqual(SIZE_T(0), bus.numSubscribers(SystemNotifications::OnFixedUpdate));
		}

		TEST_METHOD(SystemNotifierBus_AttachAndFireEvents)
		{
			SystemNotificationBus bus;
			MockSubscriber * subscriber = new MockSubscriber();

			bus.attachSubscriber(subscriber, SystemNotifications::OnFixedUpdate);
			bus.attachSubscriber(subscriber, SystemNotifications::OnSceneChanged);
			bus.attachSubscriber(subscriber, SystemNotifications::OnUpdate);

			bus.fireNotify(SystemNotifications::OnFixedUpdate);
			Assert::IsTrue(subscriber->m_set[SystemNotifications::OnFixedUpdate]);

			bus.fireNotify(SystemNotifications::OnUpdate);
			Assert::IsTrue(subscriber->m_set[SystemNotifications::OnUpdate]);

			bus.fireNotify(SystemNotifications::OnSceneChanged);
			Assert::IsTrue(subscriber->m_set[SystemNotifications::OnSceneChanged]);
		}
	};
}