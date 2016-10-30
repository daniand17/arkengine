#include "stdafx.h"
#include "CppUnitTest.h"

#include "GameObject.h"
#include "Rigidbody.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
#define SIZE_T(exp) static_cast<size_t>(exp)
namespace Test_ArkEngine
{
	TEST_CLASS(GameObject_Test)
	{
		GameObject obj;
		TEST_METHOD(GameObject_Creation)
		{
			Assert::AreEqual(ArkString("New Game Object (GameObject)").toStdString(), obj.toString().toStdString());
			Assert::AreEqual(obj.numComponents(), SIZE_T(0));
			Assert::IsTrue(obj.getTransform() != NULL);
		}


		TEST_METHOD(GameObject_AddComponent)
		{
			obj.addComponent<MeshRenderer>();
			Assert::AreEqual(SIZE_T(1), obj.numComponents());

			MeshRenderer * meshRenderer = obj.getComponent<MeshRenderer>();
			Assert::IsTrue(meshRenderer != NULL);
		}


		TEST_METHOD(GameObject_RemoveComponent)
		{
			obj.removeComponent<MeshRenderer>();

			Assert::IsTrue(obj.getComponent<MeshRenderer>() == NULL);
			Assert::AreEqual(SIZE_T(0), obj.numComponents());
		}


		TEST_METHOD(GameObject_AddMultipleComponents)
		{
			obj.addComponent<Rigidbody>();
			obj.addComponent<MeshRenderer>();
			Assert::AreEqual(SIZE_T(2), obj.numComponents());
		}

		TEST_METHOD(GameObject_RemoveMultipleComponents)
		{
			GameObject theObj;
			theObj.addComponent<Rigidbody>();
			theObj.addComponent<MeshRenderer>();
			Assert::AreEqual(SIZE_T(2), theObj.numComponents());
			Assert::IsTrue(theObj.getComponent<Rigidbody>() != NULL);
			Assert::IsTrue(theObj.getComponent<MeshRenderer>() != NULL);

			theObj.removeComponent<Rigidbody>();
			Assert::AreEqual(SIZE_T(1), theObj.numComponents());
			Assert::IsTrue(theObj.getComponent<Rigidbody>() == NULL);
			Assert::IsTrue(theObj.getComponent<MeshRenderer>() != NULL);
			theObj.removeComponent<MeshRenderer>();

			Assert::AreEqual(SIZE_T(0), theObj.numComponents());
		}

		TEST_METHOD(GameObject_CopyGameObjectFromPointer)
		{
			GameObject * gameObject = new GameObject();
			gameObject->addComponent<Rigidbody>();
			gameObject->addComponent<MeshRenderer>();

			GameObject * copy = new GameObject(gameObject);

			Assert::AreEqual(SIZE_T(2), copy->numComponents());
			
			Assert::IsNotNull(copy->getComponent<Rigidbody>());
			Assert::IsNotNull(copy->getComponent<MeshRenderer>());

		}
	};
}
