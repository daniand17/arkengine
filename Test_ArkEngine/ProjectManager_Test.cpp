#include "stdafx.h"
#include "CppUnitTest.h"

#include "ProjectManager.h"
#include "SystemDirectory.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test_ArkEngine
{
	TEST_CLASS(ProjectManager_Test)
	{
	public:

		TEST_METHOD(Construction)
		{
			ProjectManager::Initialize();

			Assert::IsTrue(ProjectManager::Instance() != NULL);


		}

		TEST_METHOD(CreateProject)
		{
			ProjectManager::Initialize();
			ProjectManager * pm = ProjectManager::Instance();

			pm->createNewProjectWithName("ProjectManagerTestProject");
			Assert::IsTrue(SystemDirectory::directoryExists("ProjectManagerTestProject"));
			Assert::IsTrue(SystemDirectory::directoryExists(pm->getCurrentProject()->getResourcesDirectory()));
			Assert::AreEqual(ArkString("ProjectManagerTestProject").toStdString(), pm->getCurrentProject()->getProjectName().toStdString());
		}

		TEST_METHOD(OpenProject)
		{
			ResourceManager::Initialize();
			ProjectManager::Initialize();
			ProjectManager * pm = ProjectManager::Instance();
			pm->openProject("AndysTestProject");

			ResourceManager::Instance()->GetMaterialFactory()->CreateMaterial();
			ResourceManager::Instance()->GetMeshFactory()->LoadMesh("cube.obj");
			ResourceManager::Instance()->GetModelFactory()->createModelFromMaterialAndMeshId(0, 0);
			ProjectManager::Instance()->closeCurrentProject();
		}

	};
}