using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using System.Linq;
using Poll;
using System.Text.RegularExpressions;
using System.IO;

public class Updater : MonoBehaviour {
    public PollResults p;
    public bool canRun = false;
    Updater()
    {
        //init
        p = new PollResults();
        canRun = false;
    }

    void changeVariable(string variableName, string filePath)
    {
        string line;
        string newline;

        //get number out of var name
        string numValue = Regex.Match(variableName, @"-?\d+").Value;
        Int32.Parse(numValue);
        Debug.Log("the number to be included : " + numValue);
        //open file
        var fileStream = new FileStream(filePath, FileMode.Open);
        //find pos(macro + 1)
        string varNameNoNum = variableName.Substring(variableName.IndexOf("!"), variableName.IndexOf(" ") - variableName.IndexOf("!"));
        Debug.Log("/*_TGI_MACRO_" + varNameNoNum + "*/");
        using (var streamReader = new StreamReader(fileStream))
        {
            while ((line = streamReader.ReadLine()) != null)
            {
                if (line.Contains("/*_TGI_MACRO_" + varNameNoNum + "*/")) break;
            }
            
            string lineToBeReplaced = line.Substring(line.IndexOf("*/")+2);
            Debug.Log(lineToBeReplaced);
            newline = line.Replace(lineToBeReplaced, numValue.ToString()+";");
            Debug.Log(line);

            streamReader.Close();

        }

        //rewrite the file!
        File.WriteAllText(filePath, File.ReadAllText(filePath).Replace(line, newline));
        
    }

	// Use this for initialization
	void Start () {
        //dont break the project if tgi is not installed
        string path = Directory.GetParent(Application.dataPath).ToString() + "/TGIChatBot.exe";
        if (File.Exists(path))
            canRun = true;

        if (canRun)
            changeVariable(p.runPoll(), Application.dataPath + "/Standard Assets" + "/Characters" + "/FirstPersonCharacter" + "/Scripts" + "/RigidbodyFirstPersonController.cs");
	}
	
	// Update is called once per frame
	void Update () {
		
	}
}
