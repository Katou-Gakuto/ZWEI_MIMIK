
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
        if (lightSource == null ||
            mirror1 == null ||
            mirror2 == null)
        {
            return;
        }

        Gizmos.color = pathColor;

        // Œõ‚ÌŒo˜H‚ğ°‚æ‚è­‚µã‚É•\¦
        Vector3 offset = Vector3.up * 0.6f;

        Vector3 start = lightSource.position + offset;
        Vector3 hit1 = mirror1.position + offset;

        // ŒõŒ¹‚©‚ç‹¾‡@‚Ö‚Ì“üË•ûŒü
        Vector3 incoming1 =
            (hit1 - start).normalized;

        // ‹¾‡@‚Ì–Ê‚É‚’¼‚È•ûŒü
        Vector3 normal1 = mirror1.forward;

        // ‹¾‡@‚Ì”½Ë•ûŒü
        Vector3 reflected1 =
            Vector3.Reflect(incoming1, normal1).normalized;

        Gizmos.DrawLine(start, hit1);

        // ‹¾‡@‚©‚çL‚Ñ‚é”½ËŒõ
        Gizmos.DrawRay(
            hit1,
            reflected1 * rayLength
        );

        // ‹¾‡A‚Ö‚Ì“’B”»’èiŠÈˆÕj
        Vector3 hit2 = mirror2.position + offset;

        Vector3 toMirror2 = hit2 - hit1;

        float distance =
            Vector3.Cross(reflected1, toMirror2).magnitude;

        // ”½ËŒõ‚ª‹¾‡A‚Ì‹ß‚­‚ğ’Ê‚Á‚½ê‡
        if (distance < 0.5f &&
            Vector3.Dot(reflected1, toMirror2) > 0)
        {
            Vector3 incoming2 = reflected1;
            Vector3 normal2 = mirror2.forward;

            Vector3 reflected2 =
                Vector3.Reflect(
                    incoming2,
                    normal2
                ).normalized;

            Gizmos.DrawLine(hit1, hit2);

            Gizmos.DrawRay(
                hit2,
                reflected2 * rayLength
            );

            Gizmos.DrawSphere(hit2, 0.15f);
        }

        Gizmos.DrawSphere(hit1, 0.15f);
    }
}
