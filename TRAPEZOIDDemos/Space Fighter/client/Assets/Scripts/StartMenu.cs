using UnityEngine;
using System.Collections;

public class StartMenu : MonoBehaviour {

	// Use this for initialization
	void Start () {
	
	}

	void OnGUI() {
		if (GUI.Button(new Rect((Screen.width - 100) / 2, (Screen.height - 20) / 4, 100, 20), "Ship Builder")) {
			Application.LoadLevel(1);
		}
		if (GUI.Button(new Rect((Screen.width - 100) / 2, ((Screen.height - 20) / 4) * 2, 100, 20), "Multiplayer")) {
		}
		if (GUI.Button(new Rect((Screen.width - 100) / 2, ((Screen.height - 20) / 4) * 3, 100, 20), "Options")) {
		}
	}

	void Update () {
	
	}
}
