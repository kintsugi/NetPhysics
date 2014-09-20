using System.Collections;

class ShipData {
	public enum Part {
		NONE,
		BRIDGE,
		THRUSTER,
		ARMOR_PLATE,
	}
	public struct PartData {
		public Part partType;
		public float relX, relY, relZ, rotX, rotY, rotZ, rotW;
	}

	ArrayList parts;

	public ShipData() {
		parts = new ArrayList();
		PartData bridge;
		bridge.partType = Part.BRIDGE;
		bridge.relX = 0; bridge.relY = 0; bridge.relZ = 0;
		bridge.rotX = 0; bridge.rotY = 0; bridge.rotZ = 0; bridge.rotW = 0;
	}

	public void addPart(PartData newPart) {
		parts.Add(newPart);
	}
}