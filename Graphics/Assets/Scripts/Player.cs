using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class Player : MonoBehaviour {
	
	public bool			info = false;
	public int			playerNo;
	public bool			isAlive = false;
	public Color		teamColor = Color.white;
	public int			posx = 0;
	public int			posy = 0;
	public string		teamName;

	float				toMove = 0;
	string				playerName;
	int					orientation = 1;
	int					level = 1;
	int					nourriture = 0;
	int					deraumere = 0;
	int					linemate = 0;
	int					mendiane = 0;
	int					phiras = 0;
	int					sibur = 0;
	int					thystame = 0;
	Animator			animator;
	List<string>		animQueue;
	bool				hasMoved = false;
	int					targetX;
	int					targetY;
	int					targetO;

	public void SetStopCasting(bool success)
	{
		animator.SetBool ("casting", false);
		if (success == true)
			level++;
		Debug.Log("<color=green>Casting done for " + playerNo + " in x" + posx + " y" + posy + " lvl=" + level + "</color>");
	}

	public void SetColor(Color col)
	{
		teamColor = col;
		GetComponentInChildren<Renderer> ().material.color = col;
	}

	public void SetStuff(string []stuff)
	{
		nourriture = int.Parse (stuff [3]);
		linemate = int.Parse (stuff [4]);
		deraumere = int.Parse (stuff [5]);
		sibur = int.Parse (stuff [6]);
		mendiane = int.Parse (stuff [7]);
		phiras = int.Parse (stuff [8]);
		thystame = int.Parse (stuff [9]);
	}

	public void SetCasting()
	{
		animQueue.Add ("casting");
	}

	void StartCasting()
	{
		animator.SetBool ("casting", true);
		EventsManager.em.map.dalles [posx, posy].GetComponent<Content> ().AddCaster (this);
	}

	public void SetMoveOrTurn(int x, int z, int or)
	{
		animQueue.Add ("move " + x + " " + z + " " + or);
	}

	void MoveOrTurn(int x, int z, int or)
	{
		if (isAlive == false)
			return ;

		if (or > 4 || or < 1)
			Debug.Log ("<color=red>Bad orientation ! " + or + "</color>");

		hasMoved = true;
		targetX = x;
		targetY = z;
		targetO = or;
		if (or == orientation && x == posx && z == posy) {
			hasMoved = false;
			return ;
		}
		if (or != orientation) {
			float y = 0f;
			float w = 0f;
			if (targetO == 2 || targetO == 4)
				y = 0.7f;
			else if (targetO == 3)
				y = 1f;
			if (targetO == 1)
				w = 1f;
			else if (targetO == 2)
				w = 0.7f;
			else if (targetO == 4)
				w = -0.7f;
			Quaternion rot = new Quaternion(0, y, 0, w);
			transform.rotation = rot;
//			if (or > orientation || (or == 1 && orientation == 4))
//				Droite ();
//			else
//				Gauche ();
			orientation = or;
		}
		if (x != posx || z != posy) {
			Avance ();
		}
		//can we move for more than one case at a time ? if so tomove should be fixed
	}

	public void SetDie()
	{
		animQueue.Add ("die");
	}

	//don't queue this one
	public void ForceDie()
	{
		isAlive = false;
		animator.SetBool ("casting", false);
		animator.SetTrigger ("die");
	}

	//don't queue this one but set dead too ?
	public void Celebrate()
	{
		isAlive = false;
		animator.SetBool ("celebration", true);
	}

	public void SetPickRess(int ressNo)
	{
		animQueue.Add ("pickRess " + ressNo);
	}

	void PickRess(int ressNo)
	{
		animator.SetTrigger ("picking");
		switch (ressNo)
		{
		case 0:
			nourriture++;
			break ;
		case 1:
			linemate++;
			break;
		case 2:
			deraumere++;
			break;
		case 3:
			sibur++;
			break;
		case 4:
			mendiane++;
			break;
		case 5:
			phiras++;
			break;
		case 6:
			thystame++;
			break;
		default:
			Debug.Log("Error: unknown ressource " + ressNo);
			break;
		}
		
	}

	public void SetThrowRess(int ressNo)
	{
		animQueue.Add ("throwing " + ressNo);
	}

	void ThrowRess(int ressNo)
	{
		animator.SetTrigger ("throwing");
		switch (ressNo)
		{
		case 0:
			nourriture--;
			break ;
		case 1:
			linemate--;
			break;
		case 2:
			deraumere--;
			break;
		case 3:
			sibur--;
			break;
		case 4:
			mendiane--;
			break;
		case 5:
			phiras--;
			break;
		case 6:
			thystame--;
			break;
		default:
			Debug.Log("Error: unknown ressource " + ressNo);
			break;
		}

	}

	public void SetStartLaying()
	{
		animQueue.Add ("startLaying");
	}

	void StartLaying()
	{
		animator.SetBool ("laying", true);
	}

	public void SetStopLaying(int eggNo)
	{
		animQueue.Add ("stopLaying " + eggNo);
	}

	void StopLaying(int eggNo)
	{
		animator.SetBool ("laying", false);
		Egg egg = EventsManager.em.eggs.Find (x => x.eggNo == eggNo);
		egg.gameObject.GetComponentInChildren <MeshRenderer> ().enabled = true;
	}

	public void SetLevel(int lvl)
	{
		this.level = lvl;
	}

	public void InitPos(int x, int z, int or, bool borning)
	{
		float xOffset = 0f;
		float zOffset = 0f;

		if (borning == true) {
			if (or == 1)
				zOffset = 0.81f;
			else if (or == 2)
				xOffset = 0.81f;
			else if (or == 3)
				zOffset = -0.81f;
			else if (or == 4)
				xOffset = -0.81f;
		}
		Vector3 pos = new Vector3 (x + xOffset, 0.1f, z + zOffset);
		transform.Rotate (Vector3.up, 90f * (or - 1));
		transform.position = pos;
		posx = x;
		posy = z;
		orientation = or;
		hasMoved = true;
		targetO = or;
		targetX = x;
		targetY = z;
	}

	public void Initnew(int id, int pos_x, int pos_y, int direction, int level, string team, bool borning)
	{
		this.playerNo = id;
		this.playerName = team+id;
		this.teamName = team;
		this.level = level;

		animQueue = new List<string> ();
		animator = GetComponent<Animator> ();
		InitPos (pos_x, pos_y, direction, borning);
		this.isAlive = true;
		gameObject.SetActive (true);
		if (borning == true)
			animator.Play ("Raising");
		else {
			animator.Play ("Waiting");
		}
	}

	void OnMouseDown () {
		// change the target of the LookAtTarget script to be this gameobject.
		if (CamManagement.cmgnt.CamNo != playerNo) {
			EventsManager.em.playerPanels.SetActive (true);
		//	pan.SetActive (true);
			EventsManager.em.playerPanels.GetComponent<infoPanel>().setinfo( playerName, posx, posy, level, nourriture, deraumere, linemate, mendiane, phiras, sibur, thystame);

			CamManagement.cmgnt.PlayerCam.gameObject.SetActive(true);					//Active PlayerCam
			CamManagement.cmgnt.MapCam.rect = new Rect(0f, 0f, 0.15f, 0.15f);			//Minimapise MapCam

			CamManagement.cmgnt.PlayerCam.transform.parent = gameObject.transform;		//put PlayerCam in Player environment
			Vector3 pos = transform.position;											//set position PlayerCam in Player environment
			pos.y = 1.23f;
			pos -= 4 * transform.forward;
			CamManagement.cmgnt.PlayerCam.transform.position = pos;
			CamManagement.cmgnt.PlayerCam.transform.rotation = transform.rotation;

			CamManagement.cmgnt.CamNo = playerNo;
		} else {
			EventsManager.em.playerPanels.SetActive (false);
			CamManagement.cmgnt.MapCam.rect = new Rect(0f, 0f, 1f, 1f);					//FullScreenise MapCam
			CamManagement.cmgnt.PlayerCam.gameObject.SetActive(false);					//Desactive PlayerCam
			CamManagement.cmgnt.CamNo = 0;
		}
	}

	void	Avance() {
		animator.SetBool ("walking", true);
		toMove += 1f;
	}

	void	Droite() {
		animator.SetTrigger ("rturn");
		transform.Rotate (new Vector3 (0, 14.69f, 0));
	}
	
	void	Gauche() {
		animator.SetTrigger ("lturn");
		transform.Rotate (new Vector3 (0, -20.4f, 0));
	}

	void	Move()
	{
		Vector3 diff = Vector3.forward * Time.deltaTime;
		transform.Translate (diff);
		toMove -= (diff.x + diff.z);
	}

	void CheckBorders()
	{
		Vector3 currentPos = transform.position;
		int width = EventsManager.em.map.width;
		int height = EventsManager.em.map.height;

		if (currentPos.x < -0.5f)
			currentPos.x += width;
		else if (currentPos.x > width - 0.5f)
			currentPos.x -= width;
		else if (currentPos.z < -0.5f)
			currentPos.z += height;
		else if (currentPos.z > height - 0.5f)
			currentPos.z -= height;
		else
			return;
		transform.position = currentPos;

	}

	void ForcePosition()
	{
		Vector3 pos;
//
		pos = transform.position;
		pos.x = targetX;
		pos.z = targetY;
		posx = targetX;
		posy = targetY;
		orientation = targetO;
		transform.position = pos;
		hasMoved = false;
	}

	void EggReady(int eggNo)
	{
		Egg egg = EventsManager.em.eggs.Find (x => x.eggNo == eggNo);
		egg.SetEggReady ();
	}

	void EggDie(int eggNo)
	{
		Egg egg = EventsManager.em.eggs.Find (x => x.eggNo == eggNo);
		egg.SetDestroyEgg ();
	}

	public void SetEggDie(int eggNo)
	{
		animQueue.Add ("eggdie " + eggNo);
	}

	public void SetEggReady(int eggNo)
	{
		animQueue.Add ("eggready " + eggNo);
	}

	void CheckAnimsQueue()
	{
		bool isIdle = false;
		if (toMove <= 0f && this.animator.GetCurrentAnimatorStateInfo (0).normalizedTime > 1
		    && !this.animator.IsInTransition (0) && this.animator.GetCurrentAnimatorStateInfo (0).IsTag ("idle")
		    && this.animator.GetCurrentAnimatorStateInfo (0).IsName("Default")) {
			isIdle = true;
		}
		bool isCasting = this.animator.GetCurrentAnimatorStateInfo (0).IsTag ("cast");
		bool isLaying = this.animator.GetCurrentAnimatorStateInfo (0).IsTag ("lay");

		// DEBUG
//		Debug.Log ("Anim idle ? " + isIdle + " cast ? " + isCasting + " Qlen = " + animQueue.Count);
//		string db = null;
//		foreach (var q in animQueue) {
//			db += q + " | ";
//		}
//		if (db != null)
//			Debug.Log ("Qlist: " + db);
		//END

		if (isCasting == true && animQueue [0].Split (' ') [0] == "die") {
			ForceDie ();
			return;
		}
		else if (isLaying == true && animQueue [0].Split (' ') [0] == "stopLaying") {
			StopLaying(int.Parse(animQueue [0].Split (' ') [1]));
			return;
		}
		if (isIdle == false)
			return;
		else if (hasMoved == true)
			ForcePosition ();
		if (animQueue.Count == 0)
			return;
		string []args = animQueue[0].Split(' ');
		string anim = args [0];
		if (isIdle == true) {
			switch (anim) {
			case "move":
				MoveOrTurn (int.Parse (args [1]), int.Parse (args [2]), int.Parse (args [3]));
				break;
			case "die":
				ForceDie();
				return;
			case "eggdie":
				EggDie (int.Parse (args [1]));
				break;
			case "eggready":
				EggReady(int.Parse(animQueue [0].Split (' ') [1]));
				break;
			case "casting":
				StartCasting ();
				break;
			case "startLaying":
				StartLaying ();
				break;
			case "stopLaying":
				StopLaying (int.Parse (args [1]));
				break;
			case "pickRess":
				PickRess (int.Parse (args [1]));
				break;
			case "throwRess":
				ThrowRess (int.Parse (args [1]));
				break;
			default:
				Debug.Log ("Unknown switch case : " + anim);
				break;
			}
		}
		animQueue.RemoveAt (0);
	}

	void Update () {
		if (!isAlive)
			return;
		if (toMove > 0f)
			Move ();
		else
			animator.SetBool ("walking", false);
		CheckAnimsQueue ();
		CheckBorders ();
	}
}
