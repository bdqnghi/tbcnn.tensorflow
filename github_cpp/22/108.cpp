







#include "vid_public.h"
#include "tranbucket.h"

#define TRANMAXBUCKETCOUNT    64


void TranBucketMan::ClearData()
{
  BucketMan::ClearData();

	maxZ = 1.0f;
	minZ = 0.0f;
	maxBucketCount = 1.0f;
	UpdateScaleZ();
  doSort = TRUE;
}


void TranBucketMan::SetPrimitiveDesc( PrimitiveDesc & prim)
{
  primitive.SetPrimitiveDescTag( prim);
}


void TranBucketMan::SetPrimitiveDesc( Bucket & bucket, PrimitiveDesc & prim)
{
  bucket.SetPrimitiveDescTag( prim);
}


Bool TranBucketMan::CompareRenderState( const PrimitiveDesc & other) const 
{
	if (
#ifndef DODXLEANANDGRUMPY
		   primitive.material       == other.material       &&
		   primitive.vertex_type    == other.vertex_type    &&
#endif
       primitive.tag            == other.tag            && 
			 primitive.primitive_type == other.primitive_type &&
			 primitive.flags          == other.flags          &&
       primitive.texture_count  == other.texture_count)
	{
		for ( U32 i = 0; i < primitive.texture_count; i++ )
		{
			if (primitive.textureStages[i] != other.textureStages[i] )
			{
				return FALSE;
			}
		}

		return TRUE;
	}

	return FALSE;
}


void TranBucketMan::Flush( Bool doDraw)  
{ 
  if (!doDraw)
	{
		BucketMan::Flush(FALSE);
		return;
	}

  Vid::SetZWriteState( FALSE);
  Bool alpha = Vid::SetAlphaState( TRUE);

	
	

	NList<Bucket>::Iterator li(&bucketList); 
  Bucket * list[444];
  S32 count = 0;
  while (Bucket * bucket = li++)
  {
    if (bucket->vCount)
    {
      list[count] = bucket;
      count++;

      ASSERT( count <= 444);
    }
#ifdef DOLASTBUCKET
    if (bucket == lastUsedBucket)
    {
      break;
    }
#endif
  }

	
	for (count--; count >= 0; count--)
	{
		Bucket *max = list[count];
  
		
    S32 i, current = count;
		for (i = count - 1; i >= 0; i--)
		{
			if (list[i]->tag > max->tag)
			{
				max = list[i];
        current = i;
			}

		}

    if (!Vid::caps.noTransort && !(max->flags & RS_NOSORT) && primitive.primitive_type != PT_LINELIST)
    {
      max->Sort();
    }
		
    if ((max->flags & RS_DST_MASK) == RS_DST_ONE)
    {
      Vid::SetFogColorD3D( 0);

  		FlushBucket( *max);

      Vid::SetFogColorD3D( Vid::renderState.fogColor);
    }
    else
    {
  		FlushBucket( *max);
    }

    max->Reset();

    
    
    list[current] = list[count];
	}


  Vid::SetAlphaState( alpha);
  Vid::SetZWriteState( TRUE);

  curMem  = memBlock;
  curSize = memSize;

  currentBucket = NULL;
  lastUsedBucket = NULL;
}


void TranBucketMan::FlushTex( const Bitmap * texture, Bool doDraw)  
{ 
  if (!doDraw)
	{
		BucketMan::Flush(FALSE);
		return;
	}

  Vid::SetZWriteState( FALSE);
  Bool alpha = Vid::SetAlphaState( TRUE);

#if 1

  NList<Bucket>::Iterator li(&bucketList); 
  for (!li; *li; li++)
	{
    Bucket *bucket = *li;

    if (bucket->texture_count && bucket->textureStages[0].texture == texture && bucket->vCount)
    {

		  
      if ((bucket->flags & RS_DST_MASK) == RS_DST_ONE)
      {
        Vid::SetFogColorD3D( 0);

  		  FlushBucket( *bucket);

        Vid::SetFogColorD3D( Vid::renderState.fogColor);
      }
      else
      {
  		  FlushBucket( *bucket);
      }
    }
    bucket->Reset();
	}

  currentBucket = NULL;

#else

	
	
	NList<Bucket>::Iterator li(&bucketList); 
  Bucket *list[222];
  S32 count = 0;
#if 0
  S32 ic = 0;
	NList<Bucket>::Node *lnode = NULL;
  NList<Bucket>::Node *llnode = NULL;
#endif
  for (!li; *li; li++)
  {

		if ((*li)->vCount)
		{
      list[count] = *li;
      count++;
		}
	}

	
	for (count--; count >= 0; count--)
	{
		Bucket *max = list[count];
  
		
    S32 i, current = count;
		for (i = count - 1; i >= 0; i--)
		{
			if (list[i]->tag > max->tag)
			{
				max = list[i];
        current = i;
			}
		}

    if (!Vid::caps.notransort && !(max->flags & RS_NOSORT))
    {
      max->Sort();
    }


		
    if ((max->flags & RS_DST_MASK) == RS_DST_ONE)
    {
      Vid::SetFogColorD3D( 0);

  		FlushBucket( *max);

      Vid::SetFogColorD3D( Vid::renderState.fogColor);
    }
    else
    {
  		FlushBucket( *max);
    }
    max->Reset();

    
    
    list[current] = list[count];
	}
#endif

  Vid::SetAlphaState( alpha);
  Vid::SetZWriteState( TRUE);

  curMem  = memBlock;
  curSize = memSize;
  currentBucket = NULL;
}


void TranBucketMan::UpdateScaleZ()
{
	ASSERT( minZ <= maxZ );
	ASSERT( maxBucketCount > 0.0f );


  scaleZ = (maxBucketCount - 1) / (maxZ - minZ);
}


void TranBucketMan::SetZ( F32 _z)
{
	ASSERT( scaleZ > 0.0f );
  
  U32 sort_z;

  if (_z < minZ)
  {
    sort_z = 0;
  }
  else if (_z > maxZ)
  {
    sort_z = (U32) Utils::FtoLDown(maxBucketCount);
  }
  else
  {
  	

	  sort_z = (U32) Utils::FtoLDown( ( _z - minZ ) * scaleZ );
  }
	
	
	
#ifdef DEVELOPMENT
  if (!(sort_z <= (U32) maxBucketCount))
  {
  	ASSERT( sort_z <= (U32) maxBucketCount );  
  }
	ASSERT( sort_z < U16_MAX );
#endif

	BucketMan::SetTag( U16( sort_z));
}

