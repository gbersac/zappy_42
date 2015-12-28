using UnityEngine;
using System.Collections;

public class Egg : MonoBehaviour {

	public int eggNo;
	public int playerNo;

	void KillEgg()
	{
		Destroy (this.gameObject);
	}

	public void DestroyEgg()
	{
		MeshRenderer msh = GetComponentInChildren <MeshRenderer> ();
		msh.material.color = Color.black;
		Invoke ("KillEgg", 3);
	}

	public void HatchEgg()
	{
		Debug.Log ("IM HATCHING YO");
	}

	public void Init(int eggno, int playerno)
	{
		eggNo = eggno;
		playerNo = playerno;
	}
	
}
