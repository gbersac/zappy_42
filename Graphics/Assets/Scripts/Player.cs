using UnityEngine;
using System.Collections;

public class Player : MonoBehaviour {
	
	public GameObject infoPanel;
	public bool info = false;

	public string	name = "lol"; //change var name to rm warning
	int		posx = 0;
	int		posy = 0;
	int		level = 1;
	int		nourriture = 2;
	int		deraumere = 0;
	int		linemate = 1;
	int		mediane = 3;
	int		phiras = 10;
	int		sibur = 1;
	int		thysame = 0;

	void Start()
	{
		this.enabled = false;
	}

	public void Init(string s)
	{
		name = s;
		//ppo just sends ko or segv atm
		//Connection.con.writeSocket ("ppo " + 1);
		this.enabled = true;//if pos OK
	}

	void OnMouseDown () {
		// change the target of the LookAtTarget script to be this gameobject.
		if (info == false) {
			infoPanel.GetComponent<infoPanel>().setinfo( name, posx, posy, level, nourriture, deraumere, linemate, mediane, phiras, sibur, thysame);
			infoPanel.SetActive (true);
			info = true;
		} else {
			infoPanel.SetActive (false);
			info = false;
		}
	}

	void	Avance() {
		transform.Translate(Vector3.forward * Time.deltaTime);
	}

	void	Droite() {
		transform.Translate(Vector3.right * Time.deltaTime);
	}
	
	void	Gauche() {
		transform.Translate(Vector3.left * Time.deltaTime);
	}

	// Update is called once per frame
	void Update () {
	
		if(Input.GetKey(KeyCode.DownArrow)){
			transform.Translate(Vector3.back * Time.deltaTime);	
		}
		if (Input.GetKey (KeyCode.Return)) {
			level = (level < 8) ? level++ : level;
			Debug.Log(level);
		}

	}
}
