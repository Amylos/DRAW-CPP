/*
 * CTcircle.cpp
 *
 *  Created on: 11 oct. 2022
 *      Author: Garnier
 */


#include <CTcircle.h>


CTcircle::CTcircle(): CTool(),m_toolType(0){}

CTcircle::~CTcircle(){}

CTcircle::CTcircle(SDL_Color color): CTool(color),m_toolType(TOOL_CIRCLE){}

void CTcircle::Draw(SDL_Renderer*pRenderer)const{

	SDL_SetRenderDrawColor(pRenderer, m_color.r, m_color.g, m_color.b, m_color.a);
	CUtil::RenderDrawCircle(pRenderer, SDL_Point{m_rFrame.x + m_rFrame.w/2,m_rFrame.y + m_rFrame.h/2}, m_rFrame.w/2);
}

int CTcircle::GetType(){
	 return m_toolType;
}

