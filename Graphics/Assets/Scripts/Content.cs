using UnityEngine;
using System.Collections;
using System;
using System.Collections.Generic;

public class Content : MonoBehaviour {
	
	public List<GameObject> stones = new List<GameObject>();
	public List<int> quantity = new List<int>();

	// Use this for initialization
	void Start () {

	}

	public void	createStone(string answer)
	{
		string [] split = answer.Split (new Char [] {' '});

		if (( int.Parse(split[1]) == transform.position.x) && ( int.Parse(split[2]) == transform.position.z))
		{
			for(int i = 0; i < 6; i++)
			{
				quantity[i] = int.Parse(split[i+3]);
				for (int j = 0; j < quantity[i]; j++)
				{
					Vector3 spawnPosition;
					spawnPosition.x = UnityEngine.Random.Range(transform.position.x - 0.5f , transform.position.x + 0.5f);
					Debug.Log (spawnPosition.x);
					spawnPosition.z = UnityEngine.Random.Range(transform.position.z - 0.5f , transform.position.z + 0.5f);
					Debug.Log (spawnPosition.z);
					spawnPosition.y = transform.position.y;


					GameObject stone = Instantiate (stones[i], spawnPosition, transform.rotation) as GameObject;
					stone.transform.parent = gameObject.transform;
				}
			}
		}
	}

	// Update is called once per frame
	void Update () {

	}
}
