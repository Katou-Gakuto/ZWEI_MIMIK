using System.Collections.Generic;
using System.IO;
using UnityEditor;
using UnityEngine;
using UnityEngine.SceneManagement;
using static UnityEngine.GraphicsBuffer;

/// <summary>
/// Editor上でのみ動作するマップ作成用class
/// </summary>
[ExecuteInEditMode]
public class SetMapDrawPos : MonoBehaviour
{
    // 抽出処理種類
    public enum EXTRACTION_PROCESS_MODE
    {
        FULL_NAME,
        START_NAME,
        TAG,
        LAYER_NAME,
        LAYER_NUMBER
    }

    // ファイル出力時の名前種類
    enum FILE_OUT_PUT_NAME_MODE
    {
        NAME,       // 名前
        TAG,        // タグ
        LAYER,     // レイヤー
    }

    // ファイル出力処理種類
    public enum FILE_OUTPUT_PROCESS_MODE
    {
        OBJECT_NOT_CORRECTION,  // そのままの値
        STAGE_CORRECTION,       // DXライブラリの描画ベクトルに変換した値
        STAGE_DRAW_CORRECTION   // DXライブラリの描画ベクトルに変換した上で画面比でにした値
    }

    // ファイル出力処理2座標種類
    public enum FILE_OUTPUT_PROCESS_2D_POS_MODE
    {
        NORMALIZE,      // 左上を0～1とした座標
        COORDINATE,     // 左上を起点とした座標
        MAGNIFICATION,  // 左上を0～1とし、指定の倍率で変更しもの座標
    }

    // ファイル出力処理2大きさ種類
    public enum FILE_OUTPUT_PROCESS_2D_SIZE_MODE
    {
        ORIGINAL,                         // そのまま
        FIXED_RATIO,                      // 固定UV変換
        EDITOR_RATIO,                     // エディターで設定した割合
        FIXED_RATIO_EDITOR_SCALE,         // 固定UV変換にエディターで設定した倍率を適用
        EDITOR_RATIO_EDITOR_SCALE         // エディターで設定した割合にエディターで設定した倍率を適用
    }

    // ステージサイズ設定種類
    public enum STAGE_SIZE_SET_MODE
    {
        NONE,
        ONE_OBJECT,
        TWO_OBJECT
    }

    /// <summary>
    /// オブジェクト1つ分の情報
    /// </summary>
    [System.Serializable]
    public class OneObjectDatas
    {
        /// <summary>
        /// ポジション
        /// </summary>
        public Vector2 MyPos;
        /// <summary>
        /// サイズ
        /// </summary>
        public Vector2 MySize;

        public OneObjectDatas(Vector2 pos, Vector2 size)
        {
            MyPos = pos;
            MySize = size;
        }
        public static OneObjectDatas operator +(OneObjectDatas src, OneObjectDatas dst)
        {
            return new OneObjectDatas(src.MyPos + dst.MyPos, src.MySize + dst.MySize);
        }
    }

    // ============================================================
    // 管理対象データ
    // ============================================================
    [System.Serializable]
    public class ObjectData
    {
        public GameObject TargetObject;

        public OneObjectDatas OutPutDatas;
    }

    [SerializeField, Header(
        "【簡易解説】\n" +
        "① Unity上でマップを作成\n" +
        "② 出力するオブジェクトの条件を設定\n" +
        "③ UIまたは3Dの座標基準を選択\n" +
        "④ 座標・サイズの出力方法を設定\n" +
        "⑤ 「マップ設定トリガー」をONにして出力\n" +
        "出力されたマップデータをDXライブラリ側で使用します。\n" +
        "\n" +
        "\n" +
        "【ファイル出力名】\nオブジェクトの名前・タグ・レイヤーのどれをファイル名として使用するかを設定します")]
    [EnumTooltip(
    "オブジェクトの名前をファイル名として出力します。",
    "オブジェクトのタグをファイル名として出力します。",
    "オブジェクトのレイヤー名をファイル名として出力します。")]
    private FILE_OUT_PUT_NAME_MODE FileOutPutNameMode;
    [SerializeField, Header("【マップ出力】\nこのボタンをONにすると、現在の設定でマップデータを出力します")]
    private bool SetMapObjectTrigger;
    [SerializeField, Header("【確認用】\nマップデータを出力した回数です")]
    private int SetMapObjectTriggerCount = 0;


