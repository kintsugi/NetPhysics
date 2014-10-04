using UnityEngine;
using System.Collections;

public class StartMenu : MonoBehaviour {
	void OnGUI() {
		GUI.Label(new Rect(5, 0, 200, 30), "Space Fighter InDev");
		if (GUI.Button(new Rect((Screen.width - 100) / 2, (Screen.height - 20) / 4, 100, 20), "Ship Builder")) {
			Application.LoadLevel(1);
		}
		if (GUI.Button(new Rect((Screen.width - 100) / 2, ((Screen.height - 20) / 4) * 2, 100, 20), "Multiplayer")) {
			Application.LoadLevel(2);
		}
		if (GUI.Button(new Rect((Screen.width - 100) / 2, ((Screen.height - 20) / 4) * 3, 100, 20), "Options")) {
		}
	}
}
