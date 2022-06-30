using System;
using System.Collections;
using System.Collections.Generic;
using Unigine;

[Component(PropertyGuid = "1b0fc5af3316b742c70c8db92f9adbc4d1003453")]
public class PlayerLogic : Component
{
	private Health health = null;
	public GameController gameController = null;

	private void Init()
	{
		health = node.GetComponentInChildren<Health>();
	}
	
	private void Update()
	{
		if (health != null && health.IsDead)
		{
			node.DeleteLater();
			Game.Player = null;
			gameController.state = GameState.Lose;
		}
	}
}
