#include "QuadTree.h"
#include "ModelData.h"
#include "CameraManager.h"
#include "DataTable.h"
#include "AI/Collision.h"

NEWDEL_IMPL(QuadTree)
NEWDEL_IMPL(QuadNode)


void QuadNode::AllocateChildren(int depth, int & count)
{
	if (depth == count)
		return;

	count++;
	mQuadNodes = new QuadNode[4];

	float halfRadius = mRadius * 0.5f;
	// 0, 1
	// 2, 3

	mQuadNodes[0].SetRadius( halfRadius );
	mQuadNodes[1].SetRadius( halfRadius );
	mQuadNodes[2].SetRadius( halfRadius );
	mQuadNodes[3].SetRadius( halfRadius );

	mQuadNodes[0].SetCenter( mCenter.x - halfRadius, mCenter.y - halfRadius );
	mQuadNodes[1].SetCenter( mCenter.x + halfRadius, mCenter.y - halfRadius );
	mQuadNodes[2].SetCenter( mCenter.x - halfRadius, mCenter.y + halfRadius );
	mQuadNodes[3].SetCenter( mCenter.x + halfRadius, mCenter.y + halfRadius );

	for (int n=0;n<4;n++)
	{			
		mQuadNodes[n].AllocateChildren( depth, count );
	}

	count--;
}



void QuadNode::GetQuadsCameraFrustum(QuadNode ** retQuadNodes, int & retQuadNodeCount, PVRTMat4 * pLookMtx)
{
	
    PVRTVec4 vecA( pLookMtx->f[12], 0.0f,  pLookMtx->f[14], 1);
	PVRTVec4 vecB( GLOBAL_SCALE *  FRUSTUM_W, 0.0f,  GLOBAL_SCALE * FRUSTUM_D, 1);
	PVRTVec4 vecC( GLOBAL_SCALE * -FRUSTUM_W, 0.0f,  GLOBAL_SCALE * FRUSTUM_D, 1);
	
    
    vecB = *pLookMtx * vecB;
    vecC = *pLookMtx * vecC;
    
	
	PVRTVec2 A(vecA.x, vecA.z);
	PVRTVec2 B(vecB.x, vecB.z);
	PVRTVec2 C(vecC.x, vecC.z);

	GetQuadsTriangleFrustum(A, B, C, retQuadNodes, retQuadNodeCount);

}

void QuadNode::GetQuadsTriangleFrustum(PVRTVec2 A, PVRTVec2 B, PVRTVec2 C, QuadNode ** retQuadNodes, int & retQuadNodeCount)
{

	PVRTVec2 P = GetCenter();


	PVRTVec2 v0 = C - A;
	PVRTVec2 v1 = B - A;
	PVRTVec2 v2 = P - A;

	// Compute dot products
	float dot00 = v0.dot(v0);
	float dot01 = v0.dot(v1);
	float dot02 = v0.dot(v2);
	float dot11 = v1.dot(v1);
	float dot12 = v1.dot(v2);

	// Compute barycentric coordinates
	float invDenom = 1.0f / (dot00 * dot11 - dot01 * dot01);
	float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
	float v = (dot00 * dot12 - dot01 * dot02) * invDenom;

	bool addToList = false;
	// Check if point is in triangle
	if ( (u > 0) && (v > 0) && (u + v < 1))
	{
		addToList = true;
	}
	else if ( Collision::CircleTriangleEdgeIntersection(A,B,this->GetCenter(), this->GetRadius() ) )
	{
		addToList = true;
	}
	else if ( Collision::CircleTriangleEdgeIntersection(A,C,this->GetCenter(), this->GetRadius() ))
	{
		addToList = true;
	}
	
	if (addToList)
	{
		retQuadNodes[retQuadNodeCount] = this;
		retQuadNodeCount++;

		if (!mQuadNodes)
            return;

		for (int n=0;n<4;n++)
		{
			mQuadNodes[n].GetQuadsTriangleFrustum( A,B,C, retQuadNodes, retQuadNodeCount);
		}
	}
}

void QuadNode::GetQuadsForLine(PVRTVec2 A, PVRTVec2 MID, QuadNode ** retQuadNodes, int & retQuadNodeCount)
{

	PVRTVec2 P = GetCenter();

	bool addToList = false;
	if ( Collision::CircleTriangleEdgeIntersection(A,MID,this->GetCenter(), this->GetRadius() ) )
	{
		addToList = true;
	}
	
	
	if (addToList)
	{
		retQuadNodes[retQuadNodeCount] = this;
		retQuadNodeCount++;

		if (!mQuadNodes)
		return;

		for (int n=0;n<4;n++)
		{
			mQuadNodes[n].GetQuadsForLine( A,MID, retQuadNodes, retQuadNodeCount);
		}
	}
}

void QuadNode::GetQuads(float x, float z, float radius, QuadNode ** retQuadNodes, int & retQuadNodeCount)
{
	PVRTVec2 dataCenter(x,z);
	PVRTVec2 dist = dataCenter - mCenter;
	float len = dist.length();
	if ( len < (mRadius + radius ) )
	{
		retQuadNodes[retQuadNodeCount] = this;
		retQuadNodeCount++;

		if (!mQuadNodes)
			return;

		for (int n=0;n<4;n++)
		{
			mQuadNodes[n].GetQuads( x, z, radius, retQuadNodes, retQuadNodeCount);
		}

	}
}

void QuadNode::GetQuads(float x, float z, QuadNode ** retQuadNodes, int & retQuadNodeCount)
{
	GetQuads(x , z , 0.0f , retQuadNodes, retQuadNodeCount);
}

bool QuadNode::Add(void * pData, float x, float z, float radius)
{
	if (!mQuadNodes)
		return false;

	PVRTVec2 dataCenter(x,z);
	PVRTVec2 dist = dataCenter - mCenter;
	float len = dist.length();
	if ( (len + radius) < mRadius )
	//if ( len < mRadius )
	{
		int falseCount = 0;
		for (int n=0;n<4;n++)
		{
			if (!mQuadNodes[n].Add(pData, x, z, radius))
				falseCount++;
		}

		if (falseCount == 4)
		{
			mDataList.Add(pData);
		}

		return true;
	}

	return false;		
}
