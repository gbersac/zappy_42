using UnityEngine;
using UnityEngine.UI;
using System.Collections;
using System.Collections.Generic;

public class MessagesBox : MonoBehaviour {
    public Text msgUI;
    string textColor = "#000000ff";
    string defaultColor = "#000000ff";
    List<string> msgs= new List<string>();

    void rmMessage()
    {
        msgUI.CrossFadeAlpha(0, 1.0f, true);
    }

    void displayMessage(string s)
    {
        System.DateTime now = System.DateTime.Now;
        s = "<color=" + textColor + ">" + now.ToString("<b>[HH:mm:ss]</b> ") + s + "</color>";
        msgs.Add(s);
        if (msgs.Count > 5)
            msgs.RemoveAt(0);
        msgUI.text = string.Join("\n", msgs.ToArray());
        msgUI.enabled = true;
        msgUI.CrossFadeAlpha(1, 0f, true);
    }

    string colorToHexa(Color color)
    {
        string ret = "#";
        ret += ((int)(color.r * 255)).ToString("x2");
        ret += ((int)(color.g * 255)).ToString("x2");
        ret += ((int)(color.b * 255)).ToString("x2");
        ret += "ff";
        Debug.Log(ret);
        return ret;
    }

    public void ServerMessage(string s, Color color)
    {
        textColor = colorToHexa(color);
        CancelInvoke("rmMessage");
        displayMessage(s);
        Invoke("rmMessage", 5);
        textColor = defaultColor;
    }

    void Start()
    {
        msgUI.enabled = false;
        msgUI.text = null;
    }
}
