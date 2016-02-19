﻿using UnityEngine;
using System.Collections;

public class Egg : MonoBehaviour {

	public int eggNo;
	public int playerNo;

	void KillEgg()
	{
		Destroy (this.gameObject);
	}

	void EggReady()
	{		
		MeshRenderer msh = GetComponentInChildren <MeshRenderer> ();
		Color gold = new Color (1f, 215f / 255f, 0f, msh.material.color.a);
		msh.material.color = gold;
	}

	public void SetEggReady()
	{
		Invoke ("EggReady", 1.0f);
	}

	void DestroyEgg()
	{
		MeshRenderer msh = GetComponentInChildren <MeshRenderer> ();
		msh.material.color = Color.black;
		EventsManager.em.eggs.Remove (this);
		Invoke ("KillEgg", 3);
	}

	public void SetDestroyEgg()
	{
		Invoke ("DestroyEgg", 1.0f);
	}

	public void HatchEgg()
	{
		Debug.Log ("IM HATCHING YO");
		//player is born so destroy egg ?
	}

	public void Init(int eggno, int playerno)
	{
		eggNo = eggno;
		playerNo = playerno;
	}

	void Start()
	{
		this.gameObject.GetComponentInChildren <MeshRenderer> ().enabled = false;
	}

}
