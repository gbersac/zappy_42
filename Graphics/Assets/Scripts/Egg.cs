using UnityEngine;
using System.Collections;

public class Egg : MonoBehaviour {

	public int 		eggNo;
	public int		playerNo;
	public int		posx;
	public int		posy;
	public string	teamName;
	public bool		ready = false;

	public void KillEgg()
	{
		EventsManager.em.eggs.Remove (this);
		Destroy (this.gameObject);
	}

	void EggReady()
	{		
		ready = true;
		MeshRenderer msh = GetComponentInChildren <MeshRenderer> ();
		Color gold = new Color (1f, 215f / 255f, 0f, msh.material.color.a);
		msh.material.color = gold;

		Player p = EventsManager.em.GetIdlePlayer (posx, posy, teamName);
		if (p != null) {
			p.StopIdle();
			KillEgg();
		}
		//if there is a player idle in pos posy with teamName, rm idle and rm this egg
	}

	public void SetEggReady()
	{
		EggReady ();
	}

	void DestroyEgg()
	{
		MeshRenderer msh = GetComponentInChildren <MeshRenderer> ();
		msh.material.color = Color.black;
		Invoke ("KillEgg", 3);
	}

	public void SetDestroyEgg()
	{
		Invoke ("DestroyEgg", 1.0f);
	}

	public void HatchEgg()
	{
		Debug.Log ("IM HATCHING YO THIS ISNT IMPLEMENTED");
	}

	public void Init(int eggno, int playerno, string team, int x, int y)
	{
		eggNo = eggno;
		playerNo = playerno;
		teamName = team;
		posx = x;
		posy = y;
	}

	void Start()
	{
		this.gameObject.GetComponentInChildren <MeshRenderer> ().enabled = false;
	}

}
