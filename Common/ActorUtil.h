/********************************************************************
	created:	2012/09/07
	created:	7:9:2012   13:28
	filename: 	E:\Git\ClassicHippoTestBox\Common\ActorUtil.h
	file path:	E:\Git\ClassicHippoTestBox\Common
	file base:	ActorUtil
	file ext:	h
	author:		sssa2000
	
	purpose:	
*********************************************************************/
#pragma once

namespace H3DI
{
	class IActor;
	class IAvatarSkeletonModel;
}

class ActorUtil
{
public:
	static void InitActorDress(const char* actor_dress);
	static void InitPetDress(const char* pet_dress);
	static void RandomBodypart(H3DI::IActor* p,int bmale);
	static void RandomLink(H3DI::IActor* p,int bmale);
	static void ClearBodypart(H3DI::IActor* p);
	static void ClearLink(H3DI::IActor* p);

	static void RandomBodypart(H3DI::IAvatarSkeletonModel* p,int bmale);
	static void RandomLink(H3DI::IAvatarSkeletonModel* p,int bmale);
	static void ClearBodypart(H3DI::IAvatarSkeletonModel* p);
	static void ClearLink(H3DI::IAvatarSkeletonModel* p);
protected:
private:
};



