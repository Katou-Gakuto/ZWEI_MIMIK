
using UnityEngine;
using UnityEngine.SceneManagement;
using System.IO;
using System.Text;
using System.Globalization;

public class RotatingBlockExporter : MonoBehaviour
{
    [Header("回転ブロック")]
    public Transform rotatingBlockPivot;
    public Transform rotatingBlockBody;

    [Header("回転設定")]
    public float startAngle = 0f;
    public float endAngle = -90f;
    public float rotationDuration = 1f;

    [ContextMenu("回転ブロック情報を出力")]
    public void Export()
    {
        if (rotatingBlockPivot == null ||
            rotatingBlockBody == null)
        {
            Debug.LogError(
                "回転ブロックが登録されていません。"
            );
            return;
        }

        if (rotationDuration <= 0f)
        {
            Debug.LogError(
                "回転時間は0より大きくしてください。"
            );
            return;
        }

        string sceneName =
            SceneManager.GetActiveScene().name;

        string path = Path.Combine(
            Application.dataPath,
            "RotatingBlockData_" + sceneName + ".txt"
        );

        StringBuilder sb = new StringBuilder();

        sb.AppendLine("ROTATING_BLOCK_DATA");
        sb.AppendLine("BlockCount=1");
        sb.AppendLine();

        sb.AppendLine(
            "BlockName=" + rotatingBlockPivot.name
        );

        sb.AppendLine(
            "PivotPosition=" +
            FormatVector(rotatingBlockPivot.position)
        );

        sb.AppendLine(
            "BodyLocalPosition=" +
            FormatVector(rotatingBlockBody.localPosition)
        );

        sb.AppendLine(
            "BodyLocalScale=" +
            FormatVector(rotatingBlockBody.localScale)
        );

        sb.AppendLine(
            "StartAngle=" + FormatFloat(startAngle)
        );

        sb.AppendLine(
            "EndAngle=" + FormatFloat(endAngle)
        );

        sb.AppendLine(
            "RotationDuration=" +
            FormatFloat(rotationDuration)
        );

        File.WriteAllText(
            path,
            sb.ToString(),
            new UTF8Encoding(false)
        );

        Debug.Log(
            "回転ブロック情報を出力しました: " + path
        );

#if UNITY_EDITOR
        UnityEditor.AssetDatabase.Refresh();
#endif
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
