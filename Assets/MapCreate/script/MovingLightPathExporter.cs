
using System.Globalization;
using System.IO;
using UnityEngine;
using UnityEngine.SceneManagement;

public class MovingLightPathExporter : MonoBehaviour
{
    [Header("移動ライト")]
    public Transform movingLight;
    public Transform lightCenter;

    [Header("回転範囲（度）")]
    public float startAngle = -45f;
    public float endAngle = 45f;

    [Header("角速度（度/秒）")]
    public float speed = 30f;

    [Header("ファイル出力")]
    public string fileName = "MovingLightPath.txt";

    [ContextMenu("移動ライト情報を出力")]
    public void Export()
    {
        if (movingLight == null || lightCenter == null)
        {
            Debug.LogError("ライトが設定されていません");
            return;
        }

        if (speed <= 0f || startAngle >= endAngle)
        {
            Debug.LogError("回転範囲または速度が不正です");
            return;
        }

        Vector3 pivot = movingLight.position;
        Vector3 offset = movingLight.InverseTransformPoint(
            lightCenter.position);

        string F(float value)
        {
            return value.ToString(
                "R", CultureInfo.InvariantCulture);
        }

        string data =
            "MOVING_LIGHT\n" +
            "LightName=" + lightCenter.name + "\n" +
            "PivotPosition=" +
                F(pivot.x) + "," +
                F(pivot.y) + "," +
                F(pivot.z) + "\n" +
            "LocalPosition=" +
                F(offset.x) + "," +
                F(offset.y) + "," +
                F(offset.z) + "\n" +
            "BaseRotationY=" +
                F(movingLight.eulerAngles.y) + "\n" +
            "StartAngle=" + F(startAngle) + "\n" +
            "EndAngle=" + F(endAngle) + "\n" +
            "Speed=" + F(speed) + "\n" +
            "LoopType=往復移動\n";


        // 現在開いているSceneの名前を取得
        string sceneName = SceneManager.GetActiveScene().name;

        // 元のファイル名から拡張子を除去
        string baseFileName = Path.GetFileNameWithoutExtension(fileName);

        // Scene名を付けたファイル名を作成
        string outputFileName =
            baseFileName + "_" + sceneName + ".txt";

        // 保存先を設定
        string path = Path.Combine(
            Application.dataPath, outputFileName);

        // テキストファイルとして出力
        File.WriteAllText(path, data);


        Debug.Log("移動ライト情報を出力しました: " + path);

#if UNITY_EDITOR
        UnityEditor.AssetDatabase.Refresh();
#endif
    }


    [Header("動線の表示")]
    public bool showPath = true;

    public Color pathColor = Color.yellow;

    [Range(8, 100)]
    public int pathSegments = 40;

    private void OnDrawGizmos()
    {
        if (!showPath || movingLight == null || lightCenter == null)
        {
            return;
        }

        Gizmos.color = pathColor;

        // 現在の親オブジェクトの姿勢を基準にする
        Vector3 pivot = movingLight.position;
        Vector3 offset = movingLight.InverseTransformPoint(
            lightCenter.position);

        Quaternion baseRotation = movingLight.rotation;
        Vector3 baseScale = movingLight.lossyScale;

        Vector3 GetPoint(float angle)
        {
            Vector3 scaledOffset = Vector3.Scale(offset, baseScale);
            return pivot +
                baseRotation *
                (Quaternion.Euler(0f, angle, 0f) * scaledOffset);
        }

        // 円弧状の動線を描画
        Vector3 previousPoint = GetPoint(startAngle);

        for (int i = 1; i <= pathSegments; i++)
        {
            float t = (float)i / pathSegments;
            float angle = Mathf.Lerp(startAngle, endAngle, t);

            Vector3 currentPoint = GetPoint(angle);

            Gizmos.DrawLine(previousPoint, currentPoint);

            previousPoint = currentPoint;
        }

        // 両端の折り返し位置を表示
        Gizmos.DrawSphere(GetPoint(startAngle), 0.12f);
        Gizmos.DrawSphere(GetPoint(endAngle), 0.12f);

        // 中央位置を表示
        Gizmos.DrawWireSphere(GetPoint(0f), 0.12f);
    }

}

