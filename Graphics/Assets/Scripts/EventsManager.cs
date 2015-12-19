using UnityEngine;
using UnityEngine.UI;
using System.Collections;
using System;
using System.Collections.Generic;

public class EventsManager : MonoBehaviour {
	
	private Dictionary<string, System.Action<string>> functions;
	public GameObject ground;
	public GameObject speedController;
    public MessagesBox msgBox;
	public Player playerPrefab;

	static public EventsManager em;
	//keep static map ?


    void    recMessage(string s)
    {
        msgBox.ServerMessage(s, Color.white);
    }

	void	ft_mapsize(string s)
	{
		GroundGenerator map;
		int x, y, index;
		
		index = s.IndexOf (' ');
		x = int.Parse (s.Substring(0, index));
		y = int.Parse (s.Substring(index + 1, s.Length - index - 1));
		map = ground.GetComponent<GroundGenerator> ();
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
		GroundGenerator map;
		map = ground.GetComponent<GroundGenerator> ();

		string [] split = s.Split (' ');
		x = int.Parse(split [0]);
		y = int.Parse(split [1]);
//		Debug.Log ("more stone " + s);
		map.dalles [x, y].GetComponent<Content> ().deleteStone ();
		map.dalles[x,y].GetComponent<Content>().createStone("bct " + s);
		return;
	}

	Dictionary<string, Player> players = new Dictionary<string, Player>();

	void	ft_team_name(string s)
	{
		if (players.ContainsKey (s)) {
			Debug.Log ("TBD Player already exists: " + s);
			return;
		}
		Player newPlayer = Instantiate<Player> (playerPrefab);
		newPlayer.Init (s);
		players.Add (s, newPlayer);
		newPlayer.transform.parent = GameObject.Find("World").transform;

		//create player s in list or dictionary ?
		//ppo = pos du joueur
		//plv level et pin inventaire ou juste au clic ?

		return;
	}
	
	void	ft_new_player(string s)
	{
		return;
	}
	
	void	ft_player_position(string s)
	{
		Debug.Log ("POS: " + s);
		return;
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
	
	void	ft_player_ponds(string s)
	{
		return;
	}
	
	void	ft_player_vomit(string s)
	{
		return;
	}
	
	void	ft_player_take(string s)
	{
		return;
	}
	
	void	ft_player_died(string s)
	{
		return;
	}
	
	void	ft_new_egg_pos(string s)
	{
		int eggNo;
		int playerNo;
		int x;
		int y;
		GroundGenerator map;//mb init at msz and keep
		map = ground.GetComponent<GroundGenerator> ();
		
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
		map.dalles [x, y].GetComponent<Content> ().layEgg (eggNo, playerNo);
	}
	
	void	ft_egg_born(string s)
	{

		int eggNo;
		GroundGenerator map;
		//mb init at msz and keep
		map = ground.GetComponent<GroundGenerator> ();

		try
		{
			eggNo = int.Parse(s);
		}
		catch
		{
			Debug.Log("Error: bad parameters in ft_egg_born.");
			return ;
		}
		//map.availableEggs
		//need an objet with all eggs
		Debug.Log("Eggno " + s + " is hatching.");
	}
	
	void	ft_egg_died(string s)
	{
		return;
	}
	
	void	ft_end(string s)
	{
		return;
	}
    void timeUnit(string s)
    {
		
		msgBox.ServerMessage("Server time unit: " + s, Color.green);
		TimeManagement tpanel = speedController.GetComponent<TimeManagement> ();

		string [] split = s.Split (' ');		
		int t = int.Parse(split [0]);

		tpanel.setTime (t);
	//	Debug.Log ("ici");
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
        if (functions.ContainsKey (f_key))
			functions [f_key] (f_arg);
		else if (f_key != "newturn")
			recMessage (line);

            //Debug.Log("Unknown command " + f_key);
	}

	void ft_bienvenue(string s)
	{
		Debug.Log ("merci");
		Connection.con.writeSocket ("GRAPHIC");
		System.Threading.Thread.Sleep (50);
		Connection.con.InitWorld();
	}

	void Start () {
		em = this.GetComponent<EventsManager> ();
		msgBox = Instantiate<MessagesBox>(msgBox);
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
		functions.Add("pfk", ft_player_ponds);
		functions.Add("pdr", ft_player_vomit);
		functions.Add("pgt", ft_player_take);
		functions.Add("pdi", ft_player_died);
		functions.Add("enw", ft_new_egg_pos);
		functions.Add("eht", ft_egg_born);
		functions.Add("edi", ft_egg_died);
		functions.Add("sgt", timeUnit);
		functions.Add("seg", ft_end);
		functions.Add("smg", recMessage);
		functions.Add("suc", unknownCommand);
		functions.Add("sbp", badArgs);

	}
}