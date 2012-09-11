/********************************************************************
	created:	2012/09/06
	created:	6:9:2012   16:18
	filename: 	E:\Git\ClassicHippoTestBox\Common\DressSelector.h
	file path:	E:\Git\ClassicHippoTestBox\Common
	file base:	ActorDressSelector
	file ext:	h
	author:		sssa2000
	
	purpose:	
*********************************************************************/
#include <string>
#include <vector>
#include "engine_interface.h"
#pragma once


class TiXmlElement;

//单件服装
//first=subtype
//second=path
typedef std::vector<std::pair<int,std::string> > SingleDress;
typedef SingleDress::iterator SingleDressItr;

//表示dress.xml中得一个dress项
struct dress_info
{
	std::string id;
	std::string chinese_name;
	int male;
	int appearancetype;
	SingleDress allfilename; 
};

typedef std::vector<dress_info*> DressCon;
typedef DressCon::iterator DressConItr;


#define ACTOR_ITEM_NUM H3DI::BODYPART_NUM+H3DI::ACTOR_ADORNMENT_NUM-1  //实际上没有BODYPART_ARM
#define PET_ITEM_NUM H3DI::PET_BODYPART_NUM+1+H3DI::PET_ADORNMENT_NUM //宠物的bodypart枚举中没有套装，所以要+1


//职责：负责提供人物的服装信息
class DressSelector
{
public:

	DressSelector(){}
	~DressSelector();

	static H3DI::EActorAdornmentPosition GetActorAdoPosFromInt(int i)
	{
		return H3DI::EActorAdornmentPosition(i-(H3DI::BODYPART_NUM-1));
	}

	static H3DI::EPetAdornmentPosition GetPetAdoPosFromInt(int i)
	{
		return H3DI::EPetAdornmentPosition(i-(H3DI::PET_BODYPART_NUM-1));
	}

	//由于宠物的subtype是从1000000开始的，所以要减去
	//参数appearancetype对应petdress中的appearancetype
	static int GetPetAdoArrayIdx(int appearancetype)
	{
		if(appearancetype==2) //头
			return 0;
		else if(appearancetype==4)//身体
			return 1;
		else if(appearancetype==9) //套装
			return 2;
		else if(appearancetype>=10) //挂件
		{
			return 3+appearancetype-10;
		}
		else
			return -1;
	}


	//load dress xml,role and pet all include 
	static void LoadDressXML(const char* filename);

	//获取随机的人物服装不包括挂件
	static DressCon GetActorRandomDress(int bmale);

	//获取随机的人物挂件
	static DressCon GetActorRandomLink(int bmale);

	//获取随机的Pet服装不包括挂件
	static DressCon GetPetRandomDress(int bmale);

	//获取随机的Pet挂件
	static DressCon GetPetRandomLink(int bmale);


private:

	static void ParseDressList(TiXmlElement* pElem);
	static void AddDressInfo(bool bIsActor,dress_info* pinfo,TiXmlElement* bodypartlist,const char* elem_key_word);


	static DressCon m_actor_dresslink[ACTOR_ITEM_NUM][2]; //第二维表示男女
	static DressCon m_pet_dresslink[PET_ITEM_NUM][2];//第二维表示男女


};