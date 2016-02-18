using UnityEngine;
using System.Collections;
using System;
using System.IO;
using System.Net.Sockets;
using UnityEngine.UI;

public class Connection : MonoBehaviour {

	public	GameObject 		menu;
	public	GameObject		world;
	public	InputField 		portField;
	public	InputField 		hostField;

	string					host;
	int						port;

	Boolean					socketReady = false;
	TcpClient				mySocket;
	NetworkStream			theStream;
	StreamWriter			theWriter;
	StreamReader			theReader;

	static public Connection con;

	void	Start()
	{
		con = this.GetComponent<Connection> ();
	}

	public void setupSocket()
	{
//		try {
//			host = hostField.text;
//			if (string.IsNullOrEmpty(host))
//				host = "localhost";
//			port = int.Parse(portField.text);
//			mySocket = new TcpClient(host, port);
//			theStream = mySocket.GetStream();
//			theWriter = new StreamWriter(theStream);
//			theReader = new StreamReader(theStream);
//			theReader.BaseStream.ReadTimeout = 1000;
//			socketReady = true;
//			Debug.Log ("Connected");
//			menu.SetActive(false);
//			world.SetActive(true);
//			EventsManager.em.speedController.SetActive (true);
//		}
		try {
			host = hostField.text;
			if (string.IsNullOrEmpty(host))
				host = "localhost";
			port = int.Parse(portField.text);
			mySocket = new TcpClient();
			var result = mySocket.BeginConnect(host, port, null, null);
			bool success = result.AsyncWaitHandle.WaitOne(TimeSpan.FromSeconds(2));
			if (!success)
				throw new Exception("Connection timed out.");
			mySocket.EndConnect(result);
			theStream = mySocket.GetStream();
			theWriter = new StreamWriter(theStream);
			theReader = new StreamReader(theStream);
			theReader.BaseStream.ReadTimeout = 1000;
			socketReady = true;
			Debug.Log ("Connected");
			menu.SetActive(false);
			world.SetActive(true);
			EventsManager.em.speedController.SetActive (true);
			EventsManager.em.dallesPanels.SetActive (true);
		}
		catch (Exception e) {
			Debug.Log("Socket error: " + e);
			EventsManager.em.msgBox.ServerMessage("Connection failed: " + e.Message, Color.red);
			//Application.LoadLevel(0);
		}
	}
	
	public void writeSocket(string theLine)
	{
		if (!theStream.CanWrite) {
			Debug.Log("Socket not ready ! " + theLine);
			return;
		}
		//Debug.Log ("Sending " + theLine);
		string foo = theLine + "\n";
		theWriter.Write(foo);
		theWriter.Flush();
	}
	
	void ReadSock()
	{
		int len = mySocket.Available;
		if (len <= 0)
			return;
		socketReady = false;
		char [] buf = new char[len];
		theReader.Read (buf, 0, len);
		string s = new string (buf);
		string [] ss = s.Split ('\0');
		foreach (string s0 in ss) {
			if (!string.IsNullOrEmpty (s0)) {
		//		Debug.Log (s0);
				EventsManager.em.Parse (s0);
			}
		}
		socketReady = true;
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
		setupSocket ();
	}

	void	Update()
	{
		if (socketReady)
			ReadSock ();

		if (Input.GetKey(KeyCode.Escape))
		{
			closeSocket();
			Debug.Log ("Disconnected...");
			world.SetActive (false);
			menu.SetActive(true);
			EventsManager.em.speedController.SetActive (false);
			EventsManager.em.dallesPanels.SetActive (false);
			Application.LoadLevel(0);
		}
	}

}
