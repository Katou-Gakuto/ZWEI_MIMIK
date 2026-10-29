using UnityEngine;

[ExecuteInEditMode]
[RequireComponent(typeof(MeshFilter), typeof(MeshRenderer))]
public class LightArea : MonoBehaviour
{
    [SerializeField, Header("光のポジション")]
    private Vector3 mvPosition;

    private Vector3 mvPrePosition;

    [SerializeField, Header("見ている方向(デグリー)")]
    public float mfMainAngle;
    private float mfPreMainAngle;
    [SerializeField, Header("見ている方向の補正量(デグリー) ※基本触らなくていい")]
    public float mfPlusMainAngle = 180.0f;
    private float MainAngle
    {
        get
        {
            return /*mfMainAngle + */mfPlusMainAngle;
        }
    }
    [SerializeField, Header("見ている範囲(デグリー)")]
    public float mfAngleRange = 90.0f;

    [SerializeField, Header("光の距離")]
    private float mViewDistance = 5.0f;

    [SerializeField, Header("扇形の分割数")]
    private int mnSegmentCount = 30;

    [SerializeField, Header("Sceneビュー表示")]
    private bool mbShowGizmos = true;

    private MeshFilter mMeshFilter;
    private Mesh mSectorMesh;


    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
#if !UNITY_EDITOR
        return;
#endif
        mvPosition = this.transform.position;
        mvPrePosition = mvPosition;

        mfMainAngle = this.transform.eulerAngles.y;
        mfPreMainAngle = mfMainAngle;
    }

    // Update is called once per frame
    void Update()
    {
#if !UNITY_EDITOR
        return;
#endif
        if (Vector3.Distance(mvPosition, mvPrePosition) < 0.0001f)
        {
            mvPosition = this.transform.position;
        }
        else
        {
            this.transform.position = mvPosition;
        }
        mvPrePosition = mvPosition;

        if (Mathf.Abs(mfMainAngle - mfPreMainAngle) < 0.0001f)
        {
            mfMainAngle = this.transform.eulerAngles.y;
        }
        else
        {
            this.transform.eulerAngles = new Vector3(this.transform.eulerAngles.x, mfMainAngle, this.transform.eulerAngles.z);
        }
        mfPreMainAngle = mfMainAngle;

        CreateSectorMesh();
    }


    private void OnEnable()
    {
#if !UNITY_EDITOR
        return;
#endif
        mMeshFilter = GetComponent<MeshFilter>();

        
        {
            mSectorMesh = new Mesh();
            mSectorMesh.name = "LightAreaMesh";
            mMeshFilter.sharedMesh = mSectorMesh;
        }

        CreateSectorMesh();
    }

    private void OnDisable()
    {
#if !UNITY_EDITOR
        return;
#endif
        if (mSectorMesh != null)
        {
            if (Application.isPlaying)
            {
                Destroy(mSectorMesh);
            }
            else
            {
                DestroyImmediate(mSectorMesh);
            }

            mSectorMesh = null;
        }
    }

    private void OnValidate()
    {
#if !UNITY_EDITOR
        return;
#endif
        mfAngleRange = Mathf.Clamp(mfAngleRange, 0.0f, 360.0f);
        mViewDistance = Mathf.Max(0.0f, mViewDistance);
        mnSegmentCount = Mathf.Max(3, mnSegmentCount);

        CreateSectorMesh();
    }

    private void CreateSectorMesh()
    {
        if (mSectorMesh == null)
        {
            return;
        }

        int segmentCount = Mathf.Max(
            1,
            Mathf.CeilToInt(mnSegmentCount * mfAngleRange / 360.0f)
        );

        Vector3[] vertices = new Vector3[segmentCount + 2];
        int[] triangles = new int[segmentCount * 3];

        // 扇形の中心
        vertices[0] = Vector3.zero;

        float startAngle = MainAngle - mfAngleRange * 0.5f;

        for (int i = 0; i <= segmentCount; i++)
        {
            float angle = startAngle + mfAngleRange * i / segmentCount;
            float radian = angle * Mathf.Deg2Rad;

            vertices[i + 1] = new Vector3(
                Mathf.Sin(radian) * mViewDistance,
                0.01f,
                Mathf.Cos(radian) * mViewDistance
            );
        }

        for (int i = 0; i < segmentCount; i++)
        {
            int index = i * 3;

            triangles[index] = 0;
            triangles[index + 1] = i + 1;
            triangles[index + 2] = i + 2;
        }

        mSectorMesh.Clear();
        mSectorMesh.vertices = vertices;
        mSectorMesh.triangles = triangles;
        mSectorMesh.RecalculateNormals();
    }

    private void OnDrawGizmos()
    {
        if (!mbShowGizmos)
        {
            return;
        }

        Gizmos.color = Color.yellow;

        Vector3 center = mvPosition;
        float startAngle = MainAngle - mfAngleRange * 0.5f;

        int segmentCount = Mathf.Max(
            1,
            Mathf.CeilToInt(mnSegmentCount * mfAngleRange / 360.0f)
        );

        Vector3 previousPoint = center;

        for (int i = 0; i <= segmentCount; i++)
        {
            float angle = startAngle + mfAngleRange * i / segmentCount;
            float radian = angle * Mathf.Deg2Rad;

            Vector3 direction = new Vector3(
                Mathf.Sin(radian),
                0.0f,
                Mathf.Cos(radian)
            );

            Vector3 point = center + direction * mViewDistance;

            if (i > 0)
            {
                Gizmos.DrawLine(previousPoint, point);
            }

            previousPoint = point;
        }

        // 中心から扇形の左右端へ線を引く
        float leftAngle = startAngle * Mathf.Deg2Rad;
        float rightAngle = (MainAngle + mfAngleRange * 0.5f)
                           * Mathf.Deg2Rad;

        Vector3 leftDirection = new Vector3(
            Mathf.Sin(leftAngle), 0.0f, Mathf.Cos(leftAngle));

        Vector3 rightDirection = new Vector3(
            Mathf.Sin(rightAngle), 0.0f, Mathf.Cos(rightAngle));

        Gizmos.DrawLine(center, center + leftDirection * mViewDistance);
        Gizmos.DrawLine(center, center + rightDirection * mViewDistance);
    }
}