    [SerializeField, Header("【座標基準】\nUIを基準にするか、3D空間を基準にするかを選択します")]
    private bool UIFlag = true;

    [SerializeField, Header("【3D出力：座標・サイズ】\n3D空間のオブジェクトを、どの基準の値で出力するかを設定します")]
    [EnumTooltip(
    "オブジェクト自身の座標・サイズをそのまま出力します。",
    "ステージ左上を基準とした座標に変換して出力します。",
    "ステージ左上を基準とした座標を、ステージサイズに対する割合へ変換して出力します。")]
    private FILE_OUTPUT_PROCESS_MODE FileOutputProcessMode;

    [SerializeField, Header("【UI出力：座標】\nUIの座標をどの形式で出力するかを設定します")]
    [EnumTooltip(
    "Canvasの左上を0、右下を1とした0～1の座標として出力します。",
    "Canvasの左上を0として、UIの座標をそのまま出力します。",
    "0～1に正規化した座標へ指定した倍率を適用して出力します。")]
    private FILE_OUTPUT_PROCESS_2D_POS_MODE FileOutputProcess2DPosMode;
    [SerializeField, Header("【UI出力：サイズ】\nUIの大きさをどの形式で出力するかを設定します")]
    [EnumTooltip(
    "UIのサイズをそのまま出力します。",
    "Canvasのサイズを基準にUV変換してサイズを出力します。",
    "エディターで設定したUV変換値を使用してサイズを出力します。",
    "Canvasのサイズを基準にUV変換した値に、エディターで設定した倍率を適用して出力します。",
    "エディターで設定したUV変換値に、エディターで設定した倍率を適用して出力します。")]
    private FILE_OUTPUT_PROCESS_2D_SIZE_MODE FileOutputProcess2DSizeMode;

    [SerializeField, Header("【UI出力：座標倍率】\nUI座標を0～1に変換した後、この倍率を適用します")]
    private Vector2 OutPutMagnificationPos = new Vector2(1.0f, 1.0f);

    /// <summary>
    /// UIファイル出力(サイズ)固定割合
    /// </summary>
    private Vector2 OutPutFixedRatio = new Vector2(1900.0f, 1070.0f);
    [SerializeField, Header("【UI出力：サイズ基準】\nサイズをUV変換するときの基準となる大きさを設定します\n")]
    private Vector2 OutPutRatio = new Vector2(1.0f, 1.0f);
    [SerializeField, Header("【UI出力：サイズ倍率】\nUIサイズに適用する倍率を設定します")]
    private Vector2 OutPutMagnificationSize = new Vector2(1.0f, 1.0f);

    [SerializeField, Header("管理データ")]
    private List<ObjectData> ObjectDatas;

    [SerializeField, Header("【マップ対象：抽出方法】\nどの条件のオブジェクトをマップデータとして出力するかを設定します")]
    [EnumTooltip(
    "指定した名前と完全に一致するオブジェクトを抽出します。",
    "指定した文字列から始まる名前のオブジェクトを抽出します。",
    "指定したタグが設定されたオブジェクトを抽出します。",
    "指定したレイヤー名のオブジェクトを抽出します。",
    "指定したレイヤー番号のオブジェクトを抽出します。")]
    private EXTRACTION_PROCESS_MODE ExtractionProcessMode;
    [SerializeField, Header("【マップ対象：名前】\n名前を条件にする場合、対象となる名前を設定します")]
    private string[] OutPutObjectNames;
    [SerializeField, Header("【マップ対象：タグ】\nタグを条件にする場合、対象となるタグを設定します")]
    private string[] OutPutTags;
    [SerializeField, Header("【マップ対象：レイヤー名】\nレイヤー名を条件にする場合、対象となるレイヤーを設定します")]
    private string[] OutPutLayerNames;
    [SerializeField, Header("【マップ対象：レイヤー番号】\nレイヤー番号を条件にする場合、対象となる番号を設定します")]
    private int[] OutPutLayerNumbers;

