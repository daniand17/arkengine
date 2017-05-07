#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "ArkRendering.h"
#include "ResourceManager.h"
#include "Filestream.h"

#define MATERIAL_DIR "material_test"
#define MATERIAL_NAME ArkString("NewMaterial")
#define SHADER_DIR	"shader_test"
namespace Test_ArkRendering
{
	TEST_CLASS(Material_Synchronization)
	{
	public:

		TEST_METHOD(MaterialInfo_Serialize)
		{
			ArkString testMaterialName("NewMaterial");


			ArkRendering::MaterialInfo matInfo;
			matInfo.m_name = testMaterialName;
			matInfo.diffuse = Vec3::one();
			matInfo.specular = Vec3::one();
			matInfo.ambient = Vec3::one();
			matInfo.shininess = 1;
			matInfo.setShaderProgram(0);

			ArkString sync = matInfo.serialize();

			ArkString expected = "MaterialInfo";
			expected += "\n\tname:" + matInfo.m_name;
			expected += "\n\tambient:" + Vec3::one().ToString();
			expected += "\n\tdiffuse:" + Vec3::one().ToString();
			expected += "\n\tspecular:" + Vec3::one().ToString();
			expected += "\n\tshininess:" + ArkString::Number(1.0f);
			expected += "\n\tshader:";

			Assert::AreEqual(expected.toStdString(), sync.toStdString());
		}

		TEST_METHOD(MaterialFactory_SerializeMaterials)
		{
			ArkString testMaterialName(MATERIAL_NAME);
			MaterialFactory resources;
			ArkDirectory dir(MATERIAL_DIR);
			if ( !dir.exists() )
				dir.mkdir();

			resources.setResourcePath(&dir);
			resources.CreateMaterial(testMaterialName, "DefaultShader");
			resources.CreateMaterial(testMaterialName + testMaterialName, "DefaultShader");
			resources.serializeResources();

			ArkFile * file = dir.getFileByFilename("materials.meta");
			ArkStringList materialContents = file->getFileContents().split(',');
			Assert::AreEqual(static_cast<unsigned int>(2), materialContents.size());

			// TODO More code coverage needed here
		}

		TEST_METHOD(MaterialFactory_DeserializeMaterials)
		{
			MaterialFactory resources;
			ArkDirectory dir(MATERIAL_DIR);

			Assert::IsTrue(dir.exists());
			Assert::AreEqual(static_cast<unsigned int>(1), dir.getFileCount());
			resources.setResourcePath(&dir);
			resources.deserializeResources();

			ArkRendering::MaterialInfo * mat0 = resources.getResourceByName(MATERIAL_NAME);
			ArkRendering::MaterialInfo * mat1 = resources.getResourceByName(MATERIAL_NAME + MATERIAL_NAME);

			Assert::AreEqual(MATERIAL_NAME.toStdString(), mat0->m_name.toStdString());
			Assert::IsTrue(mat0->ambient == Vec3(1, 1, 1));
			Assert::IsTrue(mat0->diffuse == Vec3(1, 1, 1));
			Assert::IsTrue(mat0->specular == Vec3(1, 1, 1));
			Assert::IsTrue(mat0->shininess == 32.0);
			Assert::AreEqual(ArkString("DefaultShader").toStdString(), mat0->getShaderName().toStdString());


			Assert::AreEqual((MATERIAL_NAME + MATERIAL_NAME).toStdString(), mat1->m_name.toStdString());
			Assert::IsTrue(mat1->ambient == Vec3(1, 1, 1));
			Assert::IsTrue(mat1->diffuse == Vec3(1, 1, 1));
			Assert::IsTrue(mat1->specular == Vec3(1, 1, 1));
			Assert::IsTrue(mat1->shininess == 32.0);
			Assert::AreEqual(ArkString("DefaultShader").toStdString(), mat1->getShaderName().toStdString());
		}
	};

