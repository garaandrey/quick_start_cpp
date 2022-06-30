#include "ObjectGenerator.h"

using namespace Unigine;

REGISTER_COMPONENT(ObjectGenerator);

void ObjectGenerator::init()
{
	//========================== NEW - BEGIN ===============================
	if (levelManager)
	{
		//=========================== NEW - END ================================	
				// cube 
		MeshPtr meshBox = Mesh::create();
		meshBox->addBoxSurface("box_surface", Math::vec3(1.0f));
		ObjectMeshStaticPtr box = ObjectMeshStatic::create(meshBox);
		//========================== NEW - BEGIN ===============================
		box->setParent(levelManager);
		//========================== NEW - END ===============================
		box->setTriggerInteractionEnabled(1);
		box->setIntersectionMask(0x00000080, meshBox->findSurface("box_surface")); // check the BulletIntersection bit
		box->setWorldTransform(translate(Math::Vec3(0.5f, 7.5f, 1.0f)));
		box->setMaterialPath("materials/mesh_base_0", "*");
		box->setName("box");
		Unigine::BodyRigidPtr bodyBox = BodyRigid::create(box);
		ShapeBoxPtr shapeBox = ShapeBox::create(bodyBox, Math::vec3(1.0f));
		ShapeSphere::create(bodyBox, 0.5f);
		bodyBox->setShapeBased(0);
		bodyBox->setMass(2.0f);

		// sphere
		MeshPtr meshSphere = Mesh::create();
		meshSphere->addSphereSurface("sphere_surface", 0.5f, 9, 32);
		ObjectMeshStaticPtr sphere = ObjectMeshStatic::create(meshSphere);
		//========================== NEW - BEGIN ===============================
		sphere->setParent(levelManager);
		//========================== NEW - END ===============================
		sphere->setTriggerInteractionEnabled(1);
		sphere->setIntersectionMask(0x00000080, meshSphere->findSurface("sphere_surface")); // check the BulletIntersection bit
		sphere->setWorldTransform(translate(Math::Vec3(4.5f, 5.5f, 1.0f)));
		sphere->setMaterialPath("materials/mesh_base_1", "*");
		sphere->setName("sphere");
		BodyRigidPtr bodySphere = BodyRigid::create(sphere);
		ShapeSphere::create(bodySphere, 0.5f);
		bodySphere->setShapeBased(0);
		bodySphere->setMass(2.0f);

		// capsule
		MeshPtr meshCapsule = Mesh::create();
		meshCapsule->addCapsuleSurface("capsule_surface", 0.5f, 1.0f, 9, 32);
		ObjectMeshStaticPtr capsule = ObjectMeshStatic::create(meshCapsule);
		//========================== NEW - BEGIN ===============================
		capsule->setParent(levelManager);
		//========================== NEW - END ===============================
		capsule->setTriggerInteractionEnabled(1);
		capsule->setIntersectionMask(0x00000080, meshCapsule->findSurface("capsule_surface")); // check the BulletIntersection bit
		capsule->setWorldTransform(translate(Math::Vec3(4.5f, 0.5f, 3.0f)));
		capsule->setMaterialPath("materials/mesh_base_2", "*");
		capsule->setName("capsule");
		BodyRigidPtr bodyCapsule = BodyRigid::create(capsule);
		ShapeCapsule::create(bodyCapsule, 0.5f, 1.0f);
		bodyCapsule->setShapeBased(0);
		bodyCapsule->setMass(2.0f);
		//========================== NEW - BEGIN ===============================
	}
	//=========================== NEW - END ================================
}