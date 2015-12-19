using UnityEngine;
using System.Collections;

public class Player : MonoBehaviour {
	
	public GameObject infoPanel;
	public bool info = false;

	GameObject pan;

	string	name;
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

	void Start()
	{
		//this.enabled = false;
	}

	public void Init(string s)
	{
		name = s;
		pan = Instantiate (infoPanel, infoPanel.transform.position, infoPanel.transform.rotation) as GameObject;
		pan.GetComponent<infoPanel>().setinfo( name, posx, posy, level, nourriture, deraumere, linemate, mediane, phiras, sibur, thysame);
		//ppo just sends ko or segv atm
		//Connection.con.writeSocket ("ppo " + 1);
		//this.enabled = true;//if pos OK
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
			CamManagement.cmgnt.PlayerCam.transform.localPosition = new Vector3(0f, 1.23f, -5.16f);
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

	void	Avance() {
		Debug.Log ("avance");
		transform.Translate(Vector3.forward * Time.deltaTime);
	}

	void	Droite() {
		Debug.Log ("droite");
		transform.Translate(Vector3.right * Time.deltaTime);
	}
	
	void	Gauche() {
		Debug.Log ("gauche");
		transform.Translate(Vector3.left * Time.deltaTime);
	}

	// Update is called once per frame
	void Update () {
	
		if(Input.GetKey(KeyCode.DownArrow)){
			transform.Translate(Vector3.back * Time.deltaTime);	
		}
		if(Input.GetKey(KeyCode.UpArrow)){
			Avance();
		}
		if(Input.GetKey(KeyCode.RightArrow)){
			Droite();
		}
		if(Input.GetKey(KeyCode.LeftArrow)){
			Gauche();
		}
		if (Input.GetKey (KeyCode.Return)) {
			level = (level < 8) ? level++ : level;
			Debug.Log(level);
		}

	}
}
