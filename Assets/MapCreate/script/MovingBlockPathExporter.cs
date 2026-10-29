
using System.Globalization;
using System.IO;
using UnityEngine;
using UnityEngine.SceneManagement;

public class MovingBlockPathExporter : MonoBehaviour
{
    [Header("移動ブロック")]
    public Transform movingBlock;
    public Transform blockBody;

    [Header("移動範囲（ワールド座標）")]
    public Vector3 startPosition = new Vector3(-2.5f, 0f, 0f);
    public Vector3 endPosition = new Vector3(2.5f, 0f, 0f);

    [Header("移動速度（Unity units/秒）")]
    public float speed = 1f;

    [Header("移動速度（Unity units/秒）")]
    public MovementType movementType = MovementType.PingPong;

    public enum MovementType
    {
        PingPong,   //  往復移動
        OneWey      //　一方向移動(終点で停止)
    }

    [Header("ファイル出力")]
    public string fileName = "MovingBlockPath";

    [ContextMenu("移動ブロック情報を出力")]
    public void Export()
    {
        if (movingBlock == null || blockBody == null)
        {
            Debug.LogError("MovingBlockまたはBlockBodyが設定されていません");
            return;
        }

        if (speed <= 0f)
        {
            Debug.LogError("移動速度は0より大きい値にしてください");
            return;
        }

        if (blockBody != movingBlock &&
            !blockBody.IsChildOf(movingBlock))
        {
            Debug.LogError("BlockBodyはMovingBlockの子にしてください");
            return;
        }

        string F(float value)
        {
            return value.ToString("R", CultureInfo.InvariantCulture);
        }

        string V(Vector3 value)
        {
            return F(value.x) + "," +
                   F(value.y) + "," +
                   F(value.z);
        }

        string sceneName = SceneManager.GetActiveScene().name;

        string data =
            "MOVING_BLOCK\n" +
            "BlockName=" + movingBlock.name + "\n" +
            "BodyName=" + blockBody.name + "\n" +
            "StartPosition=" + V(startPosition) + "\n" +
            "EndPosition=" + V(endPosition) + "\n" +
            "BodyLocalPosition=" + V(blockBody.localPosition) + "\n" +
            "BodyLocalScale=" + V(blockBody.localScale) + "\n" +
            "Speed=" + F(speed) + "\n" +
            "LoopType=" +
                (movementType == MovementType.PingPong
                    ? "往復移動"
                    : "一方向移動") + "\n";

        string outputFileName =
            Path.GetFileNameWithoutExtension(fileName) +
            "_" + sceneName + ".txt";

        string path = Path.Combine(
            Application.dataPath, outputFileName);

        File.WriteAllText(path, data);

        Debug.Log("移動ブロック情報を出力しました: " + path);

#if UNITY_EDITOR
        UnityEditor.AssetDatabase.Refresh();
#endif
    }


    [Header("動線の表示")]
    public bool showPath = true;

    public Color pathColor = Color.yellow;

    private void OnDrawGizmos()
    {
        if (!showPath)
        {
            return;
        }

        // 動線の色
        Gizmos.color = pathColor;

        // 開始位置から終了位置まで線を描画
        Gizmos.DrawLine(startPosition, endPosition);

        // 開始位置に球を描画
        Gizmos.DrawSphere(startPosition, 0.15f);

        // 終了位置に球を描画
        Gizmos.DrawSphere(endPosition, 0.15f);

        // ブロックの移動範囲を表示
        if (blockBody != null)
        {
            Vector3 blockSize = blockBody.lossyScale;

            // 開始位置のブロック
            Gizmos.DrawWireCube(
                startPosition + blockBody.localPosition,
                blockSize
            );

            // 終了位置のブロック
            Gizmos.DrawWireCube(
                endPosition + blockBody.localPosition,
                blockSize
            );
        }
    }

}

