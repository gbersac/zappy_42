using UnityEngine;
using System.Collections;

public class Egg : MonoBehaviour {

	public int 		eggNo;
	public int		playerNo;
	public int		posx;
	public int		posy;
	public string	teamName;
	public bool		ready = false;
	public MeshRenderer	msh;
	Color			eggColor;

	public void KillEgg()
	{
		EventsManager.em.eggs.Remove (this);
		Destroy (this.gameObject);
	}

	void EggReady()
	{		
		ready = true;
		eggColor.a = 1.0f;
		msh.material.color = eggColor;

		Player p = EventsManager.em.GetIdlePlayer (posx, posy, teamName);
		if (p != null) {
			p.StopIdle();
			DestroyEgg();
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
		Invoke ("KillEgg", 1);
	}

	public void SetDestroyEgg()
	{
		Invoke ("DestroyEgg", 1.0f);
	}

	public void Init(int eggno, int playerno, string team, int x, int y, Color col)
	{
		msh = GetComponentInChildren <MeshRenderer> ();
		msh.enabled = false;
		eggNo = eggno;
		playerNo = playerno;
		teamName = team;
		posx = x;
		posy = y;
		eggColor = col;
		eggColor.a = 0.5f;
		msh.material.color = col;
	}
}
