using UnityEditor;
using UnityEngine;

[CustomEditor(typeof(SetMapDrawPos))]
public class SetMapDrawPosEditor : Editor
{
    private bool UIFlag;

    public override void OnInspectorGUI()
    {
        serializedObject.Update();

        SerializedProperty iterator = serializedObject.GetIterator();

        bool enterChildren = true;
        bool letterSpacingFlag = false;

        SerializedProperty mode =
            serializedObject.FindProperty("UIFlag");
        UIFlag =
            mode.boolValue;

        while (iterator.NextVisible(enterChildren))
        {
            enterChildren = false;

            if (IsExtractionProcessDraw(iterator, ref letterSpacingFlag))
            {
                continue;
            }

            if (IsStageSizeModeDraw(iterator, ref letterSpacingFlag))
            {
                continue;
            }

            if (IsUIModeDraw(iterator, ref letterSpacingFlag))
            {
                continue;
            }

            if (IsUIFlagDraw(iterator))
            {
                continue;
            }

            EditorGUILayout.PropertyField(iterator, true);

            if (letterSpacingFlag)
            {
                EditorGUILayout.Space(20);
                letterSpacingFlag = false;
            }
        }

        serializedObject.ApplyModifiedProperties();
    }

    private bool IsExtractionProcessDraw(SerializedProperty iterator, ref bool letterSpacingFlag)
    {
        // OutPutObjectNamesÇæÇØì¡éÍèàóù
        if (iterator.name == "OutPutObjectNames")
        {
            SerializedProperty mode =
                serializedObject.FindProperty("ExtractionProcessMode");

            var extractionMode =
                (SetMapDrawPos.EXTRACTION_PROCESS_MODE)
                mode.enumValueIndex;

            if (extractionMode ==
                    SetMapDrawPos.EXTRACTION_PROCESS_MODE.TAG ||
                extractionMode ==
                    SetMapDrawPos.EXTRACTION_PROCESS_MODE.LAYER_NAME ||
                extractionMode ==
                    SetMapDrawPos.EXTRACTION_PROCESS_MODE.LAYER_NUMBER)
            {
                return true;
            }
            letterSpacingFlag = true;
        }
        // OutPutTagÇæÇØì¡éÍèàóù
        if (iterator.name == "OutPutTags")
        {
            SerializedProperty mode =
                serializedObject.FindProperty("ExtractionProcessMode");

            var extractionMode =
                (SetMapDrawPos.EXTRACTION_PROCESS_MODE)
                mode.enumValueIndex;

            if (extractionMode ==
                    SetMapDrawPos.EXTRACTION_PROCESS_MODE.FULL_NAME ||
                extractionMode ==
                    SetMapDrawPos.EXTRACTION_PROCESS_MODE.START_NAME ||
                extractionMode ==
                    SetMapDrawPos.EXTRACTION_PROCESS_MODE.LAYER_NAME ||
                extractionMode ==
                    SetMapDrawPos.EXTRACTION_PROCESS_MODE.LAYER_NUMBER)
            {
                return true;
            }
            letterSpacingFlag = true;
        }
        // OutPutLayerNamesÇæÇØì¡éÍèàóù
        if (iterator.name == "OutPutLayerNames")
        {
            SerializedProperty mode =
                serializedObject.FindProperty("ExtractionProcessMode");

            var extractionMode =
                (SetMapDrawPos.EXTRACTION_PROCESS_MODE)
                mode.enumValueIndex;

            if (extractionMode ==
                    SetMapDrawPos.EXTRACTION_PROCESS_MODE.FULL_NAME ||
                extractionMode ==
                    SetMapDrawPos.EXTRACTION_PROCESS_MODE.START_NAME ||
                extractionMode ==
                    SetMapDrawPos.EXTRACTION_PROCESS_MODE.TAG ||
                extractionMode ==
                    SetMapDrawPos.EXTRACTION_PROCESS_MODE.LAYER_NUMBER)
            {
                return true;
            }
            letterSpacingFlag = true;
        }
        // OutPutLayerNumbersÇæÇØì¡éÍèàóù
        if (iterator.name == "OutPutLayerNumbers")
        {
            SerializedProperty mode =
                serializedObject.FindProperty("ExtractionProcessMode");

            var extractionMode =
                (SetMapDrawPos.EXTRACTION_PROCESS_MODE)
                mode.enumValueIndex;

            if (extractionMode ==
                    SetMapDrawPos.EXTRACTION_PROCESS_MODE.FULL_NAME ||
                extractionMode ==
                    SetMapDrawPos.EXTRACTION_PROCESS_MODE.START_NAME ||
                extractionMode ==
                    SetMapDrawPos.EXTRACTION_PROCESS_MODE.TAG ||
                extractionMode ==
                    SetMapDrawPos.EXTRACTION_PROCESS_MODE.LAYER_NAME)
            {
                return true;
            }
            letterSpacingFlag = true;
        }

        return false;
    }

