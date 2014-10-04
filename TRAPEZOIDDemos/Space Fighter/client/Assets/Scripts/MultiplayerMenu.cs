using UnityEngine;
using System.Collections;

public class MultiplayerMenu : MonoBehaviour {
	public GameObject client;
	string ipAddress = "";
	string port  ="";
	void OnGUI() {
		if (GUI.Button(new UnityEngine.Rect(10, UnityEngine.Screen.height - 30, 100, 20), "Exit"))
			UnityEngine.Application.LoadLevel(0);
		//If not connected yet, show the connect menu
		if (!client.GetComponent<Client>().connected) {
			GUI.Label(new Rect((Screen.width / 2) - 50, (Screen.height / 2) - 100, 150, 20), "Enter IP Address: ");
			ipAddress = GUI.TextField(new Rect((Screen.width / 2) - 50, (Screen.height / 2) - 70, 100, 20), port);
			GUI.Label(new Rect((Screen.width / 2) - 50, (Screen.height / 2) - 40, 100, 20), "Enter Port: ");
			port = GUI.TextField(new Rect((Screen.width / 2) - 50, (Screen.height / 2) - 10, 100, 20), port);
			if (GUI.Button(new Rect((Screen.width / 2) - 50, (Screen.height / 2) + 20, 100, 20), "Connect")) {
				client.GetComponent<Client>().connect(ipAddress, port);
			}
		}
	}
}
