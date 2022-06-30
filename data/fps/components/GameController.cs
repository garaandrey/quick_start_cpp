using System;
using System.Collections;
using System.Collections.Generic;
using Unigine;

public enum GameState
{
	Gameplay,
	Win,
	Lose,
}

[Component(PropertyGuid = "99c186143ea2ba6374a0dc66c660c88d75065088")]
public class GameController : Component
{
	public GameState state = GameState.Gameplay;
}
