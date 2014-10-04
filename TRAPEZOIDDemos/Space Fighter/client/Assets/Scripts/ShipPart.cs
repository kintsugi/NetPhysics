using UnityEngine;
using System.Collections;
using System;

[Serializable]
public class ShipPart : MonoBehaviour {
	[Serializable]
	public enum Type {
		NONE,
		BRIDGE,
		THRUSTER,
		ARMOR_PLATE,
	}
	[Serializable]
	public enum State {
		ACTIVE,
		PLACED,
	}
	public Type type = Type.NONE;
	public State state = State.ACTIVE;
	public ShipPart() {}
}

