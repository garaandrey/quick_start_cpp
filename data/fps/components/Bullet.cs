using System;
using System.Collections;
using System.Collections.Generic;
using Unigine;
#region Math Variables
#if UNIGINE_DOUBLE
using Vec3 = Unigine.dvec3;
#else
using Vec3 = Unigine.vec3;
#endif
#endregion

[Component(PropertyGuid = "8b32b5082feb54c7b6988b7ae8aaa4911cd414bc")]
public class Bullet : Component
{
	public float speed = 10.0f;
	public int damage = 1;

	[ParameterFile]
	public string hitPrefab = null;

	[ParameterMask]
	public int intersectionMask = ~0;

	private WorldIntersectionNormal hitInfo = new WorldIntersectionNormal();

	private void Init()
	{
	}
	
	private void Update()
	{
		Vec3 currentPosition = node.WorldPosition;
		vec3 currentDirection = node.GetWorldDirection(MathLib.AXIS.Y);

		node.WorldPosition += currentDirection * speed * Game.IFps;

		Unigine.Object hitObject = World.GetIntersection(currentPosition, node.WorldPosition, intersectionMask, hitInfo);

		if (hitObject == null)
			return;

		Node hitEffect = World.LoadNode(hitPrefab);
		hitEffect.WorldPosition = hitInfo.Point;
		hitEffect.SetWorldDirection(hitInfo.Normal, vec3.UP, MathLib.AXIS.Y);

		// TODO: apply damage
		Health health = hitObject.GetComponent<Health>();
		if (health != null)
			health.TakeDamage(damage);

		node.DeleteLater();
	}
}