    [SerializeField, Header("【3Dステージ設定：方法】\n3Dマップの範囲をどのように設定するかを選択します")]
    [EnumTooltip(
    "ステージサイズを直接指定します。",
    "1つのオブジェクトを使用してステージの位置と大きさを指定します。",
    "左上と右下の2つのオブジェクトを使用してステージ範囲を指定します。")]
    private STAGE_SIZE_SET_MODE StageSetMode = STAGE_SIZE_SET_MODE.NONE;
    [SerializeField, Header("【3Dステージ設定：位置】\nステージの中心位置を設定します")]
    private Vector2 StagePos = new Vector2(1.0f, 1.0f);
    [SerializeField, Header("【3Dステージ設定：サイズ】\nステージ全体の大きさを設定します")]
    private Vector2 StageSize = new Vector2(1.0f, 1.0f);
    [SerializeField, Header("【3Dステージ設定：範囲指定オブジェクト】\n1つのオブジェクトをステージの大きさとして使用します")]
    private GameObject SetOneObjectStage_GameObject;
    [SerializeField, Header("【3Dステージ設定：左上】\nステージ範囲の左上を指定します")]
    private GameObject SetTwoObjectStage_GameObjectLeftUp;
    [SerializeField, Header("【3Dステージ設定：右下】\nステージ範囲の右下を指定します")]
    private GameObject SetTwoObjectStage_GameObjectRightDown;

    /// <summary>
    /// ファイル出力用ステージサイズ
    /// </summary>
    private Vector2 FileOutStageSize;
    [SerializeField, Header("ステージ情報左上の座標 ※見る専用")]
    private Vector2 StageLeftUp;
    [SerializeField, Header("ステージ情報真ん中の座標 ※見る専用")]
    private Vector2 StageMiddle;
    [SerializeField, Header("ステージ情報右下の座標 ※見る専用")]
    private Vector2 StageRightDown;

    [SerializeField, Header("【出力ファイル名】\nONにすると出力回数をファイル名に追加し、別ファイルとして保存します")]
    private bool FileNamePlusCountFlag = false;

    private void Start()
    {
        if (Application.isPlaying)
        {
            return;
        }

        OutPutFixedRatio = new Vector2(1900.0f, 1070.0f);
    }


    private void Update()
    {
        if (Application.isPlaying)
        {
            return;
        }

        SetStageSize();

        SetMapData();
    }


    private void OnValidate()
    {
        if (Application.isPlaying)
        {
            return;
        }


        SetMapData();
    }

    // マップ情報設定(ファイル出力もやってる)
    private void SetMapData()
    {
        if (!SetMapObjectTrigger)
        {
            return;
        }
        SetMapObjectTrigger = false;
        SetMapObjectTriggerCount++;

        ObjectDatas.Clear();

        // マップ情報取得排出処理作成する

        // 現在開いているSceneを取得
        Scene currentScene = SceneManager.GetActiveScene();

        // Scene直下のGameObjectを取得
        GameObject[] rootObjects = currentScene.GetRootGameObjects();

        // 全GameObjectを調査
        foreach (GameObject rootObject in rootObjects)
        {
            SearchGameObject(rootObject);
        }

        // ファイルとして出力
        OutputMapDataToFile();
    }


    /// <summary>
    /// GameObjectを再帰的に調査する
    /// </summary>
    private void SearchGameObject(GameObject target)
    {
        // 名前が抽出対象か確認
        if (IsOutputTarget(target))
        {
            ObjectData data = new ObjectData();

            data.TargetObject = target;

            // ここで座標・サイズを取得する
            data.OutPutDatas = new OneObjectDatas(new Vector2(target.transform.position.x, target.transform.position.z), new Vector2(target.transform.localScale.x, target.transform.localScale.z));

            ObjectDatas.Add(data);
        }

        // 子オブジェクトを調査
        foreach (Transform child in target.transform)
        {
            SearchGameObject(child.gameObject);
        }
    }


