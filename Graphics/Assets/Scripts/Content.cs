using UnityEngine;
using System.Collections;
using System;
using System.Collections.Generic;

public class Content : MonoBehaviour {
	
	public List<GameObject> stones = new List<GameObject>();
	public List<int> quantity = new List<int>();
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
			for(int i = 0; i < 7; i++)
			{
				quantity[i] = int.Parse(split[i+3]);
				for (int j = 0; j < quantity[i]; j++)
				{
					Vector3 spawnPosition;
					spawnPosition.x = UnityEngine.Random.Range(transform.position.x - 0.5f , transform.position.x + 0.5f);
					spawnPosition.z = UnityEngine.Random.Range(transform.position.z - 0.5f , transform.position.z + 0.5f);
					spawnPosition.y = 0.2f;

					GameObject stone = Instantiate (stones[i], spawnPosition, transform.rotation) as GameObject;
					stone.transform.parent = gameObject.transform;
				}
			}
		}
		//Deplacer ce message pour afficher l'info
		Debug.Log ("Dalles content " + transform.position.x + " " + transform.position.z + "{Nourriture: "+ quantity[0]+"; Linemate: "+ quantity[1]+"; Deraumere: "+ quantity[2]+"; Sibur: "+ quantity[3]+"; Mendiane: "+ quantity[4]+"; Phiras: "+ quantity[5]+"; Thystame: "+ quantity[6]+";}");
	}

	void OnMouseDown () {
		string s = "bct "+ transform.position.x+" "+transform.position.z;
		Connection.con.writeSocket (s);
	}

	public void deleteStone()
	{
		int i = transform.childCount;
		int j = 0;
		Debug.Log ("delete count:" +i);
		while (j < i) {
			if (transform.GetChild (j) is Egg) {
				j++;
				continue;
			} else {
				GameObject.Destroy (transform.GetChild (j).gameObject);
				j++;
			}
		}
	}

	// Update is called once per frame
	void Update () {

	}
}
