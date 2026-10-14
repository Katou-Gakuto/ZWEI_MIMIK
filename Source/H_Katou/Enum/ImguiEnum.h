#pragma once

enum class IMGUI_GROUP_TYPE
{
    NONE = 0,
    TEST_1,
    TEST_2,
    TEST_3,
    TEST_4,
    TEST_5,
    TEST_6,
    TEST_7,
    TEST_8,
    MAX
};

enum class IMGUI_TYPE
{
    SLIDER1 = 0,
    SLIDER2,
    SLIDER3,
    SLIDER4,
    DRAG1,
    DRAG2,
    DRAG3,
    DRAG4,
    INPUT1,
    INPUT2,
    INPUT3,
    INPUT4,
    ANGLE,
};

/* ïœêîÇÃå^ */
enum class IMGUI_VARIABLE_TYPE
{
    NONE = 0,
    CHAR,               //                 charå^
    UNSIGNED_CHAR,      // unsigned        charå^
    SHORT,              //                shortå^
    UNSIGNED_SHORT,     // unsigned       shortå^
    INT,                //                  intå^
    UNSIGNED_INT,       // unsigned         intå^
    LONG,               //                 longå^
    UNSIGNED_LONG,      // unsigned        longå^
    LONG_LONG,          //          long   longå^
    UNSIGNED_LONG_LONG, // unsigned long   longå^
    FLOAT,              //                floatå^
    DOUBLE,             //               doubleå^
    LONG_DOUBLE,        //          long doubleå^
};

#define IMGUI_VARIABLE_INTEGER 1
#define IMGUI_VARIABLE_MINORITY 0

/*ïœêîêÆêîï™óﬁ(0 == ïÇìÆè¨êî, 1 == êÆêî, -1 == NONE)*/
enum class IMGUI_VARIABLE_INTEGER_TYPE
{
    NONE = -1,
    CHAR = IMGUI_VARIABLE_INTEGER,                  //                 charå^
    UNSIGNED_CHAR = IMGUI_VARIABLE_INTEGER,         // unsigned        charå^
    SHORT = IMGUI_VARIABLE_INTEGER,                 //                shortå^
    UNSIGNED_SHORT = IMGUI_VARIABLE_INTEGER,        // unsigned       shortå^
    INT = IMGUI_VARIABLE_INTEGER,                   //                  intå^
    UNSIGNED_INT = IMGUI_VARIABLE_INTEGER,          // unsigned         intå^
    LONG = IMGUI_VARIABLE_INTEGER,                  //                 longå^
    UNSIGNED_LONG = IMGUI_VARIABLE_INTEGER,         // unsigned        longå^
    LONG_LONG = IMGUI_VARIABLE_INTEGER,             //          long   longå^
    UNSIGNED_LONG_LONG = IMGUI_VARIABLE_INTEGER,    // unsigned long   longå^
    FLOAT = IMGUI_VARIABLE_MINORITY,                //                floatå^
    DOUBLE = IMGUI_VARIABLE_MINORITY,               //               doubleå^
    LONG_DOUBLE = IMGUI_VARIABLE_MINORITY,          //          long doubleå^
};

/*É{É^ÉìéÌóﬁ*/
enum class IMGUI_BUTTON_TYPE
{
    NONE = 0,
    BUTTON,
    SMALL_BUTTON,
    ARROW_BUTTON,
    INVISIBLE_BUTTON,
    CHECK_BOX,
    CHECK_BOX_FLAGS,
    RADIO_BUTTON,
    COLOR_BUTTON,
    SELECTABLE,
    MENU_ITEM,
    TABITEM_BUTTON,
    TEXT_LINK,
    TEXT_LINK_OPEN_URL,
};

/*ÉåÉCÉAÉEÉgéÌóﬁ*/
enum class IMGUI_LAYOUT_TYPE
{
    NONE = 0,
    IMGUI_LAYOUT_TEXT,                      // Text()
    IMGUI_LAYOUT_TEXT_FORMAT,               // Text()ÅiÉtÉHÅ[É}ÉbÉgïtÇ´Åj

    IMGUI_LAYOUT_SAME_LINE,                 // SameLine()
    IMGUI_LAYOUT_SEPARATOR,                 // Separator()
    IMGUI_LAYOUT_SPACING,                   // Spacing()

    //==================================================
    // ÉåÉCÉAÉEÉgÅEîzíuä÷òA
    //==================================================
    IMGUI_LAYOUT_NEW_LINE,                  // NewLine()
    IMGUI_LAYOUT_INDENT,                    // Indent()
    IMGUI_LAYOUT_UNINDENT,                  // Unindent()
    IMGUI_LAYOUT_DUMMY,                     // Dummy()
    IMGUI_LAYOUT_SET_NEXT_ITEM_WIDTH,        // SetNextItemWidth()
    IMGUI_LAYOUT_PUSH_ITEM_WIDTH,            // PushItemWidth()
    IMGUI_LAYOUT_POP_ITEM_WIDTH,             // PopItemWidth()
    IMGUI_LAYOUT_ALIGN_TEXT_TO_FRAME_PADDING,// AlignTextToFramePadding()
    IMGUI_LAYOUT_SET_NEXT_ITEM_OPEN,         // SetNextItemOpen()

    //==================================================
    // ÉOÉãÅ[Évä÷òA
    //==================================================
    IMGUI_LAYOUT_BEGIN_GROUP,                // BeginGroup()
    IMGUI_LAYOUT_END_GROUP,                  // EndGroup()

    //==================================================
    // éqóÃàÊä÷òA
    //==================================================
    IMGUI_LAYOUT_BEGIN_CHILD,                // BeginChild()
    IMGUI_LAYOUT_END_CHILD,                  // EndChild()

    //==================================================
    // ê‹ÇËÇΩÇΩÇ›ÅEÉcÉäÅ[ä÷òA
    //==================================================
    IMGUI_LAYOUT_COLLAPSING_HEADER,          // CollapsingHeader()
    IMGUI_LAYOUT_TREE_NODE,                  // TreeNode()
    IMGUI_LAYOUT_TREE_POP,                   // TreePop()

    //==================================================
    // ï\ä÷òA
    //==================================================
    IMGUI_LAYOUT_BEGIN_TABLE,                // BeginTable()
    IMGUI_LAYOUT_TABLE_SETUP_COLUMN,         // TableSetupColumn()
    IMGUI_LAYOUT_TABLE_HEADERS_ROW,          // TableHeadersRow()
    IMGUI_LAYOUT_TABLE_NEXT_ROW,             // TableNextRow()
    IMGUI_LAYOUT_TABLE_NEXT_COLUMN,          // TableNextColumn()
    IMGUI_LAYOUT_TABLE_SET_COLUMN_INDEX,     // TableSetColumnIndex()
    IMGUI_LAYOUT_END_TABLE,                  // EndTable()

    //==================================================
    // ÉXÉ^ÉCÉãä÷òA
    //==================================================
    IMGUI_LAYOUT_PUSH_STYLE_VAR,             // PushStyleVar()
    IMGUI_LAYOUT_POP_STYLE_VAR,              // PopStyleVar()
    IMGUI_LAYOUT_PUSH_STYLE_COLOR,           // PushStyleColor()
    IMGUI_LAYOUT_POP_STYLE_COLOR,            // PopStyleColor()
};