    /// <summary>
    /// 抽出対象の名前か確認
    /// </summary>
    private bool IsOutputTarget(GameObject target)
    {
        switch (ExtractionProcessMode)
        {
        case EXTRACTION_PROCESS_MODE.FULL_NAME:
            if (OutPutObjectNames == null)
            {
                return false;
            }

            foreach (string targetName in OutPutObjectNames)
            {
                if (target.name == targetName)
                {
                    return true;
                }
            }
            break;

        case EXTRACTION_PROCESS_MODE.START_NAME:
            if (OutPutObjectNames == null)
            {
                return false;
            }

            foreach (string targetName in OutPutObjectNames)
            {
                if (target.name.StartsWith(targetName))
                {
                    return true;
                }
            }
            break;

        case EXTRACTION_PROCESS_MODE.TAG:
            if (OutPutTags == null)
            {
                return false;
            }

            foreach (string targetTag in OutPutTags)
            {
                if (target.CompareTag(targetTag))
                {
                    return true;
                }
            }
            break;

        case EXTRACTION_PROCESS_MODE.LAYER_NAME:
        { 
            if (OutPutLayerNames == null)
            {
                return false;
            }

            string layerName = LayerMask.LayerToName(target.layer);
            foreach (string targetLayer in OutPutLayerNames)
            {
                if (layerName == targetLayer)
                {
                    return true;
                }
            }
        }
            break;

        case EXTRACTION_PROCESS_MODE.LAYER_NUMBER:
            if (OutPutLayerNumbers == null)
            {
                return false;
            }

            foreach (int targetLayer in OutPutLayerNumbers)
            {
                if (target.layer == targetLayer)
                {
                    return true;
                }
            }
            break;
        }

        return false;
    }


    /// <summary>
    /// マップ情報を出力
    /// </summary>
    private void OutputMapDataToFile()
    {
        string mapDataString = "";

        if (UIFlag)
        {
            mapDataString = Output2DMapDataToString();
        }
        else
        {
            mapDataString = Get3DObjectOutputText();
        }

        if (0 < mapDataString.Length)
        {
            string sceneName = SceneManager.GetActiveScene().name;
            string openFileName = "";
            if (FileNamePlusCountFlag)
            {
                openFileName = "MapData_" + sceneName + "_" + SetMapObjectTriggerCount + ".txt";
            }
            else
            {
                openFileName = "MapData" + sceneName + ".txt";
            }
            string path = Path.Combine(Application.dataPath, openFileName);
            File.WriteAllText(path, mapDataString);
            AssetDatabase.Refresh();
        }

    }

