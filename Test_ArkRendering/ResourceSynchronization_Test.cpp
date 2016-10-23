#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "ArkRendering.h"
#include "ResourceManager.h"
#include "Filestream.h"

namespace Test_ArkRendering
{
	TEST_CLASS(Material_Synchronization)
	{
	public:

		TEST_METHOD(Synchronize_MaterialInfo)
		{
			ArkRendering::MaterialInfo matInfo;
			matInfo.id = 0;
			matInfo.diffuse = Vec3::one();
			matInfo.specular = Vec3::one();
			matInfo.ambient = Vec3::one();
			matInfo.shininess = 1;
			matInfo.setShaderProgram(0, false);

			ArkString sync = matInfo.Synchronize();

			ArkString expected = "MaterialInfo {";
			expected += "\n\tresourceId\t" + ArkString::Number(0);
			expected += "\n\tambient \t" + Vec3::one().ToString();
			expected += "\n\tdiffuse \t" + Vec3::one().ToString();
			expected += "\n\tspecular \t" + Vec3::one().ToString();
			expected += "\n\tshininess \t" + ArkString::Number(1.0f);
			expected += "\n\tshaderId \t" + ArkString::Number(0);
			expected += "\n}";

			Assert::AreEqual(expected.toStdString(), sync.toStdString());
		}

		TEST_METHOD(Synchronize_Many_Materials)
		{
			MaterialFactory * resources = new MaterialFactory();

			resources->GetMaterialById(resources->CreateMaterial())->setShaderProgram(0, false);
			resources->GetMaterialById(resources->CreateMaterial())->setShaderProgram(0, false);
			resources->SynchronizeResources("synchronizeManyMaterialsTest");

			Filestream instream("synchronizeManyMaterialsTest", "materials");
			instream.OpenFile(Filestream::FileOpenType::Read);
			ArkString fileContents = "";
			instream.ReadAll(&fileContents);

			ArkStringList materialContents = fileContents.split(',');
			Assert::AreEqual(static_cast<size_t>(2), materialContents.size());

			Assert::AreEqual(resources->GetMaterialById(0)->Synchronize().toStdString(), materialContents.at(0).toStdString());
			Assert::AreEqual(resources->GetMaterialById(1)->Synchronize().toStdString(), materialContents.at(1).toStdString());
			delete resources;
		}

		TEST_METHOD(Desynchronize_Many_Materials)
		{
			MaterialFactory * resources = new MaterialFactory();
			resources->DesynchronizeResources("desyncMaterialsTest");

			ArkRendering::MaterialInfo * mat0 = resources->GetMaterialById(0);
			ArkRendering::MaterialInfo * mat1 = resources->GetMaterialById(1);

			Assert::IsTrue(mat0->ambient == Vec3(1, 1, 1));
			Assert::IsTrue(mat0->diffuse == Vec3(1, 1, 1));
			Assert::IsTrue(mat0->specular == Vec3(1, 1, 1));
			Assert::IsTrue(mat0->shininess == 32.0);

			Assert::IsTrue(mat1->ambient == Vec3(2, 2, 2));
			Assert::IsTrue(mat1->diffuse == Vec3(1, 1, 1));
			Assert::IsTrue(mat1->specular == Vec3(1.234f, 1.567f, 1.0f));
			Assert::IsTrue(mat1->shininess == 0.0);

			delete resources;
		}
	};

	TEST_CLASS(Mesh_Synchronization)
	{
		TEST_METHOD(Synchronize_MeshInfo)
		{
			ArkRendering::MeshInfo meshInfo;
			meshInfo.name = "cube.obj";

			ArkString sync = meshInfo.Synchronize();

			ArkString expected = "MeshInfo\n";
			expected += "\tname:cube.obj";

			Assert::AreEqual(expected.toStdString(), sync.toStdString());
		}

		TEST_METHOD(Synchronize_Many_Meshes)
		{
			MeshFactory * meshFactory = new MeshFactory();
			meshFactory->LoadMesh("cube.obj");
			meshFactory->LoadMesh("suzanne.obj");
			meshFactory->LoadMesh("rock.obj");

			meshFactory->SynchronizeResources("synchronizeManyMeshesTest");

			Filestream instream("synchronizeManyMeshesTest", "meshes");
			instream.OpenFile(Filestream::FileOpenType::Read);
			ArkString contents("");
			instream.ReadAll(&contents);

			ArkStringList meshes = contents.split(',');
			Assert::AreEqual(static_cast<size_t>(3), meshes.size());

			Assert::AreEqual(ArkString("cube.obj").toStdString(), meshes.at(0).split('\n').at(1).split(':').at(1).toStdString());
			Assert::AreEqual(ArkString("suzanne.obj").toStdString(), meshes.at(1).split('\n').at(1).split(':').at(1).toStdString());
			Assert::AreEqual(ArkString("rock.obj").toStdString(), meshes.at(2).split('\n').at(1).split(':').at(1).toStdString());

			delete meshFactory;
		}

		TEST_METHOD(Desynchronize_Many_Meshes)
		{
			MeshFactory * meshFactory = new MeshFactory();
			meshFactory->DesynchronizeResources("desyncManyMeshesTest");


			Assert::AreEqual(static_cast<size_t>(2), meshFactory->size());
			
			ArkRendering::MeshInfo * cubeMesh = meshFactory->GetMeshById(0);
			ArkRendering::MeshInfo * suzanneMesh = meshFactory->GetMeshById(1);

			Assert::AreEqual(ArkString("cube.obj").toStdString(), cubeMesh->name.toStdString());
			Assert::AreEqual(ArkString("suzanne.obj").toStdString(), suzanneMesh->name.toStdString());
			Assert::AreEqual(static_cast<size_t>(36), cubeMesh->vertices.size());
			Assert::AreEqual(static_cast<size_t>(2904), suzanneMesh->vertices.size());

			delete meshFactory;
		}

		TEST_METHOD(CreateMeshesSyncAndDesync)
		{
			ArkString testName = "CreateMeshesSyncAndDesync";
			MeshFactory * fac0 = new MeshFactory();
			fac0->LoadMesh("cube.obj");
			size_t vertSize = fac0->GetMeshById(0)->vertices.size();
			Assert::AreEqual(static_cast<size_t>(36), vertSize);
			fac0->SynchronizeResources(testName);
			delete fac0;

			MeshFactory * fac1 = new MeshFactory();
			fac1->DesynchronizeResources(testName);
			Assert::AreEqual(static_cast<size_t>(1), fac1->size());
			Assert::AreEqual(vertSize, fac1->GetMeshById(0)->vertices.size());
			delete fac1;
		}

	};

	TEST_CLASS(Model_Synchronization)
	{
		TEST_METHOD(Synchronize_ModelInfo)
		{

		}

		TEST_METHOD(Synchronize_Many_Models)
		{

		}

		TEST_METHOD(Desynchronize_Many_Models)
		{

		}
	};
}