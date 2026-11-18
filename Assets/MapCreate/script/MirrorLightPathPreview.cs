
using UnityEngine;

[ExecuteAlways]
public class MirrorLightPathPreview : MonoBehaviour
{
    [Header("ŒõŒ¹")]
    public Transform lightSource;

    [Header("”½Ë‚·‚é‹¾")]
    public Transform mirror1;
    public Transform mirror2;

    [Header("Œõ‚Ì“’B’n“_")]
    public Transform goal;

    [Header("•\¦İ’è")]
    public Color pathColor = Color.yellow;
    public float rayLength = 15f;

    private void OnDrawGizmos()
    {
        // ŒõŒ¹‚Æ‹¾‡@‚Í•K{
        if (lightSource == null || mirror1 == null)
        {
            return;
        }

        Gizmos.color = pathColor;

        // ]—ˆ‚Æ“¯‚¶•\¦ˆÊ’u
        Vector3 offset = Vector3.up * 0.6f;

        Vector3 start = lightSource.position + offset;
        Vector3 hit1 = mirror1.position + offset;

        // ŒõŒ¹‚©‚ç‹¾‡@‚Ö‚Ì“üË•ûŒü
        Vector3 incoming1 = hit1 - start;

        if (incoming1.sqrMagnitude < 0.000001f)
        {
            return;
        }

        incoming1.Normalize();

        // ‹¾‡@‚Ì–Ê‚É‚’¼‚È•ûŒü
        Vector3 normal1 = mirror1.forward;

        // ‹¾‡@‚Å”½Ë‚µ‚½•ûŒü
        Vector3 reflected1 =
            Vector3.Reflect(incoming1, normal1).normalized;

        // ŒõŒ¹‚©‚ç‹¾‡@
        Gizmos.DrawLine(start, hit1);

        // ‹¾‡@‚Ì”½ËŒõ
        Gizmos.DrawRay(
            hit1,
            reflected1 * rayLength
        );

        Gizmos.DrawSphere(hit1, 0.15f);

        // ‹¾‚ª1–‡‚È‚ç‚±‚±‚ÅI—¹
        if (mirror2 == null)
        {
            return;
        }

        // ˆÈ‰º‚Í]—ˆ‚Ì‹¾2–‡‚Ìˆ—
        Vector3 hit2 = mirror2.position + offset;
        Vector3 toMirror2 = hit2 - hit1;

        float distance =
            Vector3.Cross(reflected1, toMirror2).magnitude;

        // ‹¾‡A‚ª”½ËŒõ‚Ìis•ûŒü‚É‚ ‚é‚©Šm”F
        bool isForward =
            Vector3.Dot(reflected1, toMirror2) > 0f;

        // ‹¾‡A‚Ì‹ß‚­‚ğŒõ‚ª’Ê‚éê‡
        if (distance < 0.5f && isForward)
        {
            Vector3 incoming2 = reflected1;
            Vector3 normal2 = mirror2.forward;

            Vector3 reflected2 =
                Vector3.Reflect(
                    incoming2,
                    normal2
                ).normalized;

            // ‹¾‡@‚©‚ç‹¾‡A
            Gizmos.DrawLine(hit1, hit2);

            // ‹¾‡A‚©‚ç‚Ì”½ËŒõ
            Gizmos.DrawRay(
                hit2,
                reflected2 * rayLength
            );

            Gizmos.DrawSphere(hit2, 0.15f);
        }
    }
}
