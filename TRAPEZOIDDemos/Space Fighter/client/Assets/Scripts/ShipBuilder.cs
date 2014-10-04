using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using System;

/*
 * Ship Builder Module.
 * Manages the creation of ships using cubical construction.
 * Works correctly if each block has an area of 1unit^3.
 * TODO Improve floating block detection algortithm.
 * 
 */

public class ShipBuilder : MonoBehaviour {

	//Ship parent object
	public GameObject shipBase;
	//Prefabs
	public GameObject armorPlatePrefab;
	public GameObject shipBasePrefab;
	public GameObject thrusterPrefab;
	//Mouse Settings
	public float xMouseSensitivity = 2;
	public float yMouseSensitivity = 2;
	public float scrollWheelSensitivity = 2;
	//Starting sphereical coordinate (in rads)
	public float theta = 135 * Mathf.Deg2Rad;
	public float phi = Mathf.PI / 4;
	//Mouse Input Axes
	public float xDisplacement = 0;
	public float yDisplacement = 0;
	//Distance from camera to center of the builder (0,0,0)
	public float radius;
	//Builder Settings
	//Scale of which one cubic unit is in unity units
	float scale = 1;
	//Numeric identifier of the selected part.
	ShipPart.Type activePart = ShipPart.Type.NONE;
	//Reference to the game object that is to be placed.
	GameObject activePartObject = null;
	//Reference to the previous hit in the screen space to world space raycast.
	RaycastHit lastHit;
	//Save and Load File Names
	String save = "New Ship", load = "";
	void OnEnable () {
		radius = Vector3.Distance(shipBase.transform.position, Camera.main.transform.position);
	}
	
	void Update () {
		Builder();
	}

	void LateUpdate() {
		UpdateViewPoint();
	}

	void OnGUI() {
		save = GUI.TextField(new UnityEngine.Rect(UnityEngine.Screen.width - 160, 20, 150, 20), save);
		load = GUI.TextField(new UnityEngine.Rect(UnityEngine.Screen.width - 160, 50, 150, 20), load);
		if (GUI.Button(new UnityEngine.Rect(10, 20, 100, 20), "Thruster")) {
			activePart = ShipPart.Type.THRUSTER;
			Destroy(activePartObject); activePartObject = null;
		}
		if (GUI.Button(new UnityEngine.Rect(10, 50, 100, 20), "Armor Plate")) {
			activePart = ShipPart.Type.ARMOR_PLATE;
			Destroy(activePartObject); activePartObject = null;
		}
		if (GUI.Button(new UnityEngine.Rect(UnityEngine.Screen.width - 220, 20, 50, 20), "Save"))
			ShipFile.Save(shipBase, save);
		if (GUI.Button(new UnityEngine.Rect(UnityEngine.Screen.width - 220, 50, 50, 20), "Load")) {
			ShipFile.Load(load);
		}
		if (GUI.Button(new UnityEngine.Rect(10, UnityEngine.Screen.height - 30, 100, 20), "Exit"))
			UnityEngine.Application.LoadLevel(0);
	}

	void UpdateViewPoint() {
		
		//Adjust the spherical coordinates when left mouse button is held down.
		if (Input.GetMouseButton(0)) {
			//Move the x position according to the mouse x axis
			xDisplacement = Input.GetAxis("Mouse X");
			yDisplacement = Input.GetAxis("Mouse Y");
			//Update the angle
			theta -= xDisplacement*0.1f * xMouseSensitivity;
			phi += yDisplacement*0.1f * yMouseSensitivity;
			//theta loops because horizontal movement is not to be restricted
			if(theta < 0)
				theta = 2 * Mathf.PI;
			if(theta > 2 * Mathf.PI)
				theta = 0;
			//phi does not loop. it also cannot equal 0 or PI becuase sin(0) & sin (pi) = 0
			//then the x and y components of the transform would equal zero, altering any rotation that existed.
			if (phi <= 0)
				phi = 0 + 0.001f;
			if (phi >= Mathf.PI)
				phi = Mathf.PI - 0.001f;
		}
		//Update distance from center moveable by the scroll wheel
		radius += Input.GetAxis("Mouse Scroll Wheel") * scrollWheelSensitivity;
		//Update position using parametric equations of a sphere
		Camera.main.transform.position = new Vector3(radius * Mathf.Cos(theta) * Mathf.Sin(phi), radius * Mathf.Cos(phi), radius * Mathf.Sin(theta) * Mathf.Sin(phi));
		//Update rotation
		Camera.main.transform.LookAt(shipBase.transform);
	}

