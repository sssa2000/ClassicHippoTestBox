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

//������װ
//first=subtype
//second=path
typedef std::vector<std::pair<int,std::string> > SingleDress;
typedef SingleDress::iterator SingleDressItr;

//��ʾdress.xml�е�һ��dress��
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


#define ACTOR_ITEM_NUM H3DI::BODYPART_NUM+H3DI::ACTOR_ADORNMENT_NUM-1  //ʵ����û��BODYPART_ARM
#define PET_ITEM_NUM H3DI::PET_BODYPART_NUM+1+H3DI::PET_ADORNMENT_NUM //�����bodypartö����û����װ������Ҫ+1


//ְ�𣺸����ṩ����ķ�װ��Ϣ
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

	//���ڳ����subtype�Ǵ�1000000��ʼ�ģ�����Ҫ��ȥ
	//����appearancetype��Ӧpetdress�е�appearancetype
	static int GetPetAdoArrayIdx(int appearancetype)
	{
		if(appearancetype==2) //ͷ
			return 0;
		else if(appearancetype==4)//����
			return 1;
		else if(appearancetype==9) //��װ
			return 2;
		else if(appearancetype>=10) //�Ҽ�
		{
			return 3+appearancetype-10;
		}
		else
			return -1;
	}


	//load dress xml,role and pet all include 
	static void LoadDressXML(const char* filename);

	//��ȡ����������װ�������Ҽ�
	static DressCon GetActorRandomDress(int bmale);

	//��ȡ���������Ҽ�
	static DressCon GetActorRandomLink(int bmale);

	//��ȡ�����Pet��װ�������Ҽ�
	static DressCon GetPetRandomDress(int bmale);

	//��ȡ�����Pet�Ҽ�
	static DressCon GetPetRandomLink(int bmale);


private:

	static void ParseDressList(TiXmlElement* pElem);
	static void AddDressInfo(bool bIsActor,dress_info* pinfo,TiXmlElement* bodypartlist,const char* elem_key_word);


	static DressCon m_actor_dresslink[ACTOR_ITEM_NUM][2]; //�ڶ�ά��ʾ��Ů
	static DressCon m_pet_dresslink[PET_ITEM_NUM][2];//�ڶ�ά��ʾ��Ů


};