using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TGIManager : MonoBehaviour {
    public Component child;
	// Use this for initialization

	void Start () {
        child.gameObject.SetActive(false);
	}
	
	// Update is called once per frame
	void Update () {
		
	}

    public void setTGIActive()
    {
        child.gameObject.SetActive(true);
    }
}
