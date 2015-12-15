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
			theReader.BaseStream.ReadTimeout = 1000;
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
				//Debug.Log (s0);
				EventsManager.em.Parse (s0);
			}
		}
		socketReady = true;
	}

	public String readSocket()
	{
		if (!socketReady) {
			return string.Empty;
		}
		if (theStream.DataAvailable) {
			var s = theReader.ReadLine();
			Debug.Log("connection readed " + s);
			return (s);
		} else {
			return string.Empty;
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
		InitWorld ();
	}
	
	void	InitWorld()
	{
		writeSocket ("msz");
		System.Threading.Thread.Sleep (50);
		writeSocket ("mct");
		System.Threading.Thread.Sleep (50);
		writeSocket ("tna");
		//some call not being received by client
	}

	private int eggCounter = 0;//
	void	Update()
	{
		if (socketReady)
			ReadSock ();

		if (Input.GetKeyDown (KeyCode.A)) {
			writeSocket("ppo 1");
		}
		if (Input.GetKeyDown (KeyCode.S)) {
			writeSocket("pin 1");
		}
		if (Input.GetKeyDown (KeyCode.D)) {
			writeSocket("plv 1");
		}
		if (Input.GetKeyDown (KeyCode.F)) {
			int i = UnityEngine.Random.Range(0,10);
			int j = UnityEngine.Random.Range(0,10);
			EventsManager.em.Parse("enw " + eggCounter + " 0 " + i + " " + j);//min mapsize 10x10 !
			eggCounter++;
		}
		if (Input.GetKeyDown (KeyCode.G)) {
			EventsManager.em.Parse("eht " + (eggCounter - 1).ToString());
		}
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
