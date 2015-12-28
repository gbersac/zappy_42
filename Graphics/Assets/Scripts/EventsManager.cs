using UnityEngine;
using UnityEngine.UI;
using System.Collections;
using System;
using System.Collections.Generic;

public class EventsManager : MonoBehaviour {
	
	private Dictionary<string, System.Action<string>> functions;
	private List<Egg> eggs;
	public GameObject ground;
	public GameObject speedController;
    public MessagesBox msgBox;
	public Player playerPrefab;

	public GroundGenerator map;
	static public EventsManager em;

	Dictionary<int, Player> players = new Dictionary<int, Player>();
	int playerCounter = 0;

    void    recMessage(string s)
    {
        msgBox.ServerMessage(s, Color.white);
    }

	void	ft_mapsize(string s)
	{
		int x, y, index;
		
		index = s.IndexOf (' ');
		x = int.Parse (s.Substring(0, index));
		y = int.Parse (s.Substring(index + 1, s.Length - index - 1));
		if (map.width == x && map.height == y)
			return;
		map.width = x;
		map.height = y;
		map.Initialize ();
	}
	
	void	ft_content_map(string s)
	{
		int x;
		int y;

		string [] split = s.Split (' ');
		x = int.Parse(split [0]);
		y = int.Parse(split [1]);
		map.dalles [x, y].GetComponent<Content> ().deleteStone ();
		map.dalles[x,y].GetComponent<Content>().createStone("bct " + s);
		return;
	}


	void	ft_team_name(string s)
	{
		Player newPlayer = Instantiate<Player> (playerPrefab);
		newPlayer.Init (s);
		newPlayer.playerNo = playerCounter;
		players.Add (playerCounter, newPlayer);
		newPlayer.transform.parent = GameObject.Find("World").transform;

		//Connection.con.writeSocket ("ppo " + playerCounter);
		//call pos or given ?


		//faking
		int x = UnityEngine.Random.Range (0, 20);
		int z = UnityEngine.Random.Range (0, 10);
		int or = UnityEngine.Random.Range (1, 5);
		string str = playerCounter + " " + x + " " + z + " " + or;
		ft_player_position (str);
		//end

		playerCounter++;
	}
	
	void	ft_new_player(string s)
	{
		return;
	}
	
	void	ft_player_position(string s)
	{
		int playerNo = int.Parse (s.Split (' ') [0]);
		if (players.ContainsKey (playerNo))
		{
			int x = int.Parse (s.Split (' ') [1]);
			int z = int.Parse (s.Split (' ') [2]);
			int or = int.Parse (s.Split (' ') [3]);
			players[playerNo].MoveOrTurn(x, z, or);
		}
		else
			Debug.Log ("Player no " + playerNo + " not found.");
	}
	
	void	ft_player_level(string s)
	{
		return;
	}
	
	void	ft_player_inventory(string s)
	{
		return;
	}
	
	void	ft_player_expulse(string s)
	{
		return;
	}
	
	void	ft_player_brodcast(string s)
	{
		return;
	}
	
	void	ft_player_incantation(string s)
	{
		return;
	}
	
	void	ft_player_lays(string s)
	{
		int playerNo = int.Parse (s);

		players [playerNo].StartLaying ();
	}
	
	void	ft_player_vomit(string s)
	{
		try
		{
			int playerNo = int.Parse (s.Split (' ') [0]);
			int ressNo = int.Parse (s.Split (' ') [1]);
			players[playerNo].ThrowRess(ressNo);
		}
		catch
		{
			Debug.Log("Error: bad parameters in ft_player_vomit.");
			return ;
		}
	}
	
	void	ft_player_picks(string s)
	{
		try
		{
			int playerNo = int.Parse (s.Split (' ') [0]);
			int ressNo = int.Parse (s.Split (' ') [1]);
			players[playerNo].PickRess(ressNo);
			map.RemoveStone((int)(players[playerNo].transform.position.x), (int)(players[playerNo].transform.position.z), ressNo);
		}
		catch
		{
			Debug.Log("Error: bad parameters in ft_player_picks.");
			return ;
		}
	}
	
	void	ft_player_died(string s)
	{
		int playerNo;

		try
		{
			playerNo = int.Parse(s);
			players[playerNo].Die();
		}
		catch
		{
			Debug.Log("Error: bad parameters in ft_player_died. " + s);
		}
	}
	
