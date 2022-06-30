using System;
using System.Collections;
using System.Collections.Generic;
using Unigine;

[Component(PropertyGuid = "07d6012903c458744bf9a94319183dc6339cfa6d")]
public class ShootInput : Component
{	
	public bool IsShooting()
	{
		return Input.IsMouseButtonDown(Input.MOUSE_BUTTON.LEFT);
	}
}
