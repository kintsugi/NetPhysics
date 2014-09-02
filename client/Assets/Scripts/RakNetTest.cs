using UnityEngine;
using System;
using System.Collections;
using RakNet;
public class RakNetTest : MonoBehaviour {
	public static string remoteIP = "localhost";
	RakPeerInterface myClient;
	SocketDescriptor scktDist;
	void Awake() {
		myClient = RakPeerInterface.GetInstance();
		scktDist = new SocketDescriptor();
		myClient.Startup(1, scktDist, 1);
		myClient.Connect(remoteIP, 60000, "",0);
	}
}