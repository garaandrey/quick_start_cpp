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

[Component(PropertyGuid = "100716360aea981d1dc93ad8ac310057898da1ca")]
public class WeaponController : Component
{
	public PlayerDummy shootingCamera = null;
	public ShootInput shootInput = null;
	public NodeDummy weaponMuzzle = null;
	public VFXController vfx = null;
	public int damage = 1;

	[ParameterMask(MaskType = ParameterMaskAttribute.TYPE.INTERSECTION)]
	public int mask = ~0;

	public void Shoot()
	{
		if (weaponMuzzle)
			vfx.OnShoot(weaponMuzzle.WorldTransform);

		Vec3 p0, p1;
		shootingCamera.GetDirectionFromScreen(out p0, out p1);

		WorldIntersectionNormal hitInfo = new WorldIntersectionNormal();
		Unigine.Object hitObject = World.GetIntersection(p0, p1, mask, hitInfo);

		if (hitObject)
		{
			Visualizer.RenderVector(hitInfo.Point, hitInfo.Point + hitInfo.Normal, vec4.RED, 0.25f, false, 2.0f);
			vfx.OnHit(hitInfo.Point, hitInfo.Normal, hitObject);

			Health health = hitObject.GetComponent<Health>();
			if (health)
				health.TakeDamage(damage);
		}
	}

	private void Update()
	{
		if (shootInput.IsShooting())
			Shoot();
	}
}
