using UnityEngine;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.Serialization.Formatters.Binary;
using System.IO;

public static class ShipFile {

	public static List<String> GetShipNames() {
		string[] files = Directory.GetFiles(Application.persistentDataPath);
		List<String> shipNames = new List<String>();
		foreach (string file in files) {
			if (file.Contains(".sf")) {
				shipNames.Add(file);
			}
		}
		return shipNames;
	}

	public static void Save(GameObject ship, String name) {
		BinaryFormatter bf = new BinaryFormatter();
		FileStream file = File.Create(Application.persistentDataPath + "/" + name + ".sf");
		ShipData shipToSave = new ShipData(ship);
		bf.Serialize(file, shipToSave);
		file.Close();
	}

	public static ShipData Load(String name) {
		if (File.Exists(Application.persistentDataPath + "/" + name + ".sf")) {
			ShipData ret;
			BinaryFormatter bf = new BinaryFormatter();
			FileStream file = File.Open(Application.persistentDataPath + "/" + name + ".sf", FileMode.Open);
			ret = (ShipData)bf.Deserialize(file);
			file.Close();
			return ret;
		}
		return null;
	}
}
