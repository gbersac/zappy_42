using UnityEngine;
using UnityEngine.UI;
using System.Collections;
using System;
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

	int i = 0;

	static public EventsManager em;

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
		map.width = x;
		map.height = y;
		map.Initialize ();
	//	Connection.con.writeSocket ("mct");
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
		// delete map.dalles[x[y];
		map.dalles[x,y].GetComponent<Content>().createStone("bct " + s);
		return;
	}

	void	ft_team_name(string s)
	{
		return;
	}
	
	void	ft_new_player(string s)
	{
		return;
	}
	
	void	ft_player_position(string s)
	{
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
		return;
	}
	
	void	ft_egg_born(string s)
	{
		return;
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
        if (functions.ContainsKey(f_key))
            functions[f_key](f_arg);
        else
            Debug.Log("Unknown command " + f_key);
	}

	void Start () {
		em = this.GetComponent<EventsManager> ();
		msgBox = Instantiate<MessagesBox>(msgBox);
		functions = new Dictionary<string, System.Action<string>> ();
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