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

public enum EnemyLogicState
{
	Idle,
	Chase,
	Attack,
}

[Component(PropertyGuid = "fd5ed8930ae584d635e9f63d3d61c2784b99a377")]
public class EnemyLogic : Component
{
	public GameController gameController = null;

	public NavigationMesh navigationMesh = null;
	public Node player = null;
	public Node intersectionSocket = null;
	public float reachRadius = 0.5f;
	public float attackInnerRadius = 5.0f;
	public float attackOuterRadius = 7.0f;
	public float speed = 1.0f;
	public float rotationStiffness = 8.0f;
	public float routeRecalculationInterval = 3.0f;

	[ParameterMask(MaskType = ParameterMaskAttribute.TYPE.INTERSECTION)]
	public int playerIntersectionMask = ~0;

	private EnemyLogicState currentState = EnemyLogicState.Idle;

	private bool targetIsVisible;
	private Vec3 lastSeenPosition;
	private vec3 lastSeenDirection;
	private float lastSeenDistanceSqr;

	private BodyRigid bodyRigid = null;
	private WorldIntersection hitInfo = new WorldIntersection();
	private Node[] hitExcludes = new Node[2];

	private EnemyFireController fireController = null;
	private Health health = null;

	private Queue<Vec3> calculatedRoute = new Queue<Vec3>();

	private PathRoute route = new PathRoute();
	private bool shouldUpdateRoute = true;
	private float lastCalculationTime = 0.0f;

	private bool IsTargetVisible()
	{
		Vec3 direction = (player.WorldPosition - intersectionSocket.WorldPosition);
		Vec3 p0 = intersectionSocket.WorldPosition;
		Vec3 p1 = p0 + direction * 2.0f;

		Unigine.Object hitObject = World.GetIntersection(p0, p1, playerIntersectionMask, hitExcludes, hitInfo);
		if (hitObject == null)
			return false;

		return player.ID == hitObject.ID;
	}

	private void Init()
	{
		route.Radius = 0.0f;
		route.Height = 1.0f;
		route.MaxAngle = 0.5f;

		bodyRigid = node.ObjectBodyRigid;
		hitExcludes[0] = node;
		hitExcludes[1] = node.GetChild(0);

		targetIsVisible = false;
		fireController = node.GetComponent<EnemyFireController>();
		health = node.GetComponentInChildren<Health>();

		shouldUpdateRoute = true;
		lastCalculationTime = Game.Time;
	}

	private void Update()
	{
		if (gameController.state != GameState.Gameplay)
			return;

		if (health != null && health.IsDead)
			node.DeleteLater();

		UpdateTargetState();
		UpdateOrientation();
		UpdateRoute();

		switch (currentState)
		{
			case EnemyLogicState.Idle: ProcessIdleState(); break;
			case EnemyLogicState.Chase: ProcessChaseState(); break;
			case EnemyLogicState.Attack: ProcessAttackState(); break;
		}

		vec4 color = vec4.BLACK;
		switch (currentState)
		{
			case EnemyLogicState.Idle: color = vec4.BLUE; break;
			case EnemyLogicState.Chase: color = vec4.YELLOW; break;
			case EnemyLogicState.Attack: color = vec4.RED; break;
		}

		Visualizer.RenderPoint3D(node.WorldPosition + vec3.UP * 2.0f, 0.25f, color);
		Visualizer.RenderPoint3D(node.WorldPosition + vec3.UP * 3.0f, 0.25f, IsTargetVisible() ? vec4.GREEN : vec4.RED);
		Visualizer.RenderPoint3D(lastSeenPosition, 0.1f, vec4.MAGENTA);

		Visualizer.RenderSphere(attackInnerRadius, node.WorldTransform, vec4.RED);
		Visualizer.RenderSphere(attackOuterRadius, node.WorldTransform, vec4.RED);

		foreach (vec3 route_point in calculatedRoute)
			Visualizer.RenderPoint3D(route_point + vec3.UP, 0.25f, vec4.BLACK);
	}

	private void UpdateRoute()
	{
		if (Game.Time - lastCalculationTime < routeRecalculationInterval)
			return;

		if (shouldUpdateRoute)
		{
			route.Create2D(node.WorldPosition, lastSeenPosition, 1);
			shouldUpdateRoute = false;
		}

		if (route.IsReady)
		{
			if (route.IsReached)
			{
				calculatedRoute.Clear();

				for(int i = 1; i < route.NumPoints; ++i)
					calculatedRoute.Enqueue(route.GetPoint(i));

				shouldUpdateRoute = true;
				lastCalculationTime = Game.Time;
			}
			else
				route.Create2D(node.WorldPosition, lastSeenPosition, 1);
		}
	}

	private void UpdateTargetState()
	{
		targetIsVisible = IsTargetVisible();
		if (targetIsVisible)
			lastSeenPosition = player.WorldPosition;

		lastSeenDirection = (vec3)(lastSeenPosition - node.WorldPosition);
		lastSeenDistanceSqr = lastSeenDirection.Length2;
		lastSeenDirection.Normalize();
	}

	private void UpdateOrientation()
	{
		vec3 direction = lastSeenDirection;
		direction.z = 0.0f;

		quat targetRotation = new quat(MathLib.SetTo(vec3.ZERO, direction.Normalized, vec3.UP, MathLib.AXIS.Y));
		quat currentRotation = node.GetWorldRotation();

		currentRotation = MathLib.Slerp(currentRotation, targetRotation, Game.IFps * rotationStiffness);
		node.SetWorldRotation(currentRotation);
	}

	private void ProcessIdleState()
	{
		// Check idle -> chase transition
		if (targetIsVisible)
		{
			currentState = EnemyLogicState.Chase;
			lastSeenPosition = player.WorldPosition;
		}
	}

	private void ProcessChaseState()
	{
		// Go to the last seen position
		if (calculatedRoute.Count > 0)
		{
			float distanceToTargetSqr = (float)(calculatedRoute.Peek() - node.WorldPosition).Length2;

			bool targetReached = (distanceToTargetSqr < reachRadius * reachRadius);
			if (targetReached)
				calculatedRoute.Dequeue();
		}

		vec3 currentVelocity = bodyRigid.LinearVelocity;
		currentVelocity.x = 0.0f;
		currentVelocity.y = 0.0f;

		if (calculatedRoute.Count > 0)
		{
			vec3 direction = (vec3)(calculatedRoute.Peek() - node.WorldPosition);
			direction.z = 0.0f;
			direction.Normalize();

			currentVelocity.x = direction.x * speed;
			currentVelocity.y = direction.y * speed;
		}

		// Check chase -> attack transition
		if (lastSeenDistanceSqr < attackInnerRadius * attackInnerRadius && targetIsVisible)
		{
			currentState = EnemyLogicState.Attack;
			currentVelocity.x = 0.0f;
			currentVelocity.y = 0.0f;

			if (fireController)
				fireController.StartFiring();
		}

		bodyRigid.LinearVelocity = currentVelocity;
	}

	private void ProcessAttackState()
	{
		// Check attack -> chase transition
		if (lastSeenDistanceSqr > attackOuterRadius * attackOuterRadius || !targetIsVisible)
		{
			currentState = EnemyLogicState.Chase;

			if (fireController)
				fireController.StopFiring();
		}
	}
}
