using UnityEngine;
using UnityEngine.UI;
using System.Collections;
using System.Collections.Generic;

public class EventsManager : MonoBehaviour {
	
	private Dictionary<string, System.Action<string>> functions;
    private string fake = "msz 20 20\n";
    private string fake2 = "msg Hello ca va ? Bonjouuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuur\n";
    private string fake3 = "suc\n";
    private string fake4 = "sbp\n";
    private string fake5 = "sgt 4\n";
	public GameObject ground;
    public MessagesBox msgBox;
	// Use this for initialization

	string	ReturnArgs(string s)
	{
		return s;
	}

  
    void    recMessage(string s)
    {
        msgBox.ServerMessage(s, Color.grey);
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

    void timeUnit(string s)
    {
        msgBox.ServerMessage("Server time unit: " + s, Color.green);
    }

    void badArgs(string s)
    {
        msgBox.ServerMessage("Bad arguments received by server.", Color.red);
    }

	void    unknownCommand(string s)
    {
        msgBox.ServerMessage("Unknown command received by server.", Color.red);
    }

	public void Parse(string line)
	{
		line = line.Trim ();
		int index = line.IndexOf(' ');
		string f_key = line.Split(' ')[0];
		string f_arg = line.Substring(index + 1, line.Length - index - 1);
		Debug.Log("key [" + f_key + "]");
        if (functions.ContainsKey(f_key))
            functions[f_key](f_arg);
        else
            Debug.Log("Unknown command " + f_key);
	}

	void Start () {
        msgBox = Instantiate<MessagesBox>(msgBox);
		functions = new Dictionary<string, System.Action<string>> ();
        functions.Add("msg", recMessage);
        functions.Add("msz", ft_mapsize);
        functions.Add("suc", unknownCommand);
        functions.Add("sbp", badArgs);
        functions.Add("sgt", timeUnit);
	}
	
	// Update is called once per frame
	void Update () {
		
		if (Input.GetKeyDown (KeyCode.Space)) {
			Parse(fake);
		}
        if (Input.GetKeyDown(KeyCode.M))
        {
            Parse(fake2);
        }
        if (Input.GetKeyDown(KeyCode.N))
        {
            Parse(fake3);
        }
        if (Input.GetKeyDown(KeyCode.B))
        {
            Parse(fake4);
        }
        if (Input.GetKeyDown(KeyCode.V))
        {
            Parse(fake5);
        }
	}
}