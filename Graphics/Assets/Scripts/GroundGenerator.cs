using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class GroundGenerator : MonoBehaviour {

	public int	width;
	public int	height;
	public GameObject dalle;
	public GameObject[,] dalles;

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

	// Use this for initialization
	void Start () {

	}
	
	// Update is called once per frame
	void Update () {
	
	}
}
