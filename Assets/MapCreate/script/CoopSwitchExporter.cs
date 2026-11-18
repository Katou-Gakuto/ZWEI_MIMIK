
using UnityEngine;
using UnityEngine.SceneManagement;
using System.IO;
using System.Text;
using System.Globalization;

public class CoopSwitchExporter : MonoBehaviour
{
    [Header("同時押しスイッチ")]
    public Transform upperSwitch;
    public Transform lowerSwitch;

    [Header("連動する回転ブロック")]
    public Transform rotatingBlockPivot;

    [Header("動作設定")]
    public bool requireBothPressed = true;
    public bool activeWhilePressed = true;

    [ContextMenu("同時押しスイッチ情報を出力")]
    public void Export()
    {
        if (upperSwitch == null ||
            lowerSwitch == null ||
            rotatingBlockPivot == null)
        {
            Debug.LogError(
                "スイッチまたは回転ブロックが登録されていません。"
            );
            return;
        }

        if (upperSwitch == lowerSwitch)
        {
            Debug.LogError(
                "2つのスイッチに同じオブジェクトが登録されています。"
            );
            return;
        }

        string sceneName =
            SceneManager.GetActiveScene().name;

        string path = Path.Combine(
            Application.dataPath,
            "CoopSwitchData_" + sceneName + ".txt"
        );

        StringBuilder sb = new StringBuilder();

        sb.AppendLine("COOP_SWITCH_DATA");
        sb.AppendLine("SwitchCount=2");
        sb.AppendLine();

        WriteSwitch(sb, upperSwitch, "Upper");
        sb.AppendLine();

        WriteSwitch(sb, lowerSwitch, "Lower");
        sb.AppendLine();

        sb.AppendLine(
            "TargetBlock=" + rotatingBlockPivot.name
        );

        sb.AppendLine(
            "RequireBothPressed=" +
            (requireBothPressed ? "true" : "false")
        );

        sb.AppendLine(
            "ActiveWhilePressed=" +
            (activeWhilePressed ? "true" : "false")
        );

        File.WriteAllText(
            path,
            sb.ToString(),
            new UTF8Encoding(false)
        );

        Debug.Log(
            "同時押しスイッチ情報を出力しました: " + path
        );

#if UNITY_EDITOR
        UnityEditor.AssetDatabase.Refresh();
#endif
    }

    private void WriteSwitch(
        StringBuilder sb,
        Transform switchTransform,
        string switchId)
    {
        sb.AppendLine("SwitchID=" + switchId);

        sb.AppendLine(
            "SwitchName=" + switchTransform.name
        );

        sb.AppendLine(
            "Position=" +
            FormatVector(switchTransform.position)
        );

        sb.AppendLine(
            "Scale=" +
            FormatVector(switchTransform.lossyScale)
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

