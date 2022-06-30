using System;
using System.Collections;
using System.Collections.Generic;
using Unigine;

[Component(PropertyGuid = "bbb72b9d0271b858ac405fd7fde27b4a6848b221")]
public class EnemyFireController : Component
{
	public Node leftMuzzle = null;
	public Node rightMuzzle = null;

	[ParameterFile]
	public string bulletPrefab = null;

	public float shootInterval = 1.0f;

	private float currentTime = 0.0f;
	private bool isLeft = false;
	private bool isFiring = false;

	public void StartFiring()
	{
		isFiring = true;
	}

	public void StopFiring()
	{
		isFiring = false;
	}

	private void Init()
	{
		currentTime = 0.0f;
		isLeft = false;
	}

	private void Update()
	{
		if (!isFiring)
			return;

		currentTime += Game.IFps;

		if (currentTime > shootInterval)
		{
			currentTime = 0.0f;
			Node bullet = World.LoadNode(bulletPrefab);

			bullet.WorldTransform = (isLeft) ? leftMuzzle.WorldTransform : rightMuzzle.WorldTransform;
			isLeft = !isLeft;
		}
	}
}
