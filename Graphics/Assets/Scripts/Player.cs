using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class Player : MonoBehaviour {
	
//	public GameObject infoPanel;
	public bool			info = false;
	public int			playerNo;
	public bool			isAlive = false;
	public Color		teamColor = Color.white;

	GameObject			pan;

	float				toMove = 0;
	string				playerName;
	public int			posx = 0;
	public int			posy = 0;
	public string		teamName;
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
	List<int[]>		casters;//[0] = current ; [1] == needed

	public void SetStopCasting(bool success)
	{
		animQueue.Add ("stopCasting " + success);
	}

	//can it really fail ? if so do it even if not enought casters
	bool StopCasting(bool success)
	{
		if (casters [0] [0] < casters [0] [1])
			return false;
		animator.SetBool ("casting", false);
		if (success == true)
			level++;
		casters.RemoveAt (0);
		return true;
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

	public void SetCasting(int nbr)
	{
		int []cast = { 0, nbr };
		casters.Add(cast);
		animQueue.Add ("casting");
	}

	public void AddCaster()
	{
		casters [0] [0]++;
	}

	void StartCasting()
	{
		EventsManager.em.addActiveCaster(this.teamName);
		//broadcast castersCount++;
		animator.SetBool ("casting", true);
	}

	public void SetMoveOrTurn(int x, int z, int or)
	{
		animQueue.Add ("move " + x + " " + z + " " + or);
	}

	void MoveOrTurn(int x, int z, int or)
	{
		if (isAlive == false)
			return ;
		if (or != orientation)
		{
			if (or > orientation || (or == 1 && orientation == 4))
				Droite();
			else
				Gauche ();
			orientation = or;
		}
		if (x != posx || z != posy)
			Avance ();
	}

	//don't queue this one
	public void Die()
	{
		isAlive = false;
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

	public void SetStopLaying()
	{
		animQueue.Add ("removeLaying");
	}

	void StopLaying()
	{
		animator.SetBool ("laying", false);
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
				zOffset = 0.3f;
			else if (or == 2)
				xOffset = -0.3f;
			else if (or == 3)
				zOffset = -0.3f;
			else if (or == 4)
				xOffset = 0.3f;
		}
		Vector3 pos = new Vector3 (x + xOffset, 0.1f, z + zOffset);
		transform.Rotate (Vector3.up, -90f * (or - 1));
		transform.position = pos;

	}

	public void Initnew(int id, int pos_x, int pos_y, int direction, int level, string team, bool borning)
	{
		this.playerNo = id;
		this.playerName = team+id;
		this.teamName = team;
		this.level = level;
	//	pan = Instantiate (infoPanel, infoPanel.transform.position, infoPanel.transform.rotation) as GameObject;

		animQueue = new List<string> ();
		casters = new List<int[]>();
		pan = GameObject.Find ("Panels/infoPanel");
		animator = GetComponent<Animator> ();
		//pan.GetComponent<infoPanel>().setinfo( playerName, pos_x, pos_y, level, nourriture, deraumere, linemate, mendiane, phiras, sibur, thystame);
		InitPos (pos_x, pos_y, direction, borning);
		this.isAlive = true;
		gameObject.SetActive (true);
		if (borning == true)
			animator.Play ("Raising");
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

	void CheckAnimsQueue()
	{
		bool playing = this.animator.GetCurrentAnimatorStateInfo (0).IsTag ("idle");
		Debug.Log ("Anim playing ? " + playing + " Qlen = " + animQueue.Count);
		if (playing == true)
			return;
		if (animQueue.Count == 0)
			return;
		string []args = animQueue[0].Split(' ');
		string anim = args [0];
		bool toRemove = true;
		switch (anim) {
		case "move":
			MoveOrTurn(int.Parse(args[1]), int.Parse(args[2]), int.Parse(args[3]));
			break;
		case "casting":
			StartCasting();
			break;
		case "stopCasting":
			toRemove = StopCasting(bool.Parse(args[1]));//returns bool ?
			break;
		case "startLaying":
			StartLaying();
			break;
		case "stopLaying":
			StopLaying();
			break;
		case "pickRess":
			PickRess(int.Parse(args[1]));
			break;
		case "throwRess":
			ThrowRess(int.Parse(args[1]));
			break;
		default:
			Debug.Log("Unknown switch case : " + anim);
			break;
		}
		if (toRemove)
			animQueue.RemoveAt (0);
	}

	void Update () {
		if (!isAlive)
			return;
		CheckAnimsQueue ();
		if (toMove > 0f)
			Move ();
		else
			animator.SetBool ("walking", false);
		CheckBorders ();
		posx = (int)(transform.position.x);
		posy = (int)(transform.position.z);


		//DEBUG
		if (Input.GetKeyDown (KeyCode.M)) {
			System.Collections.Generic.List<Color> lCol = new System.Collections.Generic.List<Color>();
			lCol.Add(Color.red);
			lCol.Add(Color.blue);
			lCol.Add(Color.green);
			lCol.Add(Color.black);
			lCol.Add(Color.white);//this seems to be default
			lCol.Add(Color.yellow);
			lCol.Add(Color.cyan);
			lCol.Add(Color.magenta);
			int i = UnityEngine.Random.Range(0, lCol.Count);
			GetComponentInChildren<Renderer>().material.color = lCol[i];
			Debug.Log(lCol[i]);
		}
		if(Input.GetKeyDown(KeyCode.UpArrow)){
			Avance();
		}
		if(Input.GetKeyDown(KeyCode.RightArrow)){
			Droite();
		}
		if(Input.GetKeyDown(KeyCode.LeftArrow)){
			Gauche();
		}
		if (Input.GetKey (KeyCode.Return)) {
			level = (level < 8) ? level++ : level;
			Debug.Log(level);
		}
		//END
	}
}
