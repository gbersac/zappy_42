using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class GroundGenerator : MonoBehaviour {

	public int	width;
	public int	height;
	public GameObject dalle;
	public GameObject[,] dalles;
	public List<Egg> availableEggs;
	private string []ressoucesNames = {
		"Nourriture(Clone)",
		"linemate(Clone)",
		"deraumere(Clone)",
		"sibur(Clone)",
		"mediane(Clone)",
		"phiras(Clone)",
		"thysame(Clone)"
	};

	public void RemoveStone(int x, int z, int no)
	{
		try
		{
			Transform target = dalles [x, z].transform;
			Transform stone = target.FindChild (ressoucesNames [no]);
			Destroy (stone.gameObject);
		}
		catch
		{
			Debug.Log("No stone of given type at location X: " + x + " y: " + z);
		}
	}

	public void Initialize()
	{
		dalles = new GameObject[width,height];
		Vector3 spawnPosition;
		spawnPosition.x = 0;
		spawnPosition.y = 0;
		spawnPosition.z = 0;
		
		for (int i = 0; i < width; i++) {
			
			spawnPosition.x = i;
			for (int j = 0; j < height; j++) {
				spawnPosition.z = j;	
				dalles[i,j] = Instantiate (dalle, spawnPosition, transform.rotation) as GameObject;
				dalles[i,j].transform.parent = gameObject.transform;
				// "bct spawnPosition.x  spawnPosition.z"
		//		dalles[i][j].GetComponent<Content>().createStone("bct " + spawnPosition.x + " " +spawnPosition.z + " 1 2 1 2 1 2");
			}
		}
		Camera.main.transform.Translate(width/2, 10, height/2, Space.World);
	}

	void Start () {
		availableEggs = new List<Egg> ();
	}
}