    private bool IsStageSizeModeDraw(SerializedProperty iterator, ref bool letterSpacingFlag)
    {
        // StagePosÇæÇØì¡éÍèàóù
        if (iterator.name == "StagePos")
        {
            if (UIFlag)
            {
                return true;
            }

            SerializedProperty mode =
                serializedObject.FindProperty("StageSetMode");

            var extractionMode =
                (SetMapDrawPos.STAGE_SIZE_SET_MODE)
                mode.enumValueIndex;

            if (extractionMode ==
                    SetMapDrawPos.STAGE_SIZE_SET_MODE.ONE_OBJECT ||
                extractionMode ==
                    SetMapDrawPos.STAGE_SIZE_SET_MODE.TWO_OBJECT)
            {
                return true;
            }
        }
        // StageSizeÇæÇØì¡éÍèàóù
        if (iterator.name == "StageSize")
        {
            if (UIFlag)
            {
                return true;
            }

            SerializedProperty mode =
                serializedObject.FindProperty("StageSetMode");

            var extractionMode =
                (SetMapDrawPos.STAGE_SIZE_SET_MODE)
                mode.enumValueIndex;

            if (extractionMode ==
                    SetMapDrawPos.STAGE_SIZE_SET_MODE.ONE_OBJECT ||
                extractionMode ==
                    SetMapDrawPos.STAGE_SIZE_SET_MODE.TWO_OBJECT)
            {
                return true;
            }
            letterSpacingFlag = true;
        }
        // SetOneObjectStage_GameObjectÇæÇØì¡éÍèàóù
        if (iterator.name == "SetOneObjectStage_GameObject")
        {
            if (UIFlag)
            {
                return true;
            }

            SerializedProperty mode =
                serializedObject.FindProperty("StageSetMode");

            var extractionMode =
                (SetMapDrawPos.STAGE_SIZE_SET_MODE)
                mode.enumValueIndex;

            if (extractionMode ==
                    SetMapDrawPos.STAGE_SIZE_SET_MODE.NONE ||
                extractionMode ==
                    SetMapDrawPos.STAGE_SIZE_SET_MODE.TWO_OBJECT)
            {
                return true;
            }
            letterSpacingFlag = true;
        }
        // SetTwoObjectStage_GameObjectLeftUpÇæÇØì¡éÍèàóù
        if (iterator.name == "SetTwoObjectStage_GameObjectLeftUp")
        {
            if (UIFlag)
            {
                return true;
            }

            SerializedProperty mode =
                serializedObject.FindProperty("StageSetMode");

            var extractionMode =
                (SetMapDrawPos.STAGE_SIZE_SET_MODE)
                mode.enumValueIndex;

            if (extractionMode ==
                    SetMapDrawPos.STAGE_SIZE_SET_MODE.NONE ||
                extractionMode ==
                    SetMapDrawPos.STAGE_SIZE_SET_MODE.ONE_OBJECT)
            {
                return true;
            }
        }

        // SetTwoObjectStage_GameObjectRightDownÇæÇØì¡éÍèàóù
        if (iterator.name == "SetTwoObjectStage_GameObjectRightDown")
        {
            if (UIFlag)
            {
                return true;
            }

            SerializedProperty mode =
                serializedObject.FindProperty("StageSetMode");

            var extractionMode =
                (SetMapDrawPos.STAGE_SIZE_SET_MODE)
                mode.enumValueIndex;

            if (extractionMode ==
                    SetMapDrawPos.STAGE_SIZE_SET_MODE.NONE ||
                extractionMode ==
                    SetMapDrawPos.STAGE_SIZE_SET_MODE.ONE_OBJECT)
            {
                return true;
            }
            letterSpacingFlag = true;
        }

        return false;
    }

