
using UnityEngine;
using UnityEngine.SceneManagement;
using System.IO;
using System.Text;
using System.Globalization;

public class WarpSwitchExporter : MonoBehaviour
{
    [Header("赤色ワープスイッチ")]
    public Transform red1;
    public Transform red2;

    [Header("緑色ワープスイッチ")]
    public Transform green1;
    public Transform green2;

    [ContextMenu("ワープスイッチ情報を出力")]
    public void Export()
    {
        if (red1 == null || red2 == null ||
            green1 == null || green2 == null)
        {
            Debug.LogError(
                "ワープスイッチがすべて登録されていません。"
            );
            return;
        }

        string sceneName =
            SceneManager.GetActiveScene().name;

        string path = Path.Combine(
            Application.dataPath,
            "WarpSwitchData_" + sceneName + ".txt"
        );

        StringBuilder sb = new StringBuilder();

        sb.AppendLine("WARP_SWITCH_DATA");
        sb.AppendLine("SwitchCount=4");
        sb.AppendLine();

        WriteSwitch(sb, red1, "Red", red2.name);
        sb.AppendLine();

        WriteSwitch(sb, red2, "Red", red1.name);
        sb.AppendLine();

        WriteSwitch(sb, green1, "Green", green2.name);
        sb.AppendLine();

        WriteSwitch(sb, green2, "Green", green1.name);

        File.WriteAllText(
            path,
            sb.ToString(),
            new UTF8Encoding(false)
        );

        Debug.Log(
            "ワープスイッチ情報を出力しました: " + path
        );

#if UNITY_EDITOR
        UnityEditor.AssetDatabase.Refresh();
#endif
    }

    private void WriteSwitch(
        StringBuilder sb,
        Transform warpSwitch,
        string color,
        string destination)
    {
        sb.AppendLine(
            "SwitchName=" + warpSwitch.name
        );

        sb.AppendLine(
            "Position=" + FormatVector(warpSwitch.position)
        );

        sb.AppendLine(
            "Scale=" + FormatVector(warpSwitch.lossyScale)
        );

        sb.AppendLine(
            "WarpColor=" + color
        );

        sb.AppendLine(
            "Destination=" + destination
        );
    }

    private string FormatVector(Vector3 value)
    {
        return FormatFloat(value.x) + "," +
               FormatFloat(value.y) + "," +
               FormatFloat(value.z);
    }

    private string FormatFloat(float value)
    {
        return value.ToString(
            "R",
            CultureInfo.InvariantCulture
        );
    }
}
