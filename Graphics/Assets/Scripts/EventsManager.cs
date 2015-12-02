using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class EventsManager : MonoBehaviour {
	
	private Dictionary<string, System.Action<string>> functions;
	private string fake = "msz 20 20\n";
	public GameObject ground;
	// Use this for initialization

	string	ReturnArgs(string s)
	{
		return s;
	}

	void	ft_mapsize(string s)
	{
		GroundGenerator map;
		int x, y, index;
		
		index = s.IndexOf (' ');
		x = int.Parse (s.Substring(0, index));
		y = int.Parse (s.Substring(index + 1, s.Length - index - 1));
		map = ground.GetComponent<GroundGenerator> ();
		Debug.Log ("Mapsize X=" + x + " Y=" + y);
		map.width = x;
		map.height = y;
		map.Initialize ();
		//start async recv
	}
	
	public void Parse(string line)
	{
		line = line.Trim ();
		int index = line.IndexOf(' ');
		string f_key = line.Split(' ')[0];
		string f_arg = line.Substring(index + 1, line.Length - index - 1);
		Debug.Log("key [" + f_key + "]");
		foreach (var fun in functions)
		{
			if (fun.Key == f_key)
				fun.Value(f_arg);
		}
	}
	void Start () {
		functions = new Dictionary<string, System.Action<string>> ();
		functions.Add ("msz", ft_mapsize);
	}
	
	// Update is called once per frame
	void Update () {
		
		if (Input.GetKeyDown (KeyCode.Space)) {
			Debug.Log("Space");
			Parse(fake);
		}
	}
}