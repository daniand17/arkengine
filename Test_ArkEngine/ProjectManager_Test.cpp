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

			ResourceManager * rm = ResourceManager::Instance();
			ProjectManager * pm = ProjectManager::Instance();
			pm->openProject("AndysTestProject");

			Assert::IsTrue(rm->GetMaterialFactory()->GetMaterialById(0)->ambient == Vec3(1, 1, 1));
			Assert::AreEqual(rm->GetMeshFactory()->GetMeshById(0)->name.toStdString(), ArkString("cube.obj").toStdString());

			pm->closeCurrentProject();
			delete rm;
			delete pm;
		}

		TEST_METHOD(IntegrationTestProject)
		{
			ResourceManager::Initialize();

			ProjectManager::Initialize();

			ResourceManager * rm = ResourceManager::Instance();
			ProjectManager * pm = ProjectManager::Instance();

			pm->openProject("ResourceIntegrationProject");

			MaterialFactory * matFac = rm->GetMaterialFactory();
			MeshFactory * meshFac = rm->GetMeshFactory();
			ShaderFactory * shaderFac = rm->GetShaderFactory();


			ArkRendering::MaterialInfo * matInfo = matFac->GetMaterialById(0);
			Assert::IsTrue(matInfo != NULL);
			Assert::AreEqual(32.0f, matInfo->shininess);

			ArkRendering::ShaderProgram * shaderProgram = shaderFac->GetShaderProgramByResourceId(matInfo->getShaderProgramId());

			Assert::IsTrue(shaderProgram != NULL);

			Assert::AreEqual(ArkString("SimpleVertexShader.vert").toStdString(), shaderProgram->getVertexShader().toStdString());
			Assert::AreEqual(ArkString("SimpleFragmentShader.frag").toStdString(), shaderProgram->getFragmentShader().toStdString());



		}


	};
}