    private bool IsUIModeDraw(SerializedProperty iterator, ref bool letterSpacingFlag)
    {
        // OutPutMagnificationPosÇæÇØì¡éÍèàóù
        if (iterator.name == "OutPutMagnificationPos")
        {
            if (!UIFlag)
            {
                return true;
            }

            SerializedProperty mode =
                serializedObject.FindProperty("FileOutputProcess2DPosMode");

            var extractionMode =
                (SetMapDrawPos.FILE_OUTPUT_PROCESS_2D_POS_MODE)
                mode.enumValueIndex;

            if (extractionMode ==
                    SetMapDrawPos.FILE_OUTPUT_PROCESS_2D_POS_MODE.NORMALIZE ||
                extractionMode ==
                    SetMapDrawPos.FILE_OUTPUT_PROCESS_2D_POS_MODE.COORDINATE)
            {
                return true;
            }
        }
        // OutPutRatioÇæÇØì¡éÍèàóù
        if (iterator.name == "OutPutRatio")
        {
            if (!UIFlag)
            {
                return true;
            }

            SerializedProperty mode =
                serializedObject.FindProperty("FileOutputProcess2DSizeMode");

            var extractionMode =
                (SetMapDrawPos.FILE_OUTPUT_PROCESS_2D_SIZE_MODE)
                mode.enumValueIndex;

            if (extractionMode ==
                    SetMapDrawPos.FILE_OUTPUT_PROCESS_2D_SIZE_MODE.ORIGINAL ||
                extractionMode ==
                    SetMapDrawPos.FILE_OUTPUT_PROCESS_2D_SIZE_MODE.FIXED_RATIO ||
                extractionMode ==
                    SetMapDrawPos.FILE_OUTPUT_PROCESS_2D_SIZE_MODE.FIXED_RATIO_EDITOR_SCALE)
            {
                return true;
            }
        }
        // OutPutMagnificationSizeÇæÇØì¡éÍèàóù
        if (iterator.name == "OutPutMagnificationSize")
        {
            if (!UIFlag)
            {
                return true;
            }

            SerializedProperty mode =
                serializedObject.FindProperty("FileOutputProcess2DSizeMode");

            var extractionMode =
                (SetMapDrawPos.FILE_OUTPUT_PROCESS_2D_SIZE_MODE)
                mode.enumValueIndex;

            if (extractionMode ==
                    SetMapDrawPos.FILE_OUTPUT_PROCESS_2D_SIZE_MODE.ORIGINAL ||
                extractionMode ==
                    SetMapDrawPos.FILE_OUTPUT_PROCESS_2D_SIZE_MODE.FIXED_RATIO ||
                extractionMode ==
                    SetMapDrawPos.FILE_OUTPUT_PROCESS_2D_SIZE_MODE.EDITOR_RATIO)
            {
                return true;
            }
        }

        return false;
    }

    /// <summary>
    /// UIFlagÇÃÇ›Ç…ÇÊÇ¡Çƒï`âÊÇ™Ç≥ÇÍÇÈ/Ç≥ÇÍÇ»Ç¢ïœêîèàóù
    /// </summary>
    private bool IsUIFlagDraw(SerializedProperty iterator)
    {
        if ((iterator.name == "FileOutputProcessMode") ||
            (iterator.name == "StageSetMode") ||
            (iterator.name == "StageLeftUp") ||
            (iterator.name == "StageMiddle") ||
            (iterator.name == "StageRightDown"))
        {
            if (UIFlag)
            {
                return true;
            }
        }

        if ((iterator.name == "FileOutputProcess2DPosMode") ||
            (iterator.name == "FileOutputProcess2DSizeMode"))
        {
            if (!UIFlag)
            {
                return true;
            }
        }
        return false;
    }
}