	TEST_CLASS(Mesh_Synchronization)
	{
		TEST_METHOD(MeshFactory_LoadMeshesFromFolder)
		{
			ArkDirectory dir("mesh_test");
			Assert::IsTrue(dir.exists());

			Assert::IsTrue(dir.fileExists("cube.obj"));
			Assert::IsTrue(dir.fileExists("rock.obj"));
			Assert::IsTrue(dir.fileExists("sphere.obj"));
			Assert::IsTrue(dir.fileExists("Suzanne.obj"));

			MeshFactory fac;
			fac.setResourcePath(&dir);
			fac.deserializeResources();

			Assert::AreEqual(static_cast<unsigned int>(4), fac.size());
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

	TEST_CLASS(Shader_Synchronization)
	{
		TEST_METHOD(Create_Shader)
		{
			ArkRendering::ShaderProgram newShader("SimpleShader", "SimpleVertexShader.vert", "SimpleFragmentShader.frag");

			ArkString val = newShader.serialize();

			ArkString expected("ShaderProgram");
			expected += "\n\tname:SimpleShader";
			expected += "\n\tvertexShader:" + newShader.getVertexShaderPath();
			expected += "\n\tfragmentShader:" + newShader.getFragmentShaderPath();

			Assert::AreEqual(expected.toStdString(), newShader.serialize().toStdString());
		}

		TEST_METHOD(Synchronize_One_Shader_In_Factory)
		{
			ShaderFactory fac;
			ArkDirectory * dir = new ArkDirectory("shader_test");
			fac.setResourcePath(dir);
			fac.CreateShader("SimpleShader", "SimpleVertexShader.vert", "SimpleFragmentShader.frag");
			fac.serializeResources();

			Filestream file("shaderTest.shaders");
			file.openFile(Filestream::FileOpenType::Read);

			ArkString contents;
			file.readAll(&contents);
			file.closeFile();
			ArkString expected("ShaderProgram");
			expected += "\n\tid:" + ArkString::Number(0);
			expected += "\n\tvertexShader:SimpleVertexShader.vert";
			expected += "\n\tfragmentShader:SimpleFragmentShader.frag";
			
			Assert::AreEqual(expected.toStdString(), contents.toStdString());
		}

		TEST_METHOD(Synchronize_Multiple_Shaders_In_Factory)
		{
			ShaderFactory fac;
			ArkDirectory * dir = new ArkDirectory("shader_test");
			if ( !dir->exists() ) dir->mkdir();
			fac.setResourcePath(dir);

			fac.CreateShader("SimpleShader", "SimpleVertexShader.vert", "SimpleFragmentShader.frag");
			fac.CreateShader("Shader", "vertShader.vert", "fragShader.frag");
			fac.CreateShader("AnotherShader", "vertShader.vert", "fragShader.frag");
			fac.serializeResources();
			
			fac.clear();
			fac.deserializeResources();

			ArkRendering::ShaderProgram * simpleShader = fac.getResourceByName("SimpleShader");
			ArkRendering::ShaderProgram * shader = fac.getResourceByName("Shader");
			ArkRendering::ShaderProgram * anotherShader = fac.getResourceByName("AnotherShader");

			Assert::AreEqual(ArkString(dir->getAbsolutePath() + "SimpleVertexShader.vert").toStdString(),
				simpleShader->getVertexShaderPath().toStdString());
			Assert::AreEqual(ArkString(dir->getAbsolutePath() + "SimpleFragmentShader.frag").toStdString(),
				simpleShader->getFragmentShaderPath().toStdString());

			Assert::AreEqual(ArkString(dir->getAbsolutePath() + "vertShader.vert").toStdString(),
				shader->getVertexShaderPath().toStdString());
			Assert::AreEqual(ArkString(dir->getAbsolutePath() + "fragShader.frag").toStdString(),
				shader->getFragmentShaderPath().toStdString());

			Assert::AreEqual(ArkString(dir->getAbsolutePath() + "vertShader.vert").toStdString(),
				anotherShader->getVertexShaderPath().toStdString());
			Assert::AreEqual(ArkString(dir->getAbsolutePath() + "fragShader.frag").toStdString(),
				anotherShader->getFragmentShaderPath().toStdString());
		}
	};
}