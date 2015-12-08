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
	string					message;

	internal Boolean		socketReady = false;
	private TcpClient		mySocket;
	private NetworkStream	theStream;
	private StreamWriter	theWriter;
	private StreamReader	theReader;

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
	
	public String readSocket()
	{
		if (!socketReady) {
			return "";
		}
		if (theStream.DataAvailable) {
			var s = theReader.ReadLine();
			Debug.Log(s);
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
		//Temporary
		writeSocket("msz");

	}


	void	Update()
	{
		if ((message = readSocket ()) != "") {
			//Debug.Log ("ou est charly " + message.Length);
			EventsManager.em.Parse(message);
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
