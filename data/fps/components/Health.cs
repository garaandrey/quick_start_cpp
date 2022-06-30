using System;
using System.Collections;
using System.Collections.Generic;
using Unigine;

[Component(PropertyGuid = "e07687971a39000a4851efe1fb24c7cc27d460bb")]
public class Health : Component
{
	public int health = 5;

	public bool IsDead => health <= 0;

	public void TakeDamage(int damage)
	{
		health = MathLib.Max(health - damage, 0);
	}
}
