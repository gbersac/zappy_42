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
			}
		}
		Camera.main.transform.Translate(width/2 - 0.5f, 10, height/2 - 0.5f, Space.World);
	}

	public void scalecamera()
	{
		Vector3 vp = Camera.main.WorldToViewportPoint (dalles [0, 0].transform.position);

		Debug.Log ("x = " + vp.x + "y = " + vp.y + "z = " + vp.z);
		while (vp.x < 0 || vp.y < 0)
		{
			Debug.Log ("x = " + vp.x + "y = " + vp.y + "z = " + vp.z);
			Camera.main.orthographicSize += 1;
			vp = Camera.main.WorldToViewportPoint(dalles [0, 0].transform.position);
		}
		
	}

	void Start () {
		availableEggs = new List<Egg> ();
	}


}
