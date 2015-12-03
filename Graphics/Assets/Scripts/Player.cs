using UnityEngine;
using System.Collections;

public class Player : MonoBehaviour {
	
	public GameObject infoPanel;
	public bool info = false;

	public string	name = "lol";
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


	// Use this for initialization
	void Start () {
	
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

	// Update is called once per frame
	void Update () {
	
		if(Input.GetKey(KeyCode.LeftArrow)){
			transform.Translate(Vector3.left * Time.deltaTime);
		}
		if(Input.GetKey(KeyCode.RightArrow)){
			transform.Translate(Vector3.right * Time.deltaTime);
		}
		if(Input.GetKey(KeyCode.UpArrow)){
			transform.Translate(Vector3.forward * Time.deltaTime);
		}
		if(Input.GetKey(KeyCode.DownArrow)){
			transform.Translate(Vector3.back * Time.deltaTime);	
		}
		if (Input.GetKey (KeyCode.Return)) {
			level = (level < 8) ? level++ : level;
			Debug.Log(level);
		}

	}
}
