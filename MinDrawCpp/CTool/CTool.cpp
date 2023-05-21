/*
 * Ctools.cpp
 *
 *  Created on: 7 oct. 2022
 *      Author: Garnier
 */


#include "CTool.h"

CTool::CTool(): CArea(),m_toolType(TOOL_UNDEFINED){}

CTool::~CTool(){}

CTool::CTool(SDL_Color color):  CArea(0,0,0,0,color),m_toolType(TOOL_UNDEFINED){}


/**************** STATIC METHOD *****************/

void CTool::SetFrame(SDL_Rect frame){
	m_rFrame = frame;
}

void*CTool::Move(SDL_Rect*frame){

	m_rFrame.x = frame->x;
	m_rFrame.y = frame->y + frame->w*frame->h;
	frame->h++;
	return nullptr;
}

 CTool*CTool::IsAtMethod(CTool*pTool,SDL_Point*Point){

	 if(pTool->IsAt(Point))return pTool;
	 return nullptr;
 }

 void*CTool::IsAt(SDL_Point*Point){

	 if(SDL_PointInRect(Point, &m_rFrame)) return this;
	 return nullptr;
 }

int CTool::GetType(){
	 return m_toolType;
}

SDL_Color CTool::GetColor(){
	return m_color;
}

SDL_Color CTool::GetColorChart(SDL_Point Point){
	return m_color;
}
