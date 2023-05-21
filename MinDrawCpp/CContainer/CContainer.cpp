/*
 * CContainer.cpp
 *
 *  Created on: 9 sept. 2022
 *      Author: Garnier
 */

#include<iostream>
using namespace std;

#include"CContainer.h"
#include<assert.h>

CContainer::CNode::CNode(CNode*pPrev, CNode*pNext,void*pItem){

	m_pPrev = pPrev;
	m_pNext = pNext;
	m_pItem = pItem;

	if(pPrev) pPrev->m_pNext = this;
	if(pNext) pNext->m_pPrev = this;

}

CContainer::CNode::~CNode(){
	if(m_pNext)	m_pNext->m_pPrev = m_pPrev;
	if(m_pPrev) m_pPrev->m_pNext = m_pNext;
}

CContainer::CNode* CContainer::CNode::DelReturnNext(t_ptfV pDeleteFunc){

	pDeleteFunc(m_pItem);

	CNode*pNodeNext = m_pNext;

	delete this;

	return pNodeNext;
}


CContainer::CContainer(){
	m_pDeleteFunc = nullptr;
	m_pHead = nullptr;
	m_pTail = nullptr;
	m_szCard = 0;
}

CContainer::CContainer(t_ptfV pDeleteFunc){
	m_pDeleteFunc = pDeleteFunc;
	m_pHead = nullptr;
	m_pTail = nullptr;
	m_szCard = 0;
}

CContainer::~CContainer(){
	this->Flush();
}


void*CContainer::Flush(){
	while(m_pHead){
		m_pHead = m_pHead->DelReturnNext(m_pDeleteFunc);
		m_szCard--;
	}
	assert(m_szCard == 0);
	m_pTail = nullptr;

	return nullptr;
}


void* CContainer::Pushback(void*pItem){

	if(m_szCard == 0){
		assert(m_pHead==nullptr);
		assert(m_pTail==nullptr);
		m_pTail = new CNode(nullptr,nullptr,pItem);
		m_pHead = m_pTail;
	}
	else{
		m_pTail = new CNode(m_pTail,nullptr,pItem);
	}
	m_szCard++;
	assert(m_pTail->m_pItem == pItem);

	return m_pTail->m_pItem;
}

void* CContainer::Pushfront(void*pItem){

	if(m_szCard == 0){
		assert(m_pHead==nullptr);
		assert(m_pTail==nullptr);
		m_pHead = new CNode(nullptr,nullptr,pItem);
		m_pTail = m_pHead;
	}
	else{
		m_pHead = new CNode(nullptr,m_pHead,pItem);
	}
	m_szCard++;
	assert(m_pHead->m_pItem == pItem);

	return m_pTail->m_pItem;
}


void* CContainer::Parse(t_ptfVV pParseFunc,void*pParam) const{

	CNode*pParse = m_pHead;

	while(pParse){
		if(pParseFunc(pParse->m_pItem,pParam))	return pParse->m_pItem;
		pParse = pParse->m_pNext;
	}
	return nullptr;
}

void* CContainer::ParseDelif(t_ptfVV pParseFunc, void*pParam){

	CNode*pParse = m_pHead;

	while(pParse){
		if(pParseFunc(pParse->m_pItem,pParam)){
			if(m_pHead == pParse)	m_pHead = pParse->m_pNext;
			if(m_pTail == pParse)	m_pTail = pParse->m_pPrev;
			pParse = pParse->DelReturnNext(m_pDeleteFunc);				/* To be cautious with pParse = pParse->Method*/
			m_szCard--;
			return nullptr;
		}
		else{
			pParse = pParse->m_pNext;
		}
	}
	return nullptr;
}



	/*********************** CONSTANTE METHODS **********************/


size_t CContainer::Card() const{

	return m_szCard;
}

void* CContainer::Getback()const{

	return m_pTail->m_pItem;
}

void* CContainer::Getfront()const{

	return m_pHead;
}

