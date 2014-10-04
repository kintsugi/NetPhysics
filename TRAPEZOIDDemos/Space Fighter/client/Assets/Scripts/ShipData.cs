using UnityEngine;
using System;
using System.Collections.Generic;

[Serializable]
public class ShipData {
	[Serializable]
	public struct PartData {
		public Vector3Serializer pos, scale;
		public QuaternionSerializer rot;
		public Vector3Serializer colliderCenter, colliderSize;
		public ShipPart.Type type;
	}
	
	public List<PartData> parts = new List<PartData>();

	public ShipData(GameObject ship) {
		Transform[] partTransforms = ship.GetComponentsInChildren<Transform>();
		foreach (Transform trans in partTransforms) {
			if (trans.tag == "Part Parent") {
				PartData newPart = new PartData();
				//Need the child scale, collider info, and part type.
				Transform childTrans = trans.GetComponentInChildren<Transform>();
				BoxCollider childCollider = trans.GetComponentInChildren<BoxCollider>();
				ShipPart.Type childPartType = trans.GetComponentInChildren<ShipPart>().type;
				//Use parent pos and rotation
				newPart.pos.Fill(trans.position);
				newPart.rot.Fill(trans.rotation);
				//Use child scale, collider, and type
				newPart.scale.Fill(childTrans.localScale);
				newPart.colliderCenter.Fill(childCollider.center);
				newPart.colliderSize.Fill(childCollider.size);
				newPart.type = childPartType;
				Debug.Log(newPart.type);
				parts.Add(newPart);
			}
			/*
			PartData newPart = new PartData();
			newPart.pos.Fill(trans.position);
			newPart.rot.Fill(trans.rotation);
			newPart.scale.Fill(trans.localScale);
			BoxCollider collider = trans.gameObject.GetComponentInChildren<BoxCollider>();
			newPart.colliderCenter.Fill(collider.center);
			newPart.colliderSize.Fill(collider.size);
			newPart.type = trans.gameObject.GetComponentInChildren<ShipPart>().type;
			Debug.Log(newPart.type);
			parts.Add(newPart);
			*/
		}
	}
}

