using UnityEngine;
using System.Collections;

public class GroundGenerator : MonoBehaviour {

	public int	width;
	public int	height;
	public GameObject dalle;

	public void Initialize()
	{
		Vector3 spawnPosition;
		spawnPosition.x = 0;
		spawnPosition.y = 0;
		spawnPosition.z = 0;
		
		for (int i = 0; i < width; i++) {
			
			spawnPosition.x = i;
			for (int j = 0; j < height; j++) {
				spawnPosition.z = j;	
				GameObject spawnedObject = Instantiate (dalle, spawnPosition, transform.rotation) as GameObject;
				spawnedObject.transform.parent = gameObject.transform;
				// "bct spawnPosition.x  spawnPosition.z"
				spawnedObject.GetComponent<Content>().createStone("bct " + spawnPosition.x + " " +spawnPosition.z + " 1 2 1 2 1 2");
			}
		}
	}
	// Use this for initialization
	void Start () {

	}
	
	// Update is called once per frame
	void Update () {
	
	}
}
