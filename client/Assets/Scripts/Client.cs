using UnityEngine;
using System.Collections;
using System;
using RakNet;
using Network;

public class Client : MonoBehaviour {

	private ArrayList NetworkComponents = new ArrayList();
	private ArrayList enemyBalls = new ArrayList();
	public GameObject playerBallPrefab;
	public GameObject enemyBallPrefab;
	public GameObject camera;
	public AudioSource gameMusic;
	public AudioSource deathSound;
	public AudioSource lostMusic;
	RakPeerInterface peer;
	NetworkIDManager networkIDManager;
	String ipAddress = "localhost";
	String port = "";
	bool connected = false;

	void OnEnable() {
		//Start RakNet
		peer = RakPeerInterface.GetInstance();
		SocketDescriptor sd = new SocketDescriptor();
		peer.Startup(1, sd, 1);
	}

	void OnGUI() {
		
		if (!connected) {
			GUI.Label(new Rect(5, 0, 400, 30), "BALLARENA Version 4.20");
			ipAddress = GUI.TextField(new Rect(5, 20, 150, 20), ipAddress);
			port = GUI.TextField(new Rect(160, 20, 100, 20), port);
			if (GUI.Button(new Rect(270, 20, 75, 20), "Connect")) {
				connect();
			}
		} else
			GUI.Label(new Rect(5, 0, 400, 30), "BALLARENA Version 4.20 (btw you cant mute lol rekt)");
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
		Debug.Log("Attempting to Connect");
		peer.Connect(ipAddress, ushort.Parse(port), "", 0);
	}

	void packetHandler(Packet packet) {
		switch (packet.data[0]) {
			case (byte)DefaultMessageIDTypes.ID_CONNECTION_REQUEST_ACCEPTED:
				connected = true; gameMusic.Play(); break;
			case (byte)DefaultMessageIDTypes.ID_CONNECTION_ATTEMPT_FAILED:
				print("Failed to connect."); break;
			case (byte)Message.NETWORK_COMPONENT_MESSAGE:
				updateNetworkComponent(packet); break;
			case (byte)Message.CREATE_PLAYER_BALL:
				createPlayerBall(packet); break;
			case (byte)Message.CREATE_ENEMY_BALL:
				createEnemyBall(packet); break;
			case (byte)Message.DELETE_ENEMY_BALL:
				deleteEnemyBall(packet); break;
			case (byte)Message.YOU_LOST:
				gameMusic.Stop(); lostMusic.Play();
				break;
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

	void createPlayerBall(Packet packet) {
		long networkID; float radius, x, y, z;
		//Convert the packet to a BitStream
		RakNet.BitStream ballData = new RakNet.BitStream(packet.data, packet.length, false);
		//Ignore the message
		ballData.IgnoreBytes(sizeof(byte));
		//Read the data.
		ballData.Read(out networkID);
		ballData.Read(out radius);
		ballData.Read(out x);
		ballData.Read(out y);
		ballData.Read(out z);
		//Create the ball.
		GameObject playerBall = Instantiate(playerBallPrefab) as GameObject;
		playerBall.GetComponent<PlayerBall>().connection = new NetworkComponent(peer, packet.guid, networkID);
		//Add the NetworkComponent to the NetworkComponents contaner.
		NetworkComponents.Add(playerBall.GetComponent<PlayerBall>().connection);
		//Set transform
		playerBall.GetComponent<Transform>().position = new Vector3(x, y, z);
		playerBall.GetComponent<Transform>().localScale = new Vector3(radius, radius, radius);
		//Attach Camera
		camera.transform.parent = playerBall.transform;
		//camera.transform.position = playerBall.transform.position;
	}

	void createEnemyBall(Packet packet) {
		long networkID; float radius, x, y, z;
		//Convert the packet to a BitStream
		RakNet.BitStream ballData = new RakNet.BitStream(packet.data, packet.length, false);
		//Ignore the message
		ballData.IgnoreBytes(sizeof(byte));
		//Read the data.
		ballData.Read(out networkID);
		ballData.Read(out radius);
		ballData.Read(out x);
		ballData.Read(out y);
		ballData.Read(out z);
		//Create the ball
		GameObject enemyBall = Instantiate(enemyBallPrefab) as GameObject;
		enemyBall.GetComponent<EnemyBall>().connection = new NetworkComponent(peer, packet.guid, networkID);
		//Add the NetworkComponent to the NetworkComponents contaner.
		NetworkComponents.Add(enemyBall.GetComponent<EnemyBall>().connection);
		//Set transform
		enemyBall.GetComponent<Transform>().position = new Vector3(x, y, z);
		enemyBall.GetComponent<Transform>().localScale = new Vector3(radius, radius, radius);
		enemyBalls.Add(enemyBall);
	}

	void deleteEnemyBall(Packet packet) {
		long networkID;
		RakNet.BitStream enemyballData = new RakNet.BitStream(packet.data, packet.length, false);
		//Ignore the message
		enemyballData.IgnoreBytes(sizeof(byte));
		enemyballData.Read(out networkID);
		foreach (GameObject enemy in enemyBalls) {
			if (enemy.GetComponent<EnemyBall>().connection.GetNetworkID() == networkID) {
				Destroy(enemy); break;
			}
		}
		deathSound.Play();
	}
}

