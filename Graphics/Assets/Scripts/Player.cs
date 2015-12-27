using UnityEngine;
using System.Collections;

public class Player : MonoBehaviour {
	
	public GameObject infoPanel;
	public bool info = false;

	GameObject pan;

	string	playerName;
	int		posx = 0;
	int		posy = 0;
	int		level = 1;
	int		nourriture = 0;
	int		deraumere = 0;
	int		linemate = 0;
	int		mediane = 0;
	int		phiras = 0;
	int		sibur = 0;
	int		thysame = 0;
	Animator animator;

	public void StartLaying()
	{
		animator.SetBool ("laying", true);
	}

	public void StopLaying()
	{
		animator.SetBool ("laying", false);
	}

	void Start()
	{
		animator = GetComponent<Animator> ();
	}

	public void InitPos(int x, int z, int or)
	{
		float xOffset = 0f;
		float zOffset = 0f;

		if (or == 1)
			zOffset = 0.8f;
		else if (or == 2)
			xOffset = -0.8f;
		else if (or == 3)
			zOffset = -0.8f;
		else if (or == 4)
			xOffset = 0.8f;
		Vector3 pos = new Vector3 (x + xOffset, 0.1f, z + zOffset);

		transform.Rotate (Vector3.up, -90f * (or - 1));
		transform.position = pos;
		gameObject.SetActive (true);
	}

	public void Init(string s)
	{
		playerName = s;
		pan = Instantiate (infoPanel, infoPanel.transform.position, infoPanel.transform.rotation) as GameObject;
		pan.GetComponent<infoPanel>().setinfo( playerName, posx, posy, level, nourriture, deraumere, linemate, mediane, phiras, sibur, thysame);
	}

	void OnMouseDown () {
		// change the target of the LookAtTarget script to be this gameobject.
		if (info == false) {
			pan.SetActive (true);
			//Active PlayerCam
			CamManagement.cmgnt.PlayerCam.gameObject.SetActive(true);
			//Desactiv MapCam
			CamManagement.cmgnt.MapCam.gameObject.SetActive(false);
			//put PlayerCam in Player environment
			CamManagement.cmgnt.PlayerCam.transform.parent = gameObject.transform;
			//set position PlayerCam in Player environment
			Vector3 pos = transform.position;
			pos.y = 1.23f;
			pos -= 4 * transform.forward;
			CamManagement.cmgnt.PlayerCam.transform.position = pos;
			CamManagement.cmgnt.PlayerCam.transform.rotation = transform.rotation;
			info = true;
		} else {
			pan.SetActive (false);
			//Activ MapCam
			CamManagement.cmgnt.MapCam.gameObject.SetActive(true);
			//Desactive PlayerCam
			CamManagement.cmgnt.PlayerCam.gameObject.SetActive(false);
			info = false;
		}
	}

	float toMove = 0;
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


	// Update is called once per frame
	void Update () {
		if (toMove > 0f)
			Move ();
		else
			animator.SetBool ("walking", false);
		CheckBorders ();


		if(Input.GetKey(KeyCode.DownArrow)){
			transform.Translate(Vector3.back * Time.deltaTime);	
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

	}
}
