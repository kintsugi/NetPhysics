using UnityEngine;
using System.Collections;

/*
 * Ship Builder Module.
 * Manages the creation of ships using cubical construction.
 * Works correctly if each block has an area of 1unit^3.
 * TODO Write algorithm so at the end of construction there are no floating blocks
 * i.e. every block is connected to the bridge.
 */

public class ShipBuilder : MonoBehaviour {

	//Ship parent object
	public GameObject ship;
	//Prefabs
	public GameObject thrusterPrefab;
	public GameObject armorPlatePrefab;
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
	ShipData.Part activePart = ShipData.Part.NONE;
	//Reference to the game object that is to be placed.
	GameObject activePartObject = null;
	//Reference to the previous hit in the screen space to world space raycast.
	RaycastHit lastHit;
	void Start () {
		radius = Vector3.Distance(ship.transform.position, Camera.main.transform.position);
	}
	
	void Update () {
		Builder();
	}

	void LateUpdate() {
		UpdateViewPoint();
	}

	void OnGUI() {
		if (GUI.Button(new Rect(10, 20, 100, 20), "Thruster")) {
			activePart = ShipData.Part.THRUSTER;
			Destroy(activePartObject); activePartObject = null;
		}
		if (GUI.Button(new Rect(10, 50, 100, 20), "Armor Plate")) {
			activePart = ShipData.Part.ARMOR_PLATE;
			Destroy(activePartObject); activePartObject = null;
		}
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
		Camera.main.transform.LookAt(ship.transform);
	}

	void Builder() {
		//Raycast from the camera position to the mouse
		RaycastHit info = new RaycastHit();
		//if theres a selected part and the raycast hits an object that us not an active part
		//Only cast the ray when the left mouse button is not down to not interfere with camera movement.
		if (Physics.Raycast(Camera.main.ScreenPointToRay(Input.mousePosition), out info) && !Input.GetMouseButton(0)) {
			if (info.transform.gameObject.tag != "Active Part" && activePart != ShipData.Part.NONE) {
				switch (activePart) {
					case ShipData.Part.THRUSTER:
						PlaceThruster(info); break;
					case ShipData.Part.ARMOR_PLATE:
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
				if (info.transform.gameObject.tag != "Ship Bridge" && (info.transform.gameObject.tag != "Active Part")) {
					ManualDelete(info);
				}
			}
		}
		//If right mouse button was clicked, place the part
		if (Input.GetMouseButtonUp(1)) {
			PlaceActivePart();
		}
		//If middle mouse button was clicked, reset the active part
		if (Input.GetMouseButtonUp(2)) {
			Destroy(activePartObject); activePartObject = null; activePart = ShipData.Part.NONE;
		}

	}

	void PlaceActivePart() {
		if (activePartObject != null) {
			GameObject placedPart = Instantiate(activePartObject) as GameObject;
			placedPart.transform.parent = ship.transform; placedPart.tag = "Placed Part";
			Color opaque = placedPart.GetComponent<Renderer>().material.color;
			opaque.a = 255f;
			placedPart.GetComponent<Renderer>().material.color = opaque;
			Destroy(activePartObject); activePartObject = null;
		}
	}

	void PlaceThruster(RaycastHit info) {
		//Thrusters can not be placed onto thrusters
		if (info.transform.gameObject.GetComponent<ShipPart>().tag != "Thruster") {
			//Cannot place the thruster if it is blocked by a armor plate
			//Create the part preemptively
			createActivePart(thrusterPrefab, info);
			//Raycast to see if it hits an armor plate in its upwardly direction
			RaycastHit thrusterCheck = new RaycastHit();
			if (Physics.Raycast(activePartObject.transform.position, activePartObject.transform.up, out thrusterCheck)) {
				if (thrusterCheck.transform.gameObject.GetComponent<ShipPart>().tag == "Armor Plate") {
					Destroy(activePartObject); activePartObject = null;
				}
			}
		}
	}

	void PlaceArmorPlate(RaycastHit info) {
		//Armor plates can not be placed onto thrusters
		if (info.transform.gameObject.GetComponent<ShipPart>().tag != "Thruster") {
			//Cannot place Armor Plate so that it would block a thruster
			//Create the part preemptively
			createActivePart(armorPlatePrefab, info);
			//Check through every part that is a thruster, then raycast in its upwardly direction.
			//If it hits an armor plate, delete the ac
			Transform[] allParts = ship.GetComponentsInChildren<Transform>();
			RaycastHit armorPlateCheck = new RaycastHit();
			foreach (Transform part in allParts) {
				if (part.gameObject.GetComponent<ShipPart>().tag == "Thruster") {
					if (Physics.Raycast(part.position, part.transform.up, out armorPlateCheck)) {
						if (armorPlateCheck.transform.gameObject.GetComponent<ShipPart>().tag == "Armor Plate") {
							Destroy(activePartObject); activePartObject = null;
						}
					}
				}
			}
			
		}
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
