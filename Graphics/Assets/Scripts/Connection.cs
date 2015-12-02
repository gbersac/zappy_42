using UnityEngine;
using System.Collections;
using System;
using System.Net;
using System.Net.Sockets;
using UnityEngine.UI;

public class Connection : MonoBehaviour {

	public	GameObject 	menu;
	public	GameObject	world;
	public	InputField 	field;
	public	int			port;

	private Socket _clientSocket = new Socket(AddressFamily.InterNetwork,SocketType.Stream,ProtocolType.Tcp);
	private byte[] _recieveBuffer = new byte[8142];

	void	Start()
	{
	}


	private void SetupServer(int port)
	{
		try
		{
			_clientSocket.Connect(new IPEndPoint(IPAddress.Loopback, port));
		}
		catch(SocketException ex)
		{
			Debug.Log(ex.Message);
			_clientSocket.Disconnect(true);
			return ;
		}
		Debug.Log("Connected...");
		menu.SetActive (false);
		world.SetActive (true);

		_clientSocket.BeginReceive(_recieveBuffer,0,_recieveBuffer.Length,SocketFlags.None,new AsyncCallback(ReceiveCallback),null);
		
	}
	
	private void ReceiveCallback(IAsyncResult AR)
	{
		//Check how much bytes are recieved and call EndRecieve to finalize handshake
		int recieved = _clientSocket.EndReceive(AR);
		
		if(recieved <= 0)
			return;
		
		//Copy the recieved data into new buffer , to avoid null bytes
		byte[] recData = new byte[recieved];
		Buffer.BlockCopy(_recieveBuffer,0,recData,0,recieved);
		
		//Process data here the way you want , all your bytes will be stored in recData
		
		//Start receiving again
		_clientSocket.BeginReceive(_recieveBuffer,0,_recieveBuffer.Length,SocketFlags.None,new AsyncCallback(ReceiveCallback),null);
	}
	
	private void SendData(byte[] data)
	{
		SocketAsyncEventArgs socketAsyncData = new SocketAsyncEventArgs();
		socketAsyncData.SetBuffer(data,0,data.Length);
		_clientSocket.SendAsync(socketAsyncData);
	}




	public void	StartConnection()
	{
		port = int.Parse (field.text);
		SetupServer (port);
	}


	void	Update()
	{
		if (Input.GetKey(KeyCode.Escape))
		{
			_clientSocket.Disconnect(true);
			Debug.Log ("Disconected...");
			world.SetActive (false);
			menu.SetActive(true);
		}
	}

}
