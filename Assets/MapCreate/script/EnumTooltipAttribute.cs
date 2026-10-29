using UnityEngine;

public class EnumTooltipAttribute : PropertyAttribute
{
    public readonly string[] Tooltips;

    public EnumTooltipAttribute(params string[] tooltips)
    {
        Tooltips = tooltips;
    }
}