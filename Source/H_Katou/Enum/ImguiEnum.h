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
    NONE,
    CHAR,               //                 charå^
    UNSIGNED_CHAR,      // unsigned        charå^
    SHORT,              //                shortå^
    UNSIGNED_SHORT,     // unsigned       shortå^
    INT,                //                  intå^
    UNSIGNED_INT,       // unsigned         intå^
    LONG,               //                 longå^
    UNSIGNED_LONG,      // unsigned        longå^
    LONG_LONG,          //          long   longå^
    UNSIGNED_long_LONG, // unsigned long   longå^
    FLOAT,              //                floatå^
    DOUBLE,             //               doubleå^
    LONG_DOUBLE,        //          long doubleå^
};