using System;
using System.Collections;
using System.Collections.Generic;
using Unigine;
#region Math Variables
#if UNIGINE_DOUBLE
using Vec3 = Unigine.dvec3;
using Mat4 = Unigine.dmat4;
#else
using Vec3 = Unigine.vec3;
using Mat4 = Unigine.mat4;
#endif
#endregion
[Component(PropertyGuid = "0d37cd3d2effad786f409277eab0cd6aa89b9dc1")]
public class VFXController : Component
{
	[ParameterFile(Filter = ".node")]
	public string hitPrefab = null;

	[ParameterFile(Filter = ".node")]
	public string muzzleFlashPrefab = null;

	public void OnShoot(Mat4 transform)
	{
		if (string.IsNullOrEmpty(hitPrefab))
			return;

		Node muzzleFlashVFX = World.LoadNode(muzzleFlashPrefab);
		muzzleFlashVFX.WorldTransform = transform;
	}

	public void OnHit(Vec3 hitPoint, vec3 hitNormal, Unigine.Object hitObject)
	{
		if (string.IsNullOrEmpty(hitPrefab))
			return;

		Node hitVFX = World.LoadNode(hitPrefab);
		hitVFX.WorldPosition = hitPoint;
		hitVFX.SetWorldDirection(hitNormal, vec3.UP, MathLib.AXIS.Y);
	}
}
