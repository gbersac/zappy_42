using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class dallesInfoPanel : MonoBehaviour {
	

	public void	setinfo(float posx, float posy, int nourriture,
	                    int linemate, int deraumere, int sibur, int mediane, int phiras, int thysame)
	{
		transform.FindChild ("Panel/Main/Position").GetComponent<Text> ().text = "x = " + posx.ToString() + " y = " + posy.ToString();
		transform.FindChild ("Panel/Food/Value").GetComponent<Text> ().text = nourriture.ToString();
		transform.FindChild ("Panel/Stone deraumere/Value").GetComponent<Text> ().text = deraumere.ToString();
		transform.FindChild ("Panel/Stone linemate/Value").GetComponent<Text> ().text = linemate.ToString();
		transform.FindChild ("Panel/Stone mediane/Value").GetComponent<Text> ().text = mediane.ToString();
		transform.FindChild ("Panel/Stone phiras/Value").GetComponent<Text> ().text = phiras.ToString ();
		transform.FindChild ("Panel/Stone sibur/Value").GetComponent<Text> ().text = sibur.ToString();
		transform.FindChild ("Panel/Stone thysame/Value").GetComponent<Text> ().text = thysame.ToString();
		return ;
	}

}
