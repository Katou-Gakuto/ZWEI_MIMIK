
using UnityEngine;
using UnityEngine.SceneManagement;
using System.IO;
using System.Text;
using System.Globalization;

public class MirrorExporter : MonoBehaviour
{
    [Header("o—Í‚·‚é‹¾")]
    public Transform mirror1;
    public Transform mirror2;

    [Header("‰ñ“]‘€ì")]
    public bool mirror1Rotatable = true;
    public bool mirror2Rotatable = true;

    [ContextMenu("‹¾‚Ìî•ñ‚ğo—Í")]
    public void Export()
    {
        if (mirror1 == null || mirror2 == null)
        {
            Debug.LogError("‹¾‚ª“o˜^‚³‚ê‚Ä‚¢‚Ü‚¹‚ñ");
            return;
        }

        string sceneName = SceneManager.GetActiveScene().name;
        string path = Path.Combine(
            Application.dataPath,
            "MirrorData_" + sceneName + ".txt"
        );

        StringBuilder sb = new StringBuilder();

        sb.AppendLine("MIRROR_DATA");
        sb.AppendLine("MirrorCount=2");
        sb.AppendLine(); // ‹ó”’s‚ğ’Ç‰Á

        WriteMirror(sb, mirror1, mirror1Rotatable);

        // ‹¾‡@‚Æ‹¾‡A‚Ìî•ñ‚ÌŠÔ‚É‹ó”’s‚ğ’Ç‰Á
        sb.AppendLine();

        WriteMirror(sb, mirror2, mirror2Rotatable);

        File.WriteAllText(path, sb.ToString(),
            new UTF8Encoding(false));

        Debug.Log("‹¾‚Ìî•ñ‚ğo—Í‚µ‚Ü‚µ‚½: " + path);

#if UNITY_EDITOR
        UnityEditor.AssetDatabase.Refresh();
#endif
    }

    void WriteMirror(
        StringBuilder sb,
        Transform mirror,
        bool rotatable)
    {
        sb.AppendLine("MirrorName=" + mirror.name);
        sb.AppendLine("Position=" + FormatVector(mirror.position));
        sb.AppendLine("RotationY=" + FormatFloat(mirror.eulerAngles.y));
        sb.AppendLine("Scale=" + FormatVector(mirror.lossyScale));
        sb.AppendLine("Rotatable=" +
            rotatable.ToString().ToLowerInvariant());
    }

    string FormatVector(Vector3 v)
    {
        return FormatFloat(v.x) + "," +
               FormatFloat(v.y) + "," +
               FormatFloat(v.z);
    }

    string FormatFloat(float value)
    {
        return value.ToString("R", CultureInfo.InvariantCulture);
    }
}
