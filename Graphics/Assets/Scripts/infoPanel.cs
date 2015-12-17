using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class infoPanel : MonoBehaviour {

	int[] tab_deraumere = new[] {0,1,0,1,2,2,2};
	int[] tab_linemate = new[] {1,1,2,1,1,1,2};
	int[] tab_mediane = new[] {0,0,0,0,3,0,2};
	int[] tab_phiras = new[] {0,0,2,1,0,1,2};
	int[] tab_sibur = new[] {0,1,1,2,1,3,2};
	int[] tab_thysame = new[] {0,0,0,0,0,0,1};

	public void	setinfo(string name, int posx, int posy, int level, int nourriture,
	                    int deraumere, int linemate, int mediane, int phiras, int sibur, int thysame)
	{
		transform.FindChild ("Panel/Main/Name").GetComponent<Text> ().text = name;
		transform.FindChild ("Panel/Main/Position").GetComponent<Text> ().text = "x = " + posx.ToString() + " y = " + posy.ToString();
		transform.FindChild ("Panel/Stone deraumere/Value").GetComponent<Text> ().text = deraumere.ToString() + " / " + tab_deraumere[level-1].ToString();
		transform.FindChild ("Panel/Stone linemate/Value").GetComponent<Text> ().text = linemate.ToString() + " / " + tab_linemate[level-1].ToString();
		transform.FindChild ("Panel/Stone mediane/Value").GetComponent<Text> ().text = mediane.ToString() + " / " + tab_mediane[level-1].ToString();
		transform.FindChild ("Panel/Stone phiras/Value").GetComponent<Text> ().text = phiras.ToString() + " / " + tab_phiras[level-1].ToString();
		transform.FindChild ("Panel/Stone sibur/Value").GetComponent<Text> ().text = sibur.ToString() + " / " + tab_sibur[level-1].ToString();
		transform.FindChild ("Panel/Stone thysame/Value").GetComponent<Text> ().text = thysame.ToString() + " / " + tab_thysame[level-1].ToString();
		return ;
	}
}
