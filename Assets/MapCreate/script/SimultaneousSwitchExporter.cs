
using System.Globalization;
using System.IO;
using System.Text;
using UnityEngine;
using UnityEngine.SceneManagement;

public class SimultaneousSwitchExporter : MonoBehaviour
{
    [Header("同時押しスイッチ")]
    public Transform switchBlack;
    public Transform switchWhite;

    [Header("起動する遮光壁")]
    public Transform targetBlock;

    [Header("動作設定")]
    public bool keepMoving = true;

    [Header("ファイル出力")]
    public string fileName = "SimultaneousSwitch";

    [ContextMenu("同時押しスイッチ情報を出力")]
    public void Export()
    {
        if (switchBlack == null ||
            switchWhite == null ||
            targetBlock == null)
        {
            Debug.LogError(
                "スイッチまたは遮光壁が設定されていません");
            return;
        }

        string F(float value)
        {
            return value.ToString(
                "R", CultureInfo.InvariantCulture);
        }

        string V(Vector3 value)
        {
            return F(value.x) + "," +
                   F(value.y) + "," +
                   F(value.z);
        }

        string data =
            "SIMULTANEOUS_SWITCH\n" +
            "SwitchName=SwitchPair_1\n" +
            "SwitchBlack=" + switchBlack.name + "\n" +
            "SwitchBlackPosition=" + V(switchBlack.position) + "\n" +
            "SwitchWhite=" + switchWhite.name + "\n" +
            "SwitchWhitePosition=" + V(switchWhite.position) + "\n" +
            "TargetBlock=" + targetBlock.name + "\n" +
            "ActivationType=2人同時押し\n" +
            "KeepMoving=" + (keepMoving ? "true" : "false") + "\n";

        string sceneName = SceneManager.GetActiveScene().name;

        string outputFileName =
            Path.GetFileNameWithoutExtension(fileName) +
            "_" + sceneName + ".txt";

        string path = Path.Combine(
            Application.dataPath, outputFileName);

        File.WriteAllText(
            path,
            data,
            new UTF8Encoding(false)
        );

        Debug.Log(
            "同時押しスイッチ情報を出力しました: " + path);

#if UNITY_EDITOR
        UnityEditor.AssetDatabase.Refresh();
#endif
    }
}

