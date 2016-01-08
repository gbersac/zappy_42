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
}
