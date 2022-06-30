using System;
using System.Collections;
using System.Collections.Generic;
using Unigine;


[Component(PropertyGuid = "2d8c6ea54ec34fc0d7e0801f28e8cef24857e1a9")]
public class HandAnimationController : Component
{
	public FirstPersonController fpsController = null;
	public ShootInput shootInput = null;

	public float moveAnimationSpeed = 30.0f;
	public float shootAnimationSpeed = 30.0f;
	public float idleWalkMixDamping = 5.0f;
	public float walkDamping = 5.0f;
	public float shootDamping = 1.0f;

	[ParameterFile(Filter = ".anim")]
	public string idleAnimation = null;

	[ParameterFile(Filter = ".anim")]
	public string moveForwardAnimation = null;

	[ParameterFile(Filter = ".anim")]
	public string moveBackwardAnimation = null;

	[ParameterFile(Filter = ".anim")]
	public string moveRightAnimation = null;

	[ParameterFile(Filter = ".anim")]
	public string moveLeftAnimation = null;

	[ParameterFile(Filter = ".anim")]
	public string shootAnimation = null;

	public vec2 LocalMovementVector
	{
		get
		{
			return new vec2(
				MathLib.Dot(fpsController.SlopeAxisY, fpsController.HorizontalVelocity),
				MathLib.Dot(fpsController.SlopeAxisX, fpsController.HorizontalVelocity)
			);
		}
		set {}
	}

	private ObjectMeshSkinned meshSkinned = null;
	private float currentIdleWalkMix = 0.0f; // 0 means idle animation, 1 means walk animation
	private float currentShootMix = 0.0f; // 0 means idle/walk mix, 1 means shoot animation
	private float currentWalkForward = 0.0f;
	private float currentWalkBackward = 0.0f;
	private float currentWalkRight = 0.0f;
	private float currentWalkLeft = 0.0f;

	private float currentWalkIdleMixFrame = 0.0f;
	private float currentShootFrame = 0.0f;
	private int numShootAnimationFrames = 0;

	private const int numLayers = 6;

	private void Init()
	{
		meshSkinned = node as ObjectMeshSkinned;

		meshSkinned.NumLayers = numLayers;

		meshSkinned.SetAnimation(0, idleAnimation);
		meshSkinned.SetAnimation(1, moveForwardAnimation);
		meshSkinned.SetAnimation(2, moveBackwardAnimation);
		meshSkinned.SetAnimation(3, moveRightAnimation);
		meshSkinned.SetAnimation(4, moveLeftAnimation);
		meshSkinned.SetAnimation(5, shootAnimation);

		int animation = meshSkinned.GetAnimation(5);
		numShootAnimationFrames = meshSkinned.GetNumAnimationFrames(animation);

		for (int i = 0; i < numLayers; ++i)
			meshSkinned.SetLayerEnabled(i, true);
	}

	public void Shoot()
	{
		currentShootMix = 1.0f;
		currentShootFrame = 0.0f;
	}

	private void Update()
	{
		vec2 movementVector = LocalMovementVector;
	
	
		bool isMoving = movementVector.Length2 > MathLib.EPSILON;

		if (shootInput.IsShooting())
			Shoot();

		// calculate target values for layer weights
		float targetIdleWalkMix = (isMoving) ? 1.0f : 0.0f;
		float targetWalkForward = (float) MathLib.Max(0.0f, movementVector.x);
		float targetWalkBackward = (float) MathLib.Max(0.0f, -movementVector.x);
		float targetWalkRight = (float) MathLib.Max(0.0f, movementVector.y);
		float targetWalkLeft = (float) MathLib.Max(0.0f, -movementVector.y);

		// apply current layer weights
		float idleWeight = 1.0f - currentIdleWalkMix;
		float walkMixWeight = currentIdleWalkMix;
		float shootWalkIdleMix = 1.0f - currentShootMix;

		meshSkinned.SetLayerWeight(0, shootWalkIdleMix * idleWeight);
		meshSkinned.SetLayerWeight(1, shootWalkIdleMix * walkMixWeight * currentWalkForward);
		meshSkinned.SetLayerWeight(2, shootWalkIdleMix * walkMixWeight * currentWalkBackward);
		meshSkinned.SetLayerWeight(3, shootWalkIdleMix * walkMixWeight * currentWalkRight);
		meshSkinned.SetLayerWeight(4, shootWalkIdleMix * walkMixWeight * currentWalkLeft);
		meshSkinned.SetLayerWeight(5, currentShootMix);

		// update animation frames
		meshSkinned.SetFrame(0, currentWalkIdleMixFrame);
		meshSkinned.SetFrame(1, currentWalkIdleMixFrame);
		meshSkinned.SetFrame(2, currentWalkIdleMixFrame);
		meshSkinned.SetFrame(3, currentWalkIdleMixFrame);
		meshSkinned.SetFrame(4, currentWalkIdleMixFrame);
		meshSkinned.SetFrame(5, currentShootFrame);

		currentWalkIdleMixFrame += moveAnimationSpeed * Game.IFps;
		currentShootFrame = MathLib.Min(currentShootFrame + shootAnimationSpeed * Game.IFps, numShootAnimationFrames);

		// smoothly update current weight values
		currentIdleWalkMix = MathLib.Lerp(currentIdleWalkMix, targetIdleWalkMix, idleWalkMixDamping * Game.IFps);

		currentWalkForward = MathLib.Lerp(currentWalkForward, targetWalkForward, walkDamping * Game.IFps);
		currentWalkBackward = MathLib.Lerp(currentWalkBackward, targetWalkBackward, walkDamping * Game.IFps);
		currentWalkRight = MathLib.Lerp(currentWalkRight, targetWalkRight, walkDamping * Game.IFps);
		currentWalkLeft = MathLib.Lerp(currentWalkLeft, targetWalkLeft, walkDamping * Game.IFps);

		currentShootMix = MathLib.Lerp(currentShootMix, 0.0f, shootDamping * Game.IFps);
	}
}
