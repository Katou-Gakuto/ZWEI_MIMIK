#pragma once
#include "WallObject.h"

// mirrorFaceは鏡面のRayを指定するもの。
// 対応表は以下の通り。
// 0 : LeftUp→RightUp
// 1 : RightUp→RightDown
// 2 : RightDown→LeftDown
// 3 : LeftDown→LeftUp
class MirrorObject : public WallObject
{
public:
	MirrorObject(bool gimmick, const VECTOR2D &leftUp, const VECTOR2D &rightDown, unsigned char mirrorFace);
	~MirrorObject() override;

	int Create() override;

private:
	unsigned char mnMirrorFace;
};