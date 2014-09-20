using UnityEngine;
using System.Collections;
using Network;

public class EnemyBall : MonoBehaviour {
	public NetworkComponent connection = new NetworkComponent();

	void Update() {
		//Only update for EnemyBalls are position updates
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
	}
}
