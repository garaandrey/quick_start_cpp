using System;
using System.Collections;
using System.Collections.Generic;
using Unigine;

[Component(PropertyGuid = "d798d617fcbdfc8a6e2dc2610bad784cb198573b")]
public class Lifetime : Component
{
	[ShowInEditor][Parameter(Tooltip = "Object's lifetime")]
	private float lifeTime = 1.0f;

	private float startTime = 0.0f;

	void Init()
	{
		// remember initialization time of an object
		startTime = Game.Time;
	}

	void Update()
	{
		// wait until the lifetime ends and delete the object
		if (Game.Time - startTime > lifeTime)
			node.DeleteLater();
	}
}
