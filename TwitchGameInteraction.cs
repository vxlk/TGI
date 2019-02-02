using System;
using System.Runtime.InteropServices;
using UnityEngine;
using UnityEngine.SceneManagement;

public class TwitchGameInteraction : MonoBehaviour {

    //DL CODE ---- DEPRECATED

    /*
    // Use this for initialization
#if UNITY_EDITOR || UNITY_STANDALONE
    const string dllname = "TGIChatBot_STD";
#elif UNITY_IOS
    const string dllname = "__Internal";
#endif

    //dll functions
    [DllImport(dllname, EntryPoint = "createInstance", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr createInstance();

    [DllImport(dllname, EntryPoint = "closeInstance", CallingConvention = CallingConvention.Cdecl)]
    private static extern void closeInstance(IntPtr _impl);

    [DllImport(dllname, EntryPoint = "botInit", CallingConvention = CallingConvention.Cdecl)]
    private static extern void botInit(IntPtr _impl);
    */
    public System.Diagnostics.Process process;
    static bool canStart = false;

    void Start()
    {
        process = System.Diagnostics.Process.Start("TGIChatBot.exe");
        //process = System.Diagnostics.Process.GetCurrentProcess();
        /*
        Debug.Log("key was registered as pressed, bot should have init");
        var bot = createInstance();
        botInit(bot);
        Debug.Log("bot finished");
        */
    }

    // Update is called once per frame
    void Update()
    {
        var isRunning = !process.HasExited;
        if (!isRunning)
        {
            //disable the object, reload the scene when closed
            gameObject.SetActive(false);
            SceneManager.LoadScene(SceneManager.GetActiveScene().name);
        }
    }
}
