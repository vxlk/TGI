using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;

namespace Poll
{

    public class PollResults /*: MonoBehaviour*/
    {

        private Dictionary<string, int> validCommands;

        public PollResults()
        {
            validCommands = new Dictionary<string, int>();
        }

        void Start() { }
        void Update() { }

        //open valid command document, make a vector of valid commands
        private void getValidCommands()
        {
            //get project path
            string path = Directory.GetParent(Application.dataPath).ToString();
            var fileStream = new FileStream(path + "/Commands.txt", FileMode.Open);
            using (var streamReader = new StreamReader(fileStream))
            {
                string line;
                while ((line = streamReader.ReadLine()) != null)
                {
                    // process the line
                    validCommands.Add(line, 0);
                }

                Debug.Log("Valid Commands Found:...\n");
                foreach (KeyValuePair<string, int> i in validCommands)
                    Debug.Log(i);
            }
        }

        ///parse out the name
        //go through chat log, return the winner
       private string checkChatLogs()
        {
            string path = Directory.GetParent(Application.dataPath).ToString();
            var fileStream = new FileStream(path + "/ChatLog.txt", FileMode.Open);
            using (var streamReader = new StreamReader(fileStream))
            {
                string line;
                while ((line = streamReader.ReadLine()) != null)
                {
                    //look for generic name ie !speed, then if it is a valid command store the specific value ie !speed 50
                    Debug.Log(line);
                    //skip wrong format
                    if (line.IndexOf("!") == -1 || line.IndexOf(" ") == -1) continue;
                    Debug.Log(line.IndexOf("!"));
                    Debug.Log(line.IndexOf(" "));
                    string strippedLine = line.Substring(line.IndexOf("!"), line.IndexOf(" ") - line.IndexOf("!"));
                    Debug.Log("Stripped Name ->" + strippedLine);
                    if (validCommands.ContainsKey(strippedLine))
                    {
                        if (!validCommands.ContainsKey(line))
                            validCommands.Add(line, 1);
                        else validCommands[line]++;
                    }
                }

                KeyValuePair<string, int> winner = new KeyValuePair<string, int>("", 0);
                foreach (KeyValuePair<string, int> entry in validCommands)
                {
                    if (entry.Value > winner.Value) winner = entry;
                }
                Debug.Log("Winner: " + winner.Key);
                return winner.Key;
            }
        }

        public string runPoll()
        {
            getValidCommands();
            return checkChatLogs();
        }
    }

}