	void Builder() {
		//Raycast from the camera position to the mouse
		RaycastHit info = new RaycastHit();
		//if theres a selected part and the raycast hits an object that us not an active part
		//Only cast the ray when the left mouse button is not down to not interfere with camera movement.
		if (Physics.Raycast(Camera.main.ScreenPointToRay(Input.mousePosition), out info) && !Input.GetMouseButton(0)) {
			if (info.transform.gameObject.GetComponent<ShipPart>().state != ShipPart.State.ACTIVE && activePart != ShipPart.Type.NONE) {
				switch (activePart) {
					case ShipPart.Type.THRUSTER:
						PlaceThruster(info); break;
					case ShipPart.Type.ARMOR_PLATE:
						PlaceArmorPlate(info); 
						break;
				}
			}
			//Stores the object from the raycast. Used for changing the position of placing
			//parts that lie in the same plane as the previous raycast.
			lastHit = info;
		}
		//When there is no active part and the left mouse button is pressed, delete the part that was clicked on
		if (Input.GetMouseButtonUp(0)) {
			if (Physics.Raycast(Camera.main.ScreenPointToRay(Input.mousePosition), out info)) {
				if (info.transform.gameObject.GetComponent<ShipPart>().type != ShipPart.Type.BRIDGE && (info.transform.gameObject.GetComponent<ShipPart>().state != ShipPart.State.ACTIVE)) {
					//TODO: Write better floating block detection algorithm.
					//ManualDelete(info);
					Destroy(info.transform.gameObject);
				}
			}
		}
		//If right mouse button was clicked, place the part
		if (Input.GetMouseButtonUp(1)) {
			PlaceActivePart();
		}
		//If middle mouse button was clicked, reset the active part
		if (Input.GetMouseButtonUp(2)) {
			Destroy(activePartObject); activePartObject = null; activePart = ShipPart.Type.NONE;
		}

	}

	void BuildShipFromData(ShipData data) {
		if (data != null) {
			Destroy(shipBase);
			shipBase = Instantiate(shipBasePrefab) as GameObject;
			foreach(ShipData.PartData part in data.parts) {
				switch (part.type) {
					case ShipPart.Type.ARMOR_PLATE:
						Debug.Log("armor");
						PlacePartFromData(armorPlatePrefab, part); break;
					case ShipPart.Type.THRUSTER:
						Debug.Log("thruster");
						PlacePartFromData(thrusterPrefab, part); break;
				}

			}
		}
	}

	void PlacePartFromData(GameObject partPrefab, ShipData.PartData part) {
		Vector3 position = part.pos.V3; Quaternion rotation = part.rot.Q;
		GameObject newPartObject = Instantiate(partPrefab, position, rotation) as GameObject;
		newPartObject.GetComponentInChildren<Transform>().localScale = part.scale.V3;
		newPartObject.GetComponentInChildren<BoxCollider>().center = part.colliderCenter.V3;
		newPartObject.GetComponentInChildren<BoxCollider>().center = part.colliderSize.V3;
		//No transparency
		Color opaque = newPartObject.GetComponentInChildren<Renderer>().material.color;
		opaque.a = 255f;
		newPartObject.GetComponentInChildren<Renderer>().material.color = opaque;
		newPartObject.transform.parent = shipBase.transform;
	}

	void PlaceActivePart() {
		if (activePartObject != null) {
			GameObject placedPart = Instantiate(activePartObject) as GameObject;
			placedPart.transform.parent = shipBase.transform;
			placedPart.GetComponentInChildren<ShipPart>().state = ShipPart.State.PLACED;
			Color opaque = placedPart.GetComponentInChildren<Renderer>().material.color;
			opaque.a = 255f;
			placedPart.GetComponentInChildren<Renderer>().material.color = opaque;
			Destroy(activePartObject); activePartObject = null;
		}
	}

	void PlaceArmorPlate(RaycastHit info) {
		//Armor plates can not be placed onto thrusters
		if (info.transform.gameObject.GetComponent<ShipPart>().type != ShipPart.Type.THRUSTER) {
			//Cannot place Armor Plate so that it would block a thruster
			//Create the part preemptively
			createActivePart(armorPlatePrefab, info);
			//Check through every part that is a thruster, then raycast in its upwardly direction.
			//If it hits an armor plate, delete the active object
			Transform[] allParts = shipBase.GetComponentsInChildren<Transform>();
			RaycastHit armorPlateCheck = new RaycastHit();
			foreach (Transform part in allParts) {
				if (part.gameObject.GetComponentInChildren<ShipPart>().type == ShipPart.Type.THRUSTER) {
					if (Physics.Raycast(part.position, part.transform.up, out armorPlateCheck)) {
						if (armorPlateCheck.transform.gameObject.GetComponent<ShipPart>().type == ShipPart.Type.ARMOR_PLATE) {
							Destroy(activePartObject); activePartObject = null;
						}
					}
				}
			}
			
		}
	}

