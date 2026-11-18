
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

    [Header("移動方式")]
    public MovementType movementType = MovementType.PingPong;

    public enum MovementType
    {
        PingPong,
        OneWey
    }

    [Header("ファイル出力")]
    public string fileName = "MovingBlockPath";

    [ContextMenu("移動ブロック情報を出力")]
    public void Export()
    {
        if (movingBlock == null || blockBody == null)
        {
            Debug.LogError(
                "MovingBlockまたはBlockBodyが設定されていません");
            return;
        }

        if (speed <= 0f)
        {
            Debug.LogError(
                "移動速度は0より大きい値にしてください");
            return;
        }

        if (blockBody != movingBlock &&
            !blockBody.IsChildOf(movingBlock))
        {
            Debug.LogError(
                "BlockBodyはMovingBlockの子にしてください");
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

        string sceneName =
            SceneManager.GetActiveScene().name;

        string data =
            "MOVING_BLOCK\n" +
            "BlockName=" + movingBlock.name + "\n" +
            "BodyName=" + blockBody.name + "\n" +
            "StartPosition=" + V(startPosition) + "\n" +
            "EndPosition=" + V(endPosition) + "\n" +
            "BodyLocalPosition=" +
                V(blockBody.localPosition) + "\n" +
            "BodyLocalScale=" +
                V(blockBody.localScale) + "\n" +
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

        Debug.Log(
            "移動ブロック情報を出力しました: " + path);

#if UNITY_EDITOR
        UnityEditor.AssetDatabase.Refresh();
#endif
    }

    [Header("動線の表示")]
    public bool showPath = true;

    public Color pathColor = Color.yellow;

    [Header("ガイド表示設定")]
    public bool showBlockOutline = true;

    public bool showMovementArea = true;

    [Min(0.01f)]
    public float pointSize = 0.15f;

    private void OnDrawGizmos()
    {
        if (!showPath)
            return;

        Gizmos.color = pathColor;

        // 開始位置と終了位置を結ぶ
        Gizmos.DrawLine(startPosition, endPosition);

        // 開始位置
        Gizmos.DrawSphere(startPosition, pointSize);

        // 終了位置
        Gizmos.DrawSphere(endPosition, pointSize);

        if (movingBlock == null || blockBody == null)
            return;

        if (blockBody != movingBlock &&
            !blockBody.IsChildOf(movingBlock))
            return;

        // 移動ブロックの形状を取得
        Matrix4x4 bodyRelativeMatrix =
            movingBlock.worldToLocalMatrix *
            blockBody.localToWorldMatrix;

        // 移動ブロックの現在の回転とスケール
        Matrix4x4 startMatrix =
            Matrix4x4.TRS(
                startPosition,
                movingBlock.rotation,
                movingBlock.lossyScale
            ) * bodyRelativeMatrix;

        Matrix4x4 endMatrix =
            Matrix4x4.TRS(
                endPosition,
                movingBlock.rotation,
                movingBlock.lossyScale
            ) * bodyRelativeMatrix;

        // ブロックのローカル形状
        Vector3 localCenter = Vector3.zero;
        Vector3 localSize = Vector3.one;

        // Unity標準Cubeのメッシュ形状を想定
        MeshFilter meshFilter =
            blockBody.GetComponent<MeshFilter>();

        if (meshFilter != null &&
            meshFilter.sharedMesh != null)
        {
            Bounds bounds =
                meshFilter.sharedMesh.bounds;

            localCenter = bounds.center;
            localSize = bounds.size;
        }

        // 開始・終了地点のブロック枠
        if (showBlockOutline)
        {
            DrawBlockOutline(
                startMatrix,
                localCenter,
                localSize
            );

            DrawBlockOutline(
                endMatrix,
                localCenter,
                localSize
            );
        }

        // 移動範囲の四隅を線で結ぶ
        if (showMovementArea)
        {
            DrawMovementArea(
                startMatrix,
                endMatrix,
                localCenter,
                localSize
            );
        }

        // Gizmosの状態を戻す
        Gizmos.matrix = Matrix4x4.identity;
    }

    private void DrawBlockOutline(
        Matrix4x4 matrix,
        Vector3 center,
        Vector3 size)
    {
        Gizmos.matrix = matrix;
        Gizmos.DrawWireCube(center, size);
        Gizmos.matrix = Matrix4x4.identity;
    }

    private void DrawMovementArea(
        Matrix4x4 startMatrix,
        Matrix4x4 endMatrix,
        Vector3 center,
        Vector3 size)
    {
        Vector3 half = size * 0.5f;

        for (int x = -1; x <= 1; x += 2)
        {
            for (int y = -1; y <= 1; y += 2)
            {
                for (int z = -1; z <= 1; z += 2)
                {
                    Vector3 corner =
                        center + new Vector3(
                            half.x * x,
                            half.y * y,
                            half.z * z
                        );

                    Vector3 startCorner =
                        startMatrix.MultiplyPoint3x4(corner);

                    Vector3 endCorner =
                        endMatrix.MultiplyPoint3x4(corner);

                    Gizmos.DrawLine(
                        startCorner,
                        endCorner
                    );
                }
            }
        }
    }
}
