using UnityEngine;
using System.Collections;
using System;
using System.Collections.Generic;

struct castingInfo{
	public int						neededCastersNbr;
	public bool						success;
	public List<Player>				activeCasters;
	public bool						hasEnded;
};

public class Content : MonoBehaviour {
	
	public List<GameObject>		stones = new List<GameObject>();
	public List<int>			quantity = new List<int>();
	public Egg					eggPrefab;
	AudioSource			levelUpManager;
	bool						displayInfo = false;
	GameObject					pan;
	bool						initialized = false;
//	bool						castEnded = false;


	List<castingInfo>			castQueue;

	void triggerCastingEnd()
	{
		castingInfo info = castQueue [0];
		foreach (Player p in info.activeCasters)
			p.SetStopCasting(info.success);
		levelUpManager.Play ();
		castQueue.RemoveAt (0);
	}

	public void SetIncantionEnd(bool success)
	{
		int i = 0;
		castingInfo info;
		while (i < castQueue.Count  && castQueue[i].hasEnded == true)
			i++;
		Debug.Log ("SIE in " + transform.position.x + " " + transform.position.z + " on index " + i);
		info = castQueue [i];
		info.hasEnded = true;
		info.success = success;
		castQueue [i] = info;
//		castQueue [i].hasEnded = true;
//		castQueue [i].success = success;
	}

	public void SetupIncantation(int nbrPlayers)
	{
		castingInfo info;
		info.neededCastersNbr = nbrPlayers;
		info.activeCasters = new List<Player> ();
		info.success = false;
		info.hasEnded = false;
		castQueue.Add (info);
	}

	public void AddCaster(Player caster)
	{
		int i = 0;
		
		while (i < castQueue.Count && castQueue[i].activeCasters.Count >= castQueue[i].neededCastersNbr)
			i++;
		castQueue[i].activeCasters.Add (caster);

		Debug.Log ("Caster added in " + this.transform.position.x + " " + this.transform.position.z);
	}

	public Egg layEgg(int eggNo, int playerNo)
	{
		Vector3 spawnPosition;
		spawnPosition.x = transform.position.x;
		spawnPosition.z = transform.position.z;
		spawnPosition.y = transform.position.y;
		Egg newEgg = Instantiate(eggPrefab, spawnPosition, transform.rotation) as Egg;
		newEgg.Init (eggNo, playerNo);
		newEgg.transform.parent = gameObject.transform;

		return newEgg;
	}

	public void	createStone(string answer)
	{
		string [] split = answer.Split (' ');

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
			if (initialized == false) {
				pan = GameObject.Find ("Panels/dalleInfoPanel");
				initialized = true;
			}
			if (displayInfo == true) {
				pan.GetComponent<dallesInfoPanel> ().setinfo (transform.position.x, transform.position.z,
				                                              quantity[0], quantity[1], quantity[2], quantity[3], quantity[4], quantity[5], quantity[6]);
				Invoke ("hidePanel", 2);
			}
		}
	}
	
	public void deleteStone()
	{
		int i = transform.childCount;
		int j = 0;
		while (j < i) {
			Transform child = transform.GetChild(j);
			if (child.tag != "Stone") {
				j++;
				continue;
			} else {
				GameObject.Destroy (child.gameObject);
				j++;
			}
		}
	}

	void OnMouseDown () {
		if (displayInfo == false) {
			displayInfo = true;
		}
		pan.GetComponent<dallesInfoPanel> ().setinfo (transform.position.x, transform.position.z,
		                                              quantity[0], quantity[1], quantity[2], quantity[3], quantity[4], quantity[5], quantity[6]);
		Invoke ("hidePanel", 2);
	}

	void hidePanel(){
		displayInfo = false;
	}

	void Update()
	{
		if (castQueue.Count > 0 && castQueue [0].hasEnded == true && castQueue [0].activeCasters.Count >= castQueue [0].neededCastersNbr)
			triggerCastingEnd ();
		else if (castQueue.Count > 0)
			Debug.Log ("In " + transform.position.x + " " + transform.position.z + " " + castQueue[0].hasEnded  + " " + castQueue [0].activeCasters.Count + "/" + castQueue [0].neededCastersNbr);
	}

	void Start()
	{
		castQueue = new List<castingInfo> ();
		this.levelUpManager = GetComponent<AudioSource> ();
	}
}