    /// <summary>
    /// UI基準でマップ情報を出力する文字列を作成
    /// Canvasの左上を座標の原点とする
    /// </summary>
    private string Output2DMapDataToString()
    {
        string mapDataString = "";

        foreach (ObjectData objectData in ObjectDatas)
        {
            RectTransform targetRect =
                objectData.TargetObject.GetComponent<RectTransform>();

            Canvas canvas =
                objectData.TargetObject.GetComponentInParent<Canvas>();

            if ((targetRect == null) || (canvas == null))
            {
                continue;
            }

            RectTransform canvasRect =
                canvas.GetComponent<RectTransform>();

            if (canvasRect == null)
            {
                continue;
            }

            Vector3[] canvasCorners = new Vector3[4];
            Vector3[] targetCorners = new Vector3[4];

            canvasRect.GetWorldCorners(canvasCorners);
            targetRect.GetWorldCorners(targetCorners);

            // Canvas
            // 0 = 左下
            // 1 = 左上
            // 2 = 右上
            // 3 = 右下

            Vector3 canvasLeftUp = canvasCorners[1];

            // UIの中心座標
            Vector3 targetCenter =
                (targetCorners[0] + targetCorners[2]) * 0.5f;

            // Canvas左上からの距離
            float posX =
                targetCenter.x - canvasLeftUp.x;

            float posY =
                canvasLeftUp.y - targetCenter.y;

            // UIサイズ
            float sizeX =
                Vector3.Distance(targetCorners[0], targetCorners[3]);

            float sizeY =
                Vector3.Distance(targetCorners[0], targetCorners[1]);

            // Canvasサイズ
            float canvasWidth =
                Vector3.Distance(canvasCorners[0], canvasCorners[3]);

            float canvasHeight =
                Vector3.Distance(canvasCorners[0], canvasCorners[1]);

            mapDataString += GetFileOutPutName(objectData.TargetObject);
            mapDataString += "\n";


            // ポジションテキスト化
            switch (FileOutputProcess2DPosMode)
            {
                case FILE_OUTPUT_PROCESS_2D_POS_MODE.NORMALIZE:
                    mapDataString +=
                        "posX:" + (posX / canvasWidth) +
                        " posY:" + (posY / canvasHeight) +
                        "\n";
                    break;

                case FILE_OUTPUT_PROCESS_2D_POS_MODE.COORDINATE:
                    mapDataString +=
                        "posX:" + posX +
                        " posY:" + posY +
                        "\n";
                    break;

                case FILE_OUTPUT_PROCESS_2D_POS_MODE.MAGNIFICATION:
                    mapDataString +=
                        "posX:" + ((posX / canvasWidth) * OutPutMagnificationPos.x) +
                        " posY:" + ((posY / canvasHeight) * OutPutMagnificationPos.y) +
                        "\n";
                    break;
            }

            // サイズテキスト化
            switch (FileOutputProcess2DSizeMode)
            {
                case FILE_OUTPUT_PROCESS_2D_SIZE_MODE.ORIGINAL:
                    mapDataString +=
                        "sizeX:" + sizeX +
                        " sizeY:" + sizeY;
                    break;

                case FILE_OUTPUT_PROCESS_2D_SIZE_MODE.FIXED_RATIO:
                    mapDataString +=
                        "sizeX:" + (sizeX / OutPutFixedRatio.x) +
                        " sizeY:" + (sizeY / OutPutFixedRatio.y);
                    break;

                case FILE_OUTPUT_PROCESS_2D_SIZE_MODE.EDITOR_RATIO:
                    mapDataString +=
                        "sizeX:" + (sizeX / OutPutRatio.x) +
                        " sizeY:" + (sizeY / OutPutRatio.y);
                    break;

                case FILE_OUTPUT_PROCESS_2D_SIZE_MODE.FIXED_RATIO_EDITOR_SCALE:
                    mapDataString +=
                        "sizeX:" + ((sizeX / OutPutFixedRatio.x) * OutPutMagnificationSize.x) +
                        " sizeY:" + ((sizeY / OutPutFixedRatio.y) * OutPutMagnificationSize.y);
                    break;

                case FILE_OUTPUT_PROCESS_2D_SIZE_MODE.EDITOR_RATIO_EDITOR_SCALE:
                    mapDataString +=
                        "sizeX:" + ((sizeX / OutPutRatio.x) * OutPutMagnificationSize.x) +
                        " sizeY:" + ((sizeY / OutPutRatio.y) * OutPutMagnificationSize.y);
                    break;
            }

            mapDataString += "\n";
            mapDataString += "\n";
        }

        return mapDataString;
    }

    /// <summary>
    /// 3Dオブジェクト基準で出力するテキストを取得
    /// </summary>
    /// <returns>出力するテキスト</returns>
    private string Get3DObjectOutputText()
    {
        string mapDataString = "";
        foreach (ObjectData objectData in ObjectDatas)
        {
            mapDataString += GetFileOutPutName(objectData.TargetObject);
            mapDataString += "\n";
            switch (FileOutputProcessMode)
            {
                case FILE_OUTPUT_PROCESS_MODE.OBJECT_NOT_CORRECTION:
                    mapDataString += (
                        "posX:"  + objectData.OutPutDatas.MyPos.x  +
                        " posY:"  + (-objectData.OutPutDatas.MyPos.y) +
                        "\n" +
                        "sizeX:" + objectData.OutPutDatas.MySize.x +
                        " sizeY:" + objectData.OutPutDatas.MySize.y
                        );
                    break;

                case FILE_OUTPUT_PROCESS_MODE.STAGE_CORRECTION:
                    mapDataString += (
                        "posX:"  + (objectData.OutPutDatas.MyPos.x - StageLeftUp.x)  +
                        " posY:"  + (StageLeftUp.y - objectData.OutPutDatas.MyPos.y) +
                        "\n" +
                        "sizeX:" + objectData.OutPutDatas.MySize.x +
                        " sizeY:" + objectData.OutPutDatas.MySize.y
                        );
                    break;

                case FILE_OUTPUT_PROCESS_MODE.STAGE_DRAW_CORRECTION:
                    mapDataString += (
                        "posX:"  + ((objectData.OutPutDatas.MyPos.x - StageLeftUp.x) / FileOutStageSize.x)  +
                        " posY:"  + ((StageLeftUp.y - objectData.OutPutDatas.MyPos.y) / FileOutStageSize.y) +
                        "\n" +
                        "sizeX:" + (objectData.OutPutDatas.MySize.x / FileOutStageSize.x) +
                        " sizeY:" + (objectData.OutPutDatas.MySize.y / FileOutStageSize.y)
                        );
                    break;
            }
            mapDataString += "\n\n";
        }
        return mapDataString;
    }

