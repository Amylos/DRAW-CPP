/*
 * CTtriangle.cpp
 *
 *  Created on: 11 oct. 2022
 *      Author: Garnier
 */



#include <CTtriangle.h>

CTtriangle::CTtriangle(): CTool(),m_toolType(0){}

CTtriangle::~CTtriangle(){}

CTtriangle::CTtriangle(SDL_Color color): CTool(color),m_toolType(TOOL_TRIANGLE){}

void CTtriangle::Draw(SDL_Renderer*pRenderer)const{
	SDL_SetRenderDrawColor(pRenderer, m_color.r,  m_color.g,  m_color.b,  m_color.a);
	CUtil::RenderDrawTriangle(pRenderer,m_rFrame, m_rFrame.w);
}

int CTtriangle::GetType(){
	 return m_toolType;
}
