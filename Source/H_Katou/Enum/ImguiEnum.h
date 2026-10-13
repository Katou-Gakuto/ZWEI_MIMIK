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