using UnityEngine;
using System.Collections;

public class CamManagement : MonoBehaviour {

	public Camera	MapCam;
	public Camera	PlayerCam;
	public int		CamNo = 0;

	static public CamManagement cmgnt;

	// Use this for initialization
	void Start () {
		cmgnt = this.GetComponent<CamManagement> ();
	}

	void MoveMainCam(KeyCode code)
	{
		Vector3 pos = MapCam.transform.position;
		switch (code) {
		case KeyCode.RightArrow:
			pos.x += 1;
			break;
		case KeyCode.LeftArrow:
			pos.x -= 1;
			break;
		case KeyCode.DownArrow:
			pos.z -= 1;
			break;
		case KeyCode.UpArrow:
			pos.z += 1;
			break;
		}
		MapCam.transform.position = pos;
	}

	void Update()
	{
		if (Input.GetKeyDown(KeyCode.RightArrow))
			MoveMainCam(KeyCode.RightArrow);
		if (Input.GetKeyDown(KeyCode.LeftArrow))
			MoveMainCam(KeyCode.LeftArrow);
		if (Input.GetKeyDown(KeyCode.DownArrow))
			MoveMainCam(KeyCode.DownArrow);
		if (Input.GetKeyDown(KeyCode.UpArrow))
			MoveMainCam(KeyCode.UpArrow);
	}
}
