using UnityEngine;
using System.Collections;
using System;
using RakNet;
using Network;

public class Client : MonoBehaviour {

	private ArrayList NetworkComponents = new ArrayList();
	RakPeerInterface peer;
	NetworkIDManager networkIDManager;
	String ipAddress = "localhost";
	String port = "60000";
	bool connected = false;
	bool failedToConnect = false;

	void OnEnable() {
		DontDestroyOnLoad(gameObject);
		//Start RakNet
		peer = RakPeerInterface.GetInstance();
		SocketDescriptor sd = new SocketDescriptor();
		peer.Startup(1, sd, 1);
	}

	void OnGUI() {
		GUI.Label(new Rect(5, 0, 200, 30), "Space Fighter InDev");
		/*if (!connected) {
			ipAddress = GUI.TextField(new Rect(5, 20, 150, 20), ipAddress);
			port = GUI.TextField(new Rect(160, 20, 100, 20), port);
			if (GUI.Button(new Rect(270, 20, 75, 20), "Connect")) {
				connect();
			}
		}
		if (failedToConnect) {
			GUI.Label(new Rect(355, 20, 200, 30), "Failed to Connect.");
		}*/
	}

	void OnApplicationQuit() {
		peer.Shutdown(100, (byte)0, RakNet.PacketPriority.HIGH_PRIORITY);
		RakPeerInterface.DestroyInstance(peer);
	}

	void Update () {
		Packet packet = new Packet();
		for (packet = peer.Receive(); packet != null; peer.DeallocatePacket(packet), packet = peer.Receive()) {
			packetHandler(packet);
		}
	}

	void connect() {
		peer.Connect(ipAddress, ushort.Parse(port), "", 0);
	}

	void packetHandler(Packet packet) {
		switch (packet.data[0]) {
			case (byte)DefaultMessageIDTypes.ID_CONNECTION_REQUEST_ACCEPTED:
				connected = true; failedToConnect = false; break;
			case (byte)DefaultMessageIDTypes.ID_CONNECTION_ATTEMPT_FAILED:
				failedToConnect = true; break;
			case (byte)Message.NETWORK_COMPONENT_MESSAGE:
				updateNetworkComponent(packet); break;
		}
	}

	void updateNetworkComponent(Packet packet) {
		long networkID; RakNet.BitStream ballData = new RakNet.BitStream(packet.data, packet.length, false);
		//Ignore the message
		ballData.IgnoreBytes(sizeof(byte));
		//Read the networkID
		ballData.Read(out networkID);
		//Find the corresponding network component
		foreach (NetworkComponent connection in NetworkComponents) {
			if (connection.GetNetworkID() == networkID) {
				connection.input = new RakNet.BitStream(packet.data, packet.length, true);
			}
		}
	}
}

