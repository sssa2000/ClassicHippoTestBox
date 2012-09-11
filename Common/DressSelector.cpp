#include "DressSelector.h"
#include "xml/tinyxml.h"
#include "ErrReport.h"
#include "idMath/dMathHeader.h"
#include <iterator>

DressCon DressSelector::m_actor_dresslink[ACTOR_ITEM_NUM][2]; //第二维表示男女
DressCon DressSelector::m_pet_dresslink[PET_ITEM_NUM][2];//第二维表示男女

DressSelector::~DressSelector()
{
	for(int part=0;part<ACTOR_ITEM_NUM;++part)
	{
		for(int i=0;i<2;++i)
		{
			DressConItr itr=m_actor_dresslink[part][i].begin();
			DressConItr itrend=m_actor_dresslink[part][i].end();
			while (itr!=itrend)
			{
				dress_info* p=*itr;
				delete p;
				++itr;
			}
			m_actor_dresslink[part][i].clear();
		}
	}

	for(int part=0;part<PET_ITEM_NUM;++part)
	{
		for(int i=0;i<2;++i)
		{
			DressConItr itr=m_pet_dresslink[part][i].begin();
			DressConItr itrend=m_pet_dresslink[part][i].end();
			while (itr!=itrend)
			{
				dress_info* p=*itr;
				delete p;
				++itr;
			}
			m_pet_dresslink[part][i].clear();
		}
	}
}

//获取随机的人物服装不包括挂件
DressCon DressSelector::GetActorRandomDress(int bmale)
{
	DressCon res;
	for(int i=0;i<H3DI::BODYPART_NUM-1;++i)
	{
		size_t s=m_actor_dresslink[i][bmale].size();
		idRandom2 _random(GetTickCount());
		int rand_idx=_random.RandomInt(s);
		DressCon* pCon=&(m_actor_dresslink[i][bmale]);
		if(!pCon->empty())
			res.push_back(pCon->at(rand_idx));
		//std::copy(pCon->begin(),pCon->end(),std::back_inserter(res));
	}
	
	return res;
}

//获取随机的人物挂件
DressCon DressSelector::GetActorRandomLink(int bmale)
{
	DressCon res;
	for(int i=H3DI::BODYPART_NUM-1;i<ACTOR_ITEM_NUM;++i)
	{
		size_t s=m_actor_dresslink[i][bmale].size();
		idRandom2 _random(GetTickCount());
		int rand_idx=_random.RandomInt(s);
		DressCon* pCon=&(m_actor_dresslink[i][bmale]);
		if(!pCon->empty())
			res.push_back(pCon->at(rand_idx));
	}

	return res;
}

//获取随机的Pet服装不包括挂件
DressCon DressSelector::GetPetRandomDress(int bmale)
{
	DressCon res;
	for(int i=0;i<H3DI::PET_BODYPART_NUM;++i)
	{
		size_t s=m_pet_dresslink[i][bmale].size();
		idRandom2 _random(GetTickCount());
		int rand_idx=_random.RandomInt(s);
		DressCon* pCon=&(m_pet_dresslink[i][bmale]);
		if(!pCon->empty())
			res.push_back(pCon->at(rand_idx));
	}

	return res;
}

//获取随机的Pet挂件
DressCon DressSelector::GetPetRandomLink(int bmale)
{
	DressCon res;
	for(int i=10;i<13;++i) //宠物是10-13
	{
		int idx=GetPetAdoArrayIdx(i);
		size_t s=m_pet_dresslink[idx][bmale].size();
		idRandom2 _random(GetTickCount());
		int rand_idx=_random.RandomInt(s);
		DressCon* pCon=&(m_pet_dresslink[idx][bmale]);
		if(!pCon->empty())
			res.push_back(pCon->at(rand_idx));
	}

	return res;
}

void DressSelector::AddDressInfo(bool bIsActor,dress_info* pinfo,TiXmlElement* bodypartlist,const char* elem_key_word)
{
	TiXmlElement* bodypart=bodypartlist->FirstChildElement(elem_key_word);
	while (bodypart)
	{
		const char* type=bodypart->Attribute("type");
		const char* src=bodypart->Attribute("src");
		int t=atoi(type);
		pinfo->allfilename.push_back(std::make_pair(t,std::string(src)));
		bodypart=bodypart->NextSiblingElement(elem_key_word);
	}

	if(bIsActor)
	{
		m_actor_dresslink[pinfo->appearancetype][pinfo->male].push_back(pinfo);
	}
	else
	{
		int idx=GetPetAdoArrayIdx(pinfo->appearancetype);
		m_pet_dresslink[idx][pinfo->male].push_back(pinfo);
	}
}

void DressSelector::ParseDressList(TiXmlElement* pElem)
{
	const char* id=pElem->Attribute("id");
	const char* name=pElem->Attribute("name");
	const char* appearancetype=pElem->Attribute("appearancetype");
	const char* gender=pElem->Attribute("gender");

	TiXmlElement* bodypartlist=pElem->FirstChildElement("bodypartlist");
	TiXmlElement* adornmentlist=pElem->FirstChildElement("adornmentlist");

	dress_info* pinfo=new dress_info;
	pinfo->id=id;
	pinfo->chinese_name=name;
	pinfo->appearancetype=atoi(appearancetype);
	pinfo->male=(strcmp("0",gender)==0);

	bool bIsActor=(id[0]!='3'); 
	TiXmlElement* pelem=bodypartlist;
	std::string keyword="bodypart";

	if(pinfo->appearancetype >= 10) //挂件
	{
		pelem=adornmentlist;
		keyword="adornment";
	}

	AddDressInfo(bIsActor,pinfo,pelem,keyword.c_str());
}

void DressSelector::LoadDressXML(const char* filename)
{
	TiXmlDocument doc;
	bool b=doc.LoadFile(filename);
	if(!b)
	{
		HippoReportErr("Load %s Failed,Reason:%s",filename,doc.ErrorDesc());
		return;
	}

	TiXmlElement* pRoot=doc.RootElement();
	TiXmlElement* pDressList=pRoot->FirstChildElement("Dress");
	while (pDressList)
	{
		ParseDressList((pDressList));
		pDressList=pDressList->NextSiblingElement("Dress");
	}
}

