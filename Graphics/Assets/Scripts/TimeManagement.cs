using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class TimeManagement : MonoBehaviour {

	int					time = 1;

	public void setTime(int i)
	{
		Debug.Log ("reset time");
		time = i;
		transform.FindChild ("Panel/Speed").GetComponent<Text> ().text = time.ToString();
	}

	public void	IncreaseSpeed()
	{
		Debug.Log ("click +");
		int t = (time + 1 < 100) ? (time + 1) : 100;
		string s = "sst " + t.ToString ();
		Debug.Log (s);
		Connection.con.writeSocket(s);
	}
	
	public void	DecreaseSpeed()
	{
		Debug.Log ("click -");
		int t = (time - 1 > 1) ? (time - 1) : 1;
		string s = "sst " + t.ToString ();
		Debug.Log (s);
		Connection.con.writeSocket(s);
	}

}
