using UnityEngine;
using System;

[Serializable]
public struct Vector3Serializer {
	public float x;
	public float y;
	public float z;

	public void Fill(Vector3 v3) {
		x = v3.x;
		y = v3.y;
		z = v3.z;
	}

	public Vector3 V3 { get { return new Vector3(x, y, z); } }
}

[Serializable]
public struct QuaternionSerializer {
	public float x;
	public float y;
	public float z;
	public float w;

	public void Fill(Quaternion q) {
		x = q.x;
		y = q.y;
		z = q.z;
		w = q.w;
	}

	public Quaternion Q { get { return new Quaternion(x, y, z, w); } }
}