#include "stdafx.h"
#include "CppUnitTest.h"

#include "ProjectManager.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
#define SIZE_T(exp) static_cast<unsigned int>(exp)
namespace Test_ArkEngine
{
	TEST_CLASS(ProjectManager_Test)
	{
	public:

		TEST_METHOD(ProjectManager_Init)
		{
			ProjectManager::Initialize();
			Assert::IsTrue(ProjectManager::Instance() != NULL);
		}


		TEST_METHOD(ProjectManager_CreateProject)
		{
			ProjectManager::Initialize();
			ProjectManager * pm = ProjectManager::Instance();

			pm->createNewProjectWithName("ProjectManagerTestProject");
			ArkDirectory dir("ProjectManagerTestProject");
			Assert::IsTrue(dir.exists());
			Assert::IsTrue(pm->getCurrentProject()->getResourceDirectory(ArkProject::ResourceType::Meta)->exists());
			Assert::AreEqual(ArkString("ProjectManagerTestProject").toStdString(), pm->getCurrentProject()->getProjectName().toStdString());
		}


		TEST_METHOD(OpenProject)
		{
			ResourceManager::Initialize();
			ProjectManager::Initialize();

			ResourceManager * rm = ResourceManager::Instance();
			ProjectManager * pm = ProjectManager::Instance();
			pm->openProject("AndysTestProject");

			Assert::AreEqual(SIZE_T(4), rm->GetMeshFactory()->size());

			Assert::IsTrue(rm->GetMaterialFactory()->getResourceByName("DefaultMaterial")->ambient == Vec3(1, 1, 1));
			Assert::AreEqual(rm->GetMeshFactory()->getResourceByName("cube.obj")->name.toStdString(), ArkString("cube.obj").toStdString());

			pm->closeCurrentProject();
			delete rm;
			delete pm;
		}
	};
}