	void	ft_new_egg_pos(string s)
	{
		int eggNo;
		int playerNo;
		int x;
		int y;
		
		string [] split = s.Split (' ');
		if (split.Length != 4) {
			Debug.Log("Error: bad paramaters number. Got " + s.Length + " expected 4. " + s);
			return ;
		}
		try
		{
			eggNo = int.Parse(split [0]);
			playerNo = int.Parse(split [1]);
			x = int.Parse(split [2]);
			y = int.Parse(split [3]);
		}
		catch
		{
			Debug.Log("Error: bad parameters in ft_new_egg_pos.");
			return ;
		}
		players [playerNo].StopLaying ();
		eggs.Add (map.dalles [x, y].GetComponent<Content> ().layEgg (eggNo, playerNo));
	}
	
	void	ft_egg_born(string s)
	{
		Egg egg;
		int eggNo;

		try
		{
			eggNo = int.Parse(s);
			egg = eggs.Find(x => x.eggNo == eggNo);
			egg.EggReady();
		}
		catch
		{
			Debug.Log("Error: bad parameters in ft_egg_born.");
			return ;
		}
	}
	void	ft_player_replaces_egg(string s)
	{
		ft_egg_died (s);
	}

	void	ft_egg_died(string s)
	{
		Egg egg;
		int eggNo;

		try
		{
			eggNo = int.Parse(s);
			egg = eggs.Find (x => x.eggNo == eggNo);
			eggs.Remove(egg);
			egg.DestroyEgg();
		}
		catch
		{
			Debug.Log("Error: bad parameters in ft_egg_died.");
		}
	}
	
	void	ft_end(string s)
	{
		Player winner;

		try
		{
			int playerNo = int.Parse(s);
			winner = players[playerNo];
			foreach (int pNo in players.Keys)
			{
				if (pNo != playerNo)
					players[pNo].Die();
			}
			winner.Celebrate();
		}
		catch
		{
			Debug.Log ("Error: bad parameters in ft_end.");
		}
		finally
		{
			Connection.con.closeSocket();
			//quit app or game over screen ?
		}
	}
    void timeUnit(string s)
    {
		
		TimeManagement tpanel = speedController.GetComponent<TimeManagement> ();

		string [] split = s.Split (' ');		
		int t = int.Parse(split [0]);

		tpanel.setTime (t);
		msgBox.ServerMessage("Server time unit: " + s, Color.green);
	//	Debug.Log ("ici");
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
        if (functions.ContainsKey (f_key))
			functions [f_key] (f_arg);
		else if (f_key != "newturn")
			recMessage (line);
	}

	void ft_bienvenue(string s)
	{
		Debug.Log ("merci");
        msgBox.ServerMessage(s, Color.white);
		Connection.con.writeSocket ("GRAPHIC");
		System.Threading.Thread.Sleep (50);
	}

	void Start () {
		em = this.GetComponent<EventsManager> ();
		msgBox = Instantiate<MessagesBox>(msgBox);
		map = ground.GetComponent<GroundGenerator> ();
		eggs = new List<Egg> ();
		functions = new Dictionary<string, System.Action<string>> ();
		functions.Add ("BIENVENUE", ft_bienvenue);
		functions.Add("msz", ft_mapsize);
		functions.Add("bct", ft_content_map);
		functions.Add("tna", ft_team_name);
		functions.Add("pnw", ft_new_player);
		functions.Add("ppo", ft_player_position);
		functions.Add("plv", ft_player_level);
		functions.Add("pin", ft_player_inventory);
		functions.Add("pex", ft_player_expulse);
		functions.Add("pbc", ft_player_brodcast);
		functions.Add("pic", ft_player_incantation);
		functions.Add("pfk", ft_player_lays);
		functions.Add("pdr", ft_player_vomit);
		functions.Add("pgt", ft_player_picks);
		functions.Add("pdi", ft_player_died);
		functions.Add("enw", ft_new_egg_pos);
		functions.Add("eht", ft_egg_born);
		functions.Add("edi", ft_egg_died);
		functions.Add("ebo", ft_player_replaces_egg);
		functions.Add("sgt", timeUnit);
		functions.Add("seg", ft_end);
		functions.Add("smg", recMessage);
		functions.Add("suc", unknownCommand);
		functions.Add("sbp", badArgs);

	}

	void Update()
	{
		if (Input.GetKeyDown (KeyCode.Z))
			Parse ("pfk 0");
		else if (Input.GetKeyDown (KeyCode.X))
			Parse ("enw 8 0 2 2");
		else if (Input.GetKeyDown (KeyCode.C))
			Parse ("pdr 0 1");
		else if (Input.GetKeyDown (KeyCode.V))
			Parse ("pgt 0 1");
		else if (Input.GetKeyDown (KeyCode.B))
			Parse ("seg 0");
		else if (Input.GetKeyDown (KeyCode.N))
			Parse ("eht 8");
		else if (Input.GetKeyDown (KeyCode.M))
			Parse ("edi 8");
	}
}