    // ステージのサイズ情報設定
    private void SetStageSize()
    {
        if (UIFlag)
        {
            if (SetOneObjectStage_GameObject != null)
            {
                SetOneObjectStage_GameObject.SetActive(false);
            }
            if ((SetTwoObjectStage_GameObjectLeftUp != null) && (SetTwoObjectStage_GameObjectRightDown != null))
            {
                SetTwoObjectStage_GameObjectLeftUp.SetActive(false);
                SetTwoObjectStage_GameObjectRightDown.SetActive(false);
            }

            return;
        }

        switch (StageSetMode)
        {
        case STAGE_SIZE_SET_MODE.NONE:
        {
            // 使わないオブジェクトを見えないようにする
            {
                if (SetOneObjectStage_GameObject != null)
                {
                    SetOneObjectStage_GameObject.SetActive(false);
                }
                if ((SetTwoObjectStage_GameObjectLeftUp != null) && (SetTwoObjectStage_GameObjectRightDown != null))
                {
                    SetTwoObjectStage_GameObjectLeftUp.SetActive(false);
                    SetTwoObjectStage_GameObjectRightDown.SetActive(false);
                }
            }
            // サイズがマイナスか確認
            {
                if (StageSize.x <= 0.0f)
                {
                    StageSize.x = 1.0f;
                }
                if (StageSize.y <= 0.0f)
                {
                    StageSize.y = 1.0f;
                }
            }
            Vector2 halfSize = StageSize * 0.5f;
            // ポジション&サイズ情報設定
            { 
                FileOutStageSize = StageSize;
                StageLeftUp = new Vector2(StagePos.x - halfSize.x, StagePos.y + halfSize.y);
                StageMiddle = StagePos;
                StageRightDown = new Vector2(StagePos.x + halfSize.x, StagePos.y - halfSize.y);
            }
        }
            break;

        case STAGE_SIZE_SET_MODE.ONE_OBJECT:
        {
            // オブジェクトが設定してあるかを確認
            {
                if (SetOneObjectStage_GameObject == null)
                {
                    SetOneObjectStage_GameObject = GameObject.CreatePrimitive(PrimitiveType.Cube);

                    SetOneObjectStage_GameObject.name = "MyCube_OneObjectStage";
                    SetOneObjectStage_GameObject.transform.SetParent(this.gameObject.transform);

                    SetOneObjectStage_GameObject.transform.localPosition = Vector3.zero;
                    SetOneObjectStage_GameObject.transform.localScale = new Vector3(1, 1, 1);
                }
            }
            // オブジェクトの見える見えない操作
            {
                if ((SetTwoObjectStage_GameObjectLeftUp != null) && (SetTwoObjectStage_GameObjectRightDown != null))
                {
                    SetTwoObjectStage_GameObjectLeftUp.SetActive(false);
                    SetTwoObjectStage_GameObjectRightDown.SetActive(false);
                }
                if (SetOneObjectStage_GameObject != null)
                {
                    SetOneObjectStage_GameObject.SetActive(true);
                }
            }
            Vector2 objectScale = SetOneObjectStage_GameObject.transform.localScale;
            // サイズがマイナスか確認
            {
                if (objectScale.x <= 0.0f)
                {
                    objectScale =
                                SetOneObjectStage_GameObject.transform.localScale =
                                                                                    new Vector3(1.0f, objectScale.y, 1.0f);
                }
                if (objectScale.y <= 0.0f)
                {
                    objectScale = 
                                 SetOneObjectStage_GameObject.transform.localScale =
                                                                                    new Vector3(objectScale.x, 1.0f, 1.0f);
                }
            }
            Vector2 halfSize = objectScale * 0.5f;
            Vector2 objectPos = SetOneObjectStage_GameObject.transform.localPosition;
            // ポジション&サイズ情報設定
            {
                FileOutStageSize = objectScale;
                StageLeftUp = new Vector2(
                    objectPos.x - halfSize.x,
                    objectPos.y + halfSize.y);
                StageMiddle = objectPos;
                    StageRightDown = new Vector2(
                    objectPos.x + halfSize.x,
                    objectPos.y - halfSize.y);
            }
        }
            break;

        case STAGE_SIZE_SET_MODE.TWO_OBJECT:
        {
            // オブジェクトが設定してあるかを確認
            {
                if (SetTwoObjectStage_GameObjectLeftUp == null)
                {
                    SetTwoObjectStage_GameObjectLeftUp = GameObject.CreatePrimitive(PrimitiveType.Cube);

                    SetTwoObjectStage_GameObjectLeftUp.name = "MyCube_TwoObjectStage_LeftUp";
                    SetTwoObjectStage_GameObjectLeftUp.transform.SetParent(this.gameObject.transform);

                    SetTwoObjectStage_GameObjectLeftUp.transform.localPosition = Vector3.zero;
                    SetTwoObjectStage_GameObjectLeftUp.transform.localScale = new Vector3(1, 1, 1);
                }
                if (SetTwoObjectStage_GameObjectRightDown == null)
                {
                    SetTwoObjectStage_GameObjectRightDown = GameObject.CreatePrimitive(PrimitiveType.Cube);

                    SetTwoObjectStage_GameObjectRightDown.name = "MyCube_TwoObjectStage_RightDown";
                    SetTwoObjectStage_GameObjectRightDown.transform.SetParent(this.gameObject.transform);

                    SetTwoObjectStage_GameObjectRightDown.transform.localPosition = new Vector3(1, -1, 0);
                    SetTwoObjectStage_GameObjectRightDown.transform.localScale = new Vector3(1, 1, 1);
                }
            }
            // オブジェクトの見える見えない操作
            {
                if (SetOneObjectStage_GameObject != null)
                {
                    SetOneObjectStage_GameObject.SetActive(false);
                }
                if ((SetTwoObjectStage_GameObjectLeftUp != null) && (SetTwoObjectStage_GameObjectRightDown != null))
                {
                    SetTwoObjectStage_GameObjectLeftUp.SetActive(true);
                    SetTwoObjectStage_GameObjectRightDown.SetActive(true);
                }
            }
            Vector2 objectLeftUpPos = SetTwoObjectStage_GameObjectLeftUp.transform.localPosition;
            Vector2 objectRightDownPos = SetTwoObjectStage_GameObjectRightDown.transform.localPosition;
            // オブジェクトの位置関係が正しいか確認
            {
                if ((objectRightDownPos.x - objectLeftUpPos.x) <= 0.0f)
                {
                    objectRightDownPos = 
                                        SetTwoObjectStage_GameObjectRightDown.transform.localPosition =
                                                                                                        new Vector3(objectLeftUpPos.x + 1.0f, objectRightDownPos.y, 0.0f);
                }
                if ((objectLeftUpPos.y - objectRightDownPos.y) <= 0.0f)
                {
                    objectRightDownPos = 
                                        SetTwoObjectStage_GameObjectRightDown.transform.localPosition =
                                                                                                        new Vector3(objectRightDownPos.x, objectLeftUpPos.y - 1.0f, 0.0f);
                }
            }
            // ポジション&サイズ情報設定
            {
                FileOutStageSize = new Vector2(
                    objectRightDownPos.x - objectLeftUpPos.x,
                    objectLeftUpPos.y - objectRightDownPos.y);
                StageLeftUp = objectLeftUpPos;
                StageMiddle = objectLeftUpPos + ((objectRightDownPos - objectLeftUpPos) * 0.5f);
                StageRightDown = objectRightDownPos;
            }
        }
            break;
        }
    }

    /// <summary>
    /// 出力するファイル名を取得
    /// </summary>
    private string GetFileOutPutName(GameObject target)
    {
        string outPutName = "";
        switch (FileOutPutNameMode)
        {
            case FILE_OUT_PUT_NAME_MODE.NAME:
                outPutName = target.name;
                break;
            case FILE_OUT_PUT_NAME_MODE.TAG:
                outPutName = target.tag;
                break;
            case FILE_OUT_PUT_NAME_MODE.LAYER:
                outPutName = LayerMask.LayerToName(target.layer);
                break;
        }
        return outPutName;
    }
}