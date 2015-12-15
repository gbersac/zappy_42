using UnityEngine;
using System.Collections;

public class Egg : MonoBehaviour {
	private int eggNo;
	private int playerNo;

	public void HatchEgg()
	{
		Debug.Log ("IM HATCHING YO");
	}

	public void Init(int eggno, int playerno)
	{
		eggNo = eggno;
		playerNo = playerno;
		//prob change color, mb get a ref to parent player
	}
}
