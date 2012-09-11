#include "ActorUtil.h"
#include "engine_interface.h"
#include "HippoFrameWork.h"
#include "DressSelector.h"

void ActorUtil::InitActorDress(const char* actor_dress)
{
	static bool bInit=false;
	if(!bInit)
	{
		if(actor_dress)
		{
			DressSelector::LoadDressXML(actor_dress);
			bInit=true;
		}
	}
}

void ActorUtil::InitPetDress(const char* pet_dress)
{
	static bool bInit=false;
	if(!bInit)
	{
		if(pet_dress)
		{
			DressSelector::LoadDressXML(pet_dress);
			bInit=true;
		}
	}
}

void ActorUtil::RandomBodypart(H3DI::IActor* p,int bmale)
{
	DressCon con=DressSelector::GetActorRandomDress(bmale);
	DressConItr itr=con.begin();
	DressConItr itrend=con.end();
	while (itr!=itrend)
	{
		dress_info* pinfo=*itr;

		if(pinfo->appearancetype==1) //eye的资源有问题
		{
			++itr;
			continue;
		}


		SingleDress& single=pinfo->allfilename;
		
		SingleDressItr s_itr=single.begin();
		SingleDressItr s_itrend=single.end();
		while (s_itr!=s_itrend)
		{
			std::string& path=s_itr->second;
			std::string bppath="../resources/art/role/bodypart/";
			bppath+=path;
			p->SetBodyPart(bppath.c_str());
			++s_itr;
		}

		++itr;
	}
}

void ActorUtil::RandomLink(H3DI::IActor* p,int bmale)
{
	DressCon con=DressSelector::GetActorRandomLink(bmale);
	DressConItr itr=con.begin();
	DressConItr itrend=con.end();
	while (itr!=itrend)
	{
		dress_info* pinfo=*itr;
		SingleDress& single=pinfo->allfilename;

		SingleDressItr s_itr=single.begin();
		SingleDressItr s_itrend=single.end();
		while (s_itr!=s_itrend)
		{
			std::string& path=s_itr->second;
			H3DI::EActorAdornmentPosition e=DressSelector::GetActorAdoPosFromInt(s_itr->first);
			std::string bppath="../resources/art/role/link/";
			bppath+=path;
			p->SetAdornment(e,bppath.c_str());
			++s_itr;
		}

		++itr;
	}
}

void ActorUtil::ClearBodypart(H3DI::IActor* p)
{

}

void ActorUtil::ClearLink(H3DI::IActor* p)
{

}


void ActorUtil::RandomBodypart(H3DI::IAvatarSkeletonModel* p,int bmale)
{
	DressCon con=DressSelector::GetPetRandomDress(bmale);
	DressConItr itr=con.begin();
	DressConItr itrend=con.end();
	while (itr!=itrend)
	{
		dress_info* pinfo=*itr;

		SingleDress& single=pinfo->allfilename;

		SingleDressItr s_itr=single.begin();
		SingleDressItr s_itrend=single.end();
		while (s_itr!=s_itrend)
		{
			std::string& path=s_itr->second;
			std::string bppath="../resources/art/role/pet/";
			bppath+=path;
			p->SetBodyPart(bppath.c_str());
			++s_itr;
		}

		++itr;
	}
}

void ActorUtil::RandomLink(H3DI::IAvatarSkeletonModel* p,int bmale)
{
	DressCon con=DressSelector::GetPetRandomLink(bmale);
	DressConItr itr=con.begin();
	DressConItr itrend=con.end();
	while (itr!=itrend)
	{
		dress_info* pinfo=*itr;
		SingleDress& single=pinfo->allfilename;

		SingleDressItr s_itr=single.begin();
		SingleDressItr s_itrend=single.end();
		while (s_itr!=s_itrend)
		{
			std::string& path=s_itr->second;
			H3DI::EPetAdornmentPosition e=DressSelector::GetPetAdoPosFromInt(s_itr->first);
			std::string bppath="../resources/art/role/pet/link/";
			bppath+=path;
			p->SetAdornment(e,bppath.c_str());
			++s_itr;
		}

		++itr;
	}
}
void ActorUtil::ClearBodypart(H3DI::IAvatarSkeletonModel* p)
{

}
void ActorUtil::ClearLink(H3DI::IAvatarSkeletonModel* p)
{

}