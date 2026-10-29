using UnityEditor;
using UnityEngine;

[CustomPropertyDrawer(typeof(EnumTooltipAttribute))]
public class EnumTooltipDrawer : PropertyDrawer
{
    public override void OnGUI(
        Rect position,
        SerializedProperty property,
        GUIContent label)
    {
        EnumTooltipAttribute attribute =
            (EnumTooltipAttribute)this.attribute;

        string[] enumNames = property.enumNames;

        GUIContent[] contents =
            new GUIContent[enumNames.Length];

        for (int i = 0; i < enumNames.Length; i++)
        {
            string tooltip = "";

            if (i < attribute.Tooltips.Length)
            {
                tooltip = attribute.Tooltips[i];
            }

            contents[i] = new GUIContent(
                enumNames[i],
                tooltip);
        }

        property.enumValueIndex =
            EditorGUI.Popup(
                position,
                label,
                property.enumValueIndex,
                contents);
    }
}