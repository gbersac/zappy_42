﻿using UnityEngine;
using UnityEngine.UI;
using System.Collections;
using System;
using System.Collections.Generic;

public class EventsManager : MonoBehaviour {
	
	private Dictionary<string, System.Action<string>> functions;
	private List<Team> teams;
	public GameObject ground;
	public GameObject speedController;
	public GameObject dallesPanels;
	public GameObject playerPanels;
    public MessagesBox msgBox;
	public Player playerPrefab;
	public List<Egg> eggs;
	bool	gameover = false;
	bool	celebrationDone = false;
	public GroundGenerator map;
	static public EventsManager em;

	List<Player> players = new List<Player> ();
	static readonly string[] tags = {
		"<color=blue>",
		"<color=yellow>",
		"<color=red>"
	};

	enum	DebugLevel
	{
		Info,
		Warning,
		Error
	};

	void	debugMessage(DebugLevel lvl, string msg)
	{
		Debug.Log(tags[(int)lvl] + msg + "</color>");
	}

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
		map.scalecamera ();
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
		return ;
	}

	void	ft_team_name(string s)
	{
		Team newTeam = new Team ();

		newTeam.InitTeam (s, teams.Count);
		teams.Add (newTeam);
	}
	
	void	ft_new_player(string s)
	{
		Player newPlayer = Instantiate<Player> (playerPrefab);
		debugMessage (DebugLevel.Info, "new player " + s);
		string [] split = s.Split (' ');
		try
		{
			newPlayer.Initnew (int.Parse(split[0]), int.Parse(split[1]), int.Parse(split[2]), int.Parse (split [3]), int.Parse(split[4]), split[5], true, true);
			newPlayer.transform.parent = GameObject.Find("World").transform;
			players.Add(newPlayer);
			teams.Find(t => t.teamName == split[5]).AddPlayer(newPlayer);
		}
		catch{
			debugMessage(DebugLevel.Error, "Bad parameters in ft_new_player. " + s);
		}
	}
	
	void	ft_player_position(string s)
	{
		try
		{
			int playerNo = int.Parse (s.Split (' ') [0]);
			if (players.Exists (x => x.playerNo == playerNo)) {
				int x = int.Parse (s.Split (' ') [1]);
				int z = int.Parse (s.Split (' ') [2]);
				int or = int.Parse (s.Split (' ') [3]);
				players.Find (p => p.playerNo == playerNo).SetMoveOrTurn (x, z, or);
			} else {
				debugMessage(DebugLevel.Error, "Unknown player moving.");
			}
		}
		catch
		{
			debugMessage(DebugLevel.Error, "Error: bad parameters in ft_player_position. " + s);
		}
	}
	
	void	ft_player_level(string s)
	{
		try
		{
			int playerNo = int.Parse (s.Split (' ') [0]);
			int lvl = int.Parse (s.Split (' ') [1]);
			players.Find(p => p.playerNo == playerNo).SetLevel(lvl);
		}
		catch
		{
			debugMessage(DebugLevel.Error, "Error: bad parameters in ft_player_level. " + s);
		}
	}
	
	void	ft_player_inventory(string s)
	{
		try
		{
			string []ss = s.Split(' ');
			int playerNo = int.Parse(ss[0]);
			players.Find(p => p.playerNo == playerNo).SetStuff(ss);
		}
		catch
		{
			debugMessage(DebugLevel.Error, "Error: bad parameters in ft_player_inventory. " + s);
		}
	}
	
	void	ft_player_expulse(string s)
	{
		return;
	}
	
	void	ft_player_broadcast(string s)
	{
		msgBox.ServerMessage ("Player No: " + s, Color.cyan);
	}
	
	void	ft_player_end_incantation(string s)
	{
		try
		{
			int x = int.Parse (s.Split (' ') [0]);
			int y = int.Parse (s.Split (' ') [1]);
			bool success = (int.Parse(s.Split (' ') [2]) == 1) ? true : false;
			map.dalles [x, y].GetComponent<Content> ().SetIncantionEnd(success);
		}
		catch
		{
			debugMessage(DebugLevel.Error, "Error: bad parameters in ft_player_end_incantation. " + s);
		}
	}

	void	ft_player_incantation(string s)
	{
		int playerNo;
		string [] ss = s.Split (' ');
		try
		{
			int x = int.Parse(ss[0]);
			int y = int.Parse(ss[1]);
			int i = 3;
			int playersNbr = ss.Length - 3;

			map.dalles [x, y].GetComponent<Content> ().SetupIncantation(playersNbr);
			while (i < ss.Length)
			{
				playerNo = int.Parse(ss[i]);
				if (players.Exists(p => p.playerNo == playerNo))
					players.Find(p => p.playerNo == playerNo).SetCasting();
				else
					debugMessage(DebugLevel.Error, "ft_player_incantation: Player no " + playerNo + " not found.");
				i++;
			}
		}
		catch
		{
			debugMessage(DebugLevel.Error, "Error: bad parameters in ft_player_incantation. " + s);
		}
	}
	
	void	ft_player_lays(string s)
	{
		int playerNo = int.Parse (s);

		if (players.Exists(p => p.playerNo == playerNo))
		    players.Find(p => p.playerNo == playerNo).SetStartLaying();
		else
			debugMessage(DebugLevel.Error, "ft_player_lays: Player no " + playerNo + " not found.");
	}
	
	void	ft_player_vomit(string s)
	{
		try
		{
			int playerNo = int.Parse (s.Split (' ') [0]);
			int ressNo = int.Parse (s.Split (' ') [1]);
			players.Find(p => p.playerNo == playerNo).SetThrowRess(ressNo);
		}
		catch
		{
			debugMessage(DebugLevel.Error, "Error: bad parameters in ft_player_vomit. " + s);
		}
	}
	
	void	ft_player_picks(string s)
	{
		try
		{
			int playerNo = int.Parse (s.Split (' ') [0]);
			int ressNo = int.Parse (s.Split (' ') [1]);
			Player play = players.Find(p => p.playerNo == playerNo);

			play.SetPickRess(ressNo);
			//should not be triggered here but we animations kicks in
			//maybe never since bct is not in queue
//			map.RemoveStone((int)(play.transform.position.x), (int)(play.transform.position.z), ressNo);
		}
		catch
		{
			debugMessage(DebugLevel.Error, "Error: bad parameters in ft_player_picks. " + s);
		}
	}
	
	void	ft_player_died(string s)
	{
		int playerNo;

		try
		{
			if (gameover == true)
				return ;
			playerNo = int.Parse(s);
			Player p = players.Find(pp => pp.playerNo == playerNo);
			players.Remove(p);
			teams.Find(t => t.teamName == p.teamName).players.Remove(p);
			p.SetDie();
		}
		catch
		{
			debugMessage(DebugLevel.Error, "Error: bad parameters in ft_player_died. " + s);
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
			debugMessage(DebugLevel.Error, "Error: bad parameters number in ft_new_egg_pos. " + s);
			return ;
		}
		try
		{
			debugMessage(DebugLevel.Info, "New egg. " + s);
			eggNo = int.Parse(split [0]);
			playerNo = int.Parse(split [1]);
			Player player = players.Find(p => p.playerNo == playerNo);
			x = int.Parse(split [2]);
			y = int.Parse(split [3]);
			eggs.Add (map.dalles [x, y].GetComponent<Content> ().layEgg (eggNo, playerNo, player.teamName, player.teamColor));
			players.Find(p => p.playerNo == playerNo).SetStopLaying(eggNo);
		}
		catch
		{
			debugMessage(DebugLevel.Error, "Error: bad parameters in ft_new_egg_pos. " + s);
		}
	}

	public Player	GetIdlePlayer(int x, int y, string team)
	{
		if (players.Exists (p => p.posx == x && p.posy == y && p.idle == true && p.teamName == team) == false)
			return null;
		Player play = players.Find (p => p.posx == x && p.posy == y && p.idle == true && p.teamName == team);
		return (play);
	}

	void	ft_egg_born(string s)
	{
		Egg egg;
		int eggNo;

		try
		{
			eggNo = int.Parse(s);
			egg = eggs.Find(x => x.eggNo == eggNo);
			players.Find(x => x.playerNo == egg.playerNo).SetEggReady(eggNo);
			debugMessage(DebugLevel.Info, "Egg ready. " + s);
		}
		catch
		{
			debugMessage(DebugLevel.Error, "Error: bad parameters in ft_egg_born. " + s);
		}
	}
	void	ft_player_replaces_egg(string s)
	{
		Egg egg = null;

		try
		{
			//we get pno X Y Or team
			string []ss = s.Split(' ');

			int playerNo = int.Parse(ss[0]);
			int x = int.Parse(ss[1]);
			int y = int.Parse(ss[2]);
			int or = int.Parse(ss[3]);
			string team = ss[4];
			bool ready;

			if (eggs.Exists(e => e.posx == x && e.posy == y && e.ready == true && e.teamName == team) == true)
			{
				egg = eggs.Find(e => e.posx == x && e.posy == y && e.ready == true && e.teamName == team);
				ready = true;
			}
			else
				ready = false;
			Player newPlayer = Instantiate<Player>(playerPrefab);
			newPlayer.Initnew (playerNo, x, y, or, 1, team, false, ready);
			newPlayer.transform.parent = GameObject.Find("World").transform;
			players.Add(newPlayer);
			teams.Find(t => t.teamName == team).AddPlayer(newPlayer);
			if (ready == true)
			{
				egg.KillEgg();
			}
		}
		catch
		{
			debugMessage(DebugLevel.Error, "Error: bad parameters in ft_player_replaces_egg. " + s);
		}
	}

	void	ft_egg_died(string s)
	{
		Egg egg;
		int eggNo;

		try
		{
			eggNo = int.Parse(s);
			egg = eggs.Find (x => x.eggNo == eggNo);
			players.Find(x => x.playerNo == egg.playerNo).SetEggDie(eggNo);
		}
		catch
		{
			debugMessage(DebugLevel.Error, "Error: bad parameters in ft_egg_died. " + s);
		}
	}
	
	void	ft_end(string s)
	{
		try
		{
			gameover = true;
			debugMessage(DebugLevel.Warning, "END " + s);
			foreach (var p in players.FindAll(p => p.teamName == s))
			{
				p.SetCelebration();
			}
		}
		catch
		{
			debugMessage(DebugLevel.Error, "Error: bad parameters in ft_end. " + s);
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
        msgBox.ServerMessage(s, Color.white);
		Connection.con.writeSocket ("GRAPHIC");
		System.Threading.Thread.Sleep (50);
	}

	void Start () {

		em = this.GetComponent<EventsManager> ();
		msgBox = Instantiate<MessagesBox>(msgBox);
		map = ground.GetComponent<GroundGenerator> ();
		eggs = new List<Egg> ();
		teams = new List<Team> ();
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
		functions.Add("pbc", ft_player_broadcast);
		functions.Add("pic", ft_player_incantation);
		functions.Add("pie", ft_player_end_incantation);
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
		if (celebrationDone == true)
			return;
		bool end = false;
		foreach (Team t in teams) {
			foreach (Player p in t.players)
			{
				if (p.win == false){
					end = false;
					t.win = false;
					break;
				}
				t.win = true;
				end = true;
			}
		}
		if (end == true) {
			foreach (Player p in players)
			{
				if (p.win == true)
					p.ForceCelebration();
				else
					p.ForceDie();
			}
			Team winningTeam = teams.Find(t => t.win == true);
			msgBox.ServerMessage("Team " + winningTeam.teamName + " won !", Color.red);
			celebrationDone = true;
		}
	}
}