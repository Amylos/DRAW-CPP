/*
 * CContainer.h
 *
 *  Created on: 9 sept. 2022
 *      Author: Garnier
 */

#ifndef CCONTAINER_H_
#define CCONTAINER_H_


typedef void*(*t_ptfV)(void*);
typedef void*(*t_ptfVV)(void*, void*);


class CContainer{
private:
	class CNode{
	public:
		CNode* 	m_pPrev;
		CNode*	m_pNext;
		void*	m_pItem;

	private:
		CNode();
		~CNode();

	public:
		CNode(CNode*pPrev, CNode*pNext,void*pItem);

		CNode*DelReturnNext(t_ptfV pDeleteFunc);
	};

	CNode*	m_pHead;
	CNode*	m_pTail;
	t_ptfV	m_pDeleteFunc;
	size_t	m_szCard;

private:
	CContainer();
public:
	CContainer(t_ptfV pDeleteFunc);
	~CContainer();
	/******* OTHER METHODS ********/
	void* Flush();
	void*Pushback(void*pItem);
	void*Pushfront(void*pItem);
	void*Parse(t_ptfVV pParsFunc,void*pParam) const;
	void*ParseDelif(t_ptfVV pParseFunc, void*pParam);

	/******* CONSTANTE METHODS ********/

	void*Getback() const;
	void*Getfront()const;
	size_t Card() const;
};

#endif /* CCONTAINER_H_ */
