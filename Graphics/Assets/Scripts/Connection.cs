using UnityEngine;
using System.Collections;
using System;
using System.IO;
using System.Net.Sockets;
using UnityEngine.UI;

public class Connection : MonoBehaviour {

	public	GameObject 		menu;
	public	GameObject		world;
	public	InputField 		field;

	string					host;
	int						port;
//	string					message;

	Boolean					socketReady = false;
	TcpClient		mySocket;
	NetworkStream	theStream;
	StreamWriter	theWriter;
	StreamReader	theReader;

	static public Connection con;

	void	Start()
	{
		con = this.GetComponent<Connection> ();
	}

	public void setupSocket()
	{
		try {
			mySocket = new TcpClient(host, port);
			theStream = mySocket.GetStream();
			theWriter = new StreamWriter(theStream);
			theReader = new StreamReader(theStream);
			socketReady = true;
			Debug.Log ("Connected");
			menu.SetActive(false);
		}
		catch (Exception e) {
			Debug.Log("Socket error: " + e);
			Application.LoadLevel(0);
		}
	}
	
	public void writeSocket(string theLine)
	{
		if (!socketReady)
			return;
		string foo = theLine + "\n";
		theWriter.Write(foo);
		theWriter.Flush();
	}

	string half = string.Empty;
	void ReadSock()
	{
		socketReady = false;
		if (theStream.DataAvailable && theStream.CanRead) {
			char []buf = new char[1024];
			bool done = false;
			string s;
			while (!done)
			{
				int l;
				if ((l = theReader.Read (buf, 0, buf.Length)) <= 0)
				{
					Debug.Log("read failed");
					break ;
				}
				else if (l == buf.Length)
				{
					half = half + new string(buf);
					continue;
				}
				else
				{
					s = half + new string(buf);
					half = string.Empty;
				}
				string []ss = s.Split('\0');
				int i = 1;
				foreach (string s0 in ss)
				{
					Debug.Log ("len = " + s0.Length +  " read " + s0);
					if (!string.IsNullOrEmpty(s0) && i != ss.Length)
						EventsManager.em.Parse(s0);
				}
				//I have no idea why split adds an extra line each? time
				done = true;
			}
		}
		socketReady = true;
	}

	public String readSocket()
	{
		if (!socketReady) {
			return "";
		}
		if (theStream.DataAvailable) {
			var s = theReader.ReadLine();
			Debug.Log("connection readed " + s);
			return (s);
			//return theReader.ReadLine ();
		} else {
			return "";
		}
	}
	
	public void closeSocket()
	{
		if (!socketReady)
			return;
		theWriter.Close();
		theReader.Close();
		mySocket.Close();
		socketReady = false;
	}

	public void	StartConnection()
	{
		host = "127.0.0.1";
		port = int.Parse (field.text);
		setupSocket ();
	}

	void	Update()
	{
		if (socketReady)
			ReadSock ();
		
		if(Input.GetKeyDown(KeyCode.Q)){
			writeSocket("msz");
		}
		if(Input.GetKeyDown(KeyCode.W)){
			int i = UnityEngine.Random.Range(0,19);
			int j = UnityEngine.Random.Range(0,19);
			writeSocket("bct "+i.ToString()+" "+j.ToString());
		}
		if(Input.GetKeyDown(KeyCode.E)){
			writeSocket("mct");
		}
		if(Input.GetKeyDown(KeyCode.R)){
			writeSocket("tna");
		}
		if(Input.GetKeyDown(KeyCode.T)){
			writeSocket("ppo 0");
		}
		if(Input.GetKeyDown(KeyCode.Y)){
			writeSocket("plv 0");
		}
		if(Input.GetKeyDown(KeyCode.U)){
			writeSocket("pin 0");
		}
		if(Input.GetKeyDown(KeyCode.I)){
			writeSocket("sgt");
		}
		if(Input.GetKeyDown(KeyCode.O)){
			writeSocket("sst 10");
		}

		if (Input.GetKey(KeyCode.Escape))
		{
			closeSocket();
			Debug.Log ("Disconected...");
			world.SetActive (false);
			menu.SetActive(true);
		}
	}

}
