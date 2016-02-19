using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class Team {
	public List<Player> players;
	public string teamName;
	public Color teamColor = Color.white;
	private Color []colors = new Color[3] { Color.white, Color.blue, Color.red };
//	private Color []colors = new Color[3] { Color.black, Color.white, Color.red };
//	private Color []colors = new Color[3] { Color.black, Color.white, Color.red };
	public void InitTeam(string name, int teamNo)
	{
		players = new List<Player> ();
		teamName = name;
		teamNo = teamNo % colors.Length;
		teamColor = colors [teamNo];
	}

	public void AddPlayer(Player p)
	{
		this.players.Add (p);
		p.SetColor (teamColor);
	}
}