	void PlaceThruster(RaycastHit info) {
		//Thrusters can not be placed onto thrusters
		if (info.transform.gameObject.GetComponent<ShipPart>().type != ShipPart.Type.THRUSTER) {
			//Cannot place the thruster if it is blocked by a armor plate
			//Create the part preemptively
			createActivePart(thrusterPrefab, info);
			//Raycast to see if it hits an armor plate in its upwardly direction
			RaycastHit thrusterCheck = new RaycastHit();
			if (Physics.Raycast(activePartObject.transform.position, activePartObject.transform.up, out thrusterCheck)) {
				if (thrusterCheck.transform.gameObject.GetComponent<ShipPart>().type == ShipPart.Type.ARMOR_PLATE) {
					Destroy(activePartObject); activePartObject = null;
				}
			}
		}
	}

	void PlaceThruster(ShipData.PartData part) {
		Vector3 position = part.pos.V3, scale = part.scale.V3,
		colliderCenter = part.colliderCenter.V3,
		colliderSize = part.colliderSize.V3;
		Quaternion rotation = part.rot.Q;
		GameObject thruster = Instantiate(thrusterPrefab, position, rotation) as GameObject;
		thruster.GetComponentInChildren<BoxCollider>().center = colliderCenter;
		thruster.GetComponentInChildren<BoxCollider>().size = colliderSize;
		thruster.GetComponentInChildren<ShipPart>().type = ShipPart.Type.THRUSTER;
		thruster.GetComponentInChildren<ShipPart>().state = ShipPart.State.PLACED;
		Color opaque = thruster.GetComponentInChildren<Renderer>().material.color;
		opaque.a = 255f;
		thruster.GetComponentInChildren<Renderer>().material.color = opaque;
		thruster.transform.parent = shipBase.transform;
	}

	void createActivePart(GameObject part, RaycastHit info) {
		//If the part has not already been placed, place it
		if (!activePartObject) {
			InstantiatePart(info, part);
		}
		//If the rotation of the object is not the same as the direction of the normal vector, it has moved
		else if (activePartObject.transform.rotation != Quaternion.FromToRotation(Vector3.up, info.normal)) {
			Destroy(activePartObject);
			InstantiatePart(info, part);
		//If the object has not rotated but the object the raycast hit is not the same as the previous raycast, it has moved.
		} else if (info.transform.gameObject != lastHit.transform.gameObject) {
			Destroy(activePartObject);
			InstantiatePart(info, part);
		}
	}

	void InstantiatePart(RaycastHit info, GameObject toInstantiate) {
		//Get the transform of the new block by using the raycasthitinfo
		Vector3 transform = CalculatePlacement(info);
		//Rotate the object to the direction of the normal.
		Quaternion rotation = Quaternion.FromToRotation(toInstantiate.transform.up, info.normal);
		activePartObject = Instantiate(toInstantiate, transform, rotation) as GameObject;
	}

	Vector3 CalculatePlacement(RaycastHit info) {
		//A is the object that the new object is being placed on.
		Vector3 centerA = info.transform.position;
		return new Vector3(centerA.x + info.normal.x * scale,
						   centerA.y + info.normal.y * scale,
						   centerA.z + info.normal.z * scale);
	}
	void ManualDelete(RaycastHit info) {
		Vector3[] directions = { Vector3.up, Vector3.down, Vector3.left, Vector3.right, Vector3.forward, Vector3.back };
		bool disconnects = false; bool adjacentToShipBridge = false;
		//If every adjacent block has an block opposite of its rotation 
		//when this block is removed, this block will not disconnect anything.
		GameObject deletedObject = info.transform.gameObject;
		Destroy(info.transform.gameObject);
		RaycastHit check;
		foreach (Vector3 direction in directions) {
			if (Physics.Raycast(info.transform.position, direction, out check, scale)) {
				RaycastHit secondCheck = new RaycastHit();
				if (!Physics.Raycast(check.transform.position, -check.transform.up, out secondCheck, scale)) {
						disconnects = true;
				}
				if (check.transform.gameObject.tag == "Ship Bridge")
					adjacentToShipBridge = true;
			}
		}
		if (adjacentToShipBridge) {
			if (Physics.Raycast(info.transform.position, info.transform.up, out check, scale))
				disconnects = true;
			else
				disconnects = false;
		}
		if (disconnects) {
			Instantiate(deletedObject);
		}
	}
}
