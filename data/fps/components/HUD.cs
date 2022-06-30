using System;
using System.Collections;
using System.Collections.Generic;
using Unigine;

[Component(PropertyGuid = "370da2d85e1a48578d1649ca7cb12ea1b7bb778c")]
public class HUD : Component
{
	[ParameterFile]
	public string crosshairImage = null;
	public int crosshairSize = 16;

	private WidgetSprite sprite = null;

	private void Init()
	{

		Gui screenGui = Gui.Get();

		sprite = new WidgetSprite(screenGui, crosshairImage);
		sprite.Width = crosshairSize;
		sprite.Height = crosshairSize;

		screenGui.AddChild(sprite, Gui.ALIGN_CENTER | Gui.ALIGN_OVERLAP);
	}
	
	private void Update()
	{
		// write here code to be called before updating each render frame
		
	}
}