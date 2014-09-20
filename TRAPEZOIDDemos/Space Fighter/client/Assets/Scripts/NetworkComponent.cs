using System;
using RakNet;
using UnityEngine;

namespace Network {
	public class NetworkComponent {
		private long networkID = 0;
		//TODO learn about C# attributes
		public RakNetGUID serverGUID = new RakNetGUID();
		public RakPeerInterface peer;
		public RakNet.BitStream input = new RakNet.BitStream();
		public NetworkComponent() {}
		public NetworkComponent(RakPeerInterface peer, RakNetGUID serverGuid, long networkID) {
			this.serverGUID = serverGuid; this.peer = peer; this.networkID = networkID;
		}
		public long GetNetworkID() { return networkID; }
	}
}
