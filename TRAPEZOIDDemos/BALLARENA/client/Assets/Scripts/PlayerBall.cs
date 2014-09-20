using UnityEngine;
using System.Collections;
using Network;

public class PlayerBall : MonoBehaviour {
	public NetworkComponent connection = new NetworkComponent();
	public float sensitivityX = 2f;
	public float sensitivityY = 2f;
	public float rotationX = 0f;
	public float rotationY = 0f;
	public float minimumY = -90f;
	public float maximumY = 90f;
	public float horizontal = 0f;
	public float vertical = 0f;
	public bool noInput = true;
	public bool skipInputCheck;

	void Update() {
		//Handle input from server:
		if (connection.input != null) {
			
			//Skip the message and networkID
			connection.input.IgnoreBytes(sizeof(byte) + sizeof(long));
			//Read position values
			float x, y, z;
			connection.input.Read(out x);
			connection.input.Read(out y);
			connection.input.Read(out z);
			//Assign position values
			transform.position = new Vector3(x, y, z);
			//Reset the input component
			connection.input = null;
		}
		//Keep the mouse from showing and exiting the window. Temporary code. Decomment on build
		Screen.showCursor = false;
		Screen.lockCursor = true;
		//Get Rotation and input axis
		rotationX = transform.eulerAngles.y + Input.GetAxis("Mouse X") * sensitivityX;
		rotationY += Input.GetAxis("Mouse Y") * sensitivityY;
		rotationY = Mathf.Clamp(rotationY, minimumY, maximumY);
		vertical = Input.GetAxis("Vertical");
		//Update perspective
		transform.eulerAngles = new Vector3(-rotationY, rotationX, 0);
		//Create and send bitstream with message NETWORK_COMPONENT_MESSAGE if player wants to move. If they dont, send zero once and dont send until they move again
		if (horizontal != 0 || vertical != 0) {
			//Now that input has been recorded, the input needs to be checked again to avoid resending packets
			noInput = false; skipInputCheck = false;
			RakNet.BitStream outBS = new RakNet.BitStream();
			outBS.Write((byte)Message.NETWORK_COMPONENT_MESSAGE);
			outBS.Write((long)connection.GetNetworkID());
			Vector3 direction = transform.forward;
			outBS.Write(direction.x);
			outBS.Write(direction.y);
			outBS.Write(direction.z);
			outBS.Write(vertical);
			connection.peer.Send(outBS, RakNet.PacketPriority.HIGH_PRIORITY, RakNet.PacketReliability.RELIABLE_ORDERED, (char)0, connection.serverGUID, false);
			
		} else {
			//If input values are zero, need to tell server no force is being added one time.
			noInput = true;	
		}
		//If there is no input and we have not checked yet, send the zero input. This is to avoid sending packets of useless data.
		 if(noInput && !skipInputCheck) {
			//Once we check one time, do not check again until input has been recorded.
			skipInputCheck = true;
			RakNet.BitStream outBS = new RakNet.BitStream();
			outBS.Write((byte)Message.NETWORK_COMPONENT_MESSAGE);
			outBS.Write((long)connection.GetNetworkID());
			outBS.Write(transform.eulerAngles.x);
			outBS.Write(transform.eulerAngles.y);
			outBS.Write(transform.eulerAngles.z);
			outBS.Write(horizontal);
			outBS.Write(vertical);
			connection.peer.Send(outBS, RakNet.PacketPriority.HIGH_PRIORITY, RakNet.PacketReliability.RELIABLE_ORDERED, (char)0, connection.serverGUID, false);
		}
	}
}
