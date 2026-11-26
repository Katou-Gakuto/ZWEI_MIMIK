
using System.Collections.Generic;
using UnityEngine;

[ExecuteAlways]
public class MirrorLightPathPreview : MonoBehaviour
{
    [Header("光源")]
    public Transform lightSource;

    [Header("反射する鏡（反射順に登録）")]
    public List<Transform> mirrors = new List<Transform>();

    [Header("光の到達地点")]
    public Transform goal;

    [Header("表示設定")]
    public Color pathColor = Color.yellow;
    public float rayLength = 15f;

    [Header("反射判定設定")]
    public float hitTolerance = 0.5f;

    private void OnDrawGizmos()
    {
        // 光源と最低1枚の鏡が必要
        if (lightSource == null ||
            mirrors == null ||
            mirrors.Count == 0 ||
            mirrors[0] == null)
        {
            return;
        }

        Gizmos.color = pathColor;

        // 従来と同じ表示位置
        Vector3 offset = Vector3.up * 0.6f;

        Vector3 start = lightSource.position + offset;

        // 最初の鏡の位置
        Vector3 firstHit = mirrors[0].position + offset;

        // 光源から最初の鏡への入射方向
        Vector3 incoming = firstHit - start;

        if (incoming.sqrMagnitude < 0.000001f)
        {
            return;
        }

        incoming.Normalize();

        // 光源から最初の鏡まで描画
        Gizmos.DrawLine(start, firstHit);

        // 現在の反射位置
        Vector3 currentHit = firstHit;

        // 登録された鏡を順番に処理
        for (int i = 0; i < mirrors.Count; i++)
        {
            Transform currentMirror = mirrors[i];

            // 未設定の鏡があれば処理終了
            if (currentMirror == null)
            {
                break;
            }

            // 鏡の面に垂直な方向
            Vector3 normal = currentMirror.forward;

            // 反射方向を計算
            Vector3 reflected =
                Vector3.Reflect(incoming, normal).normalized;

            // 反射地点を表示
            Gizmos.DrawSphere(currentHit, 0.15f);

            // 反射光を表示
            Gizmos.DrawRay(
                currentHit,
                reflected * rayLength
            );

            // 最後の鏡なら処理終了
            if (i + 1 >= mirrors.Count)
            {
                break;
            }

            // 次の鏡を取得
            Transform nextMirror = mirrors[i + 1];

            if (nextMirror == null)
            {
                break;
            }

            // 次の鏡の位置
            Vector3 nextHit = nextMirror.position + offset;

            Vector3 toNextMirror = nextHit - currentHit;

            // 反射光と次の鏡との距離
            float distance =
                Vector3.Cross(
                    reflected,
                    toNextMirror
                ).magnitude;

            // 次の鏡が反射光の進行方向にあるか
            bool isForward =
                Vector3.Dot(
                    reflected,
                    toNextMirror
                ) > 0f;

            // 次の鏡に反射光が届くか判定
            if (distance < hitTolerance && isForward)
            {
                // 現在の鏡から次の鏡まで描画
                Gizmos.DrawLine(currentHit, nextHit);

                // 次の鏡の入射方向を更新
                incoming = reflected;

                // 反射位置を更新
                currentHit = nextHit;
            }
            else
            {
                // 次の鏡に光が届かなければ終了
                break;
            }
        }
    }
}
