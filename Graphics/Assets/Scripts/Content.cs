using UnityEngine;
using System.Collections;
using System;
using System.Collections.Generic;

public class Content : MonoBehaviour {
	
	public List<GameObject> stones = new List<GameObject>();
	public List<int> quantity = new List<int>();//can we rm this ?
	public Egg eggPrefab;

	//enw #eggNbr #nPlayer X Y
	public void layEgg(int eggNo, int playerNo)
	{
		Vector3 spawnPosition;
		spawnPosition.x = transform.position.x;
		spawnPosition.z = transform.position.z;
		spawnPosition.y = transform.position.y;
		Debug.Log (string.Format ("Laying eggno {0} from playerno {1}", eggNo, playerNo));
		Egg newEgg = Instantiate(eggPrefab, spawnPosition, transform.rotation) as Egg;
		newEgg.Init (eggNo, playerNo);
		newEgg.transform.parent = gameObject.transform;
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
					spawnPosition.z = UnityEngine.Random.Range(transform.position.z - 0.5f , transform.position.z + 0.5f);
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
