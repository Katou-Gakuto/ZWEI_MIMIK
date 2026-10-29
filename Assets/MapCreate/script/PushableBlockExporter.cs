
using System.Globalization;
using System.IO;
using UnityEngine;
using UnityEngine.SceneManagement;

public class PushableBlockExporter : MonoBehaviour
{
    [Header("押せるブロック")]
    public Transform pushableBlock;
    public Transform blockBody;

    [Header("押せる方向")]
    public bool canPushHorizontal = true;
    public bool canPushVertical = false;

    [Header("押す速度（Unity units/秒）")]
    public float pushSpeed = 1f;

    [Header("ファイル出力")]
    public string fileName = "PushableBlock";

    [ContextMenu("押せるブロック情報を出力")]
    public void Export()
    {
        if (pushableBlock == null || blockBody == null)
        {
            Debug.LogError("ブロックが設定されていません");
            return;
        }

        if (!blockBody.IsChildOf(pushableBlock))
        {
            Debug.LogError("BlockBodyは押せるブロックの子にしてください");
            return;
        }

        if (pushSpeed <= 0f)
        {
            Debug.LogError("押す速度は0より大きくしてください");
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

        string pushDirection = "None";

        if (canPushHorizontal && canPushVertical)
        {
            pushDirection = "上下左右";
        }
        else if (canPushHorizontal)
        {
            pushDirection = "左右";
        }
        else if (canPushVertical)
        {
            pushDirection = "上下";
        }

        string data =
            "PUSHABLE_BLOCK\n" +
            "BlockName=" + pushableBlock.name + "\n" +
            "Position=" + V(pushableBlock.position) + "\n" +
            "BodyLocalPosition=" + V(blockBody.localPosition) + "\n" +
            "BodySize=" + V(blockBody.lossyScale) + "\n" +
            "PushDirection=" + pushDirection + "\n" +
            "PushSpeed=" + F(pushSpeed) + "\n";

        string sceneName = SceneManager.GetActiveScene().name;

        string outputFileName =
            Path.GetFileNameWithoutExtension(fileName) +
            "_" + sceneName + ".txt";

        string path = Path.Combine(
            Application.dataPath, outputFileName);

        File.WriteAllText(
            path,
            data,
            new System.Text.UTF8Encoding(false)
        );

        Debug.Log("押せるブロック情報を出力しました: " + path);

#if UNITY_EDITOR
        UnityEditor.AssetDatabase.Refresh();
#endif
    }
}
