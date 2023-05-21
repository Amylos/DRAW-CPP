/*
 * CToolBox.h
 *
 *  Created on: 7 oct. 2022
 *      Author: Garnier
 */

#ifndef CTOOLBOX_H_
#define CTOOLBOX_H_

#include<iostream>
#include<cstdint>
#include<SDL2/SDL.h>
#include<defines.h>
#include<CContainer.h>
#include<CArea.h>
#include"CTool.h"


class CToolBox : public CArea{
private:
	SDL_Rect	m_rHand;
	Uint32		m_uStatus;
	CContainer  m_tools{(t_ptfV)CToolBox::ToolDeleteMethod};

private:
	CToolBox();
public:
	CToolBox(int iLocX,int iLocY,int iWidth, int iHeight, SDL_Color color);
	~CToolBox();
	void Draw(SDL_Renderer* Renderer) const; /* ANCESTRAL REDEFINITION DRAW METHOD :  same name same signature    the youngest class is used !!!  */
	int MouseMotion(SDL_MouseMotionEvent*pEvent);

	CTool*AddTool(CTool*pTool);
	size_t GetCard();
	SDL_Rect GetLocation()const;
	int MouseOnToolBox(SDL_Point Point)const;

	CTool*ToolAt(SDL_Point Point);


	static void*ToolMoveMethod(CTool*pTool,SDL_Rect*frame);
	static CTool*ToolDrawMethod(CTool*pTool, SDL_Renderer*pRenderer);
	static CTool*ToolDeleteMethod(CTool*pTool);


};


#endif /* CTOOLBOX_H_ */
