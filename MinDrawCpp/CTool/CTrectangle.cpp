/*
 * CTrectangle.cpp
 *
 *  Created on: 11 oct. 2022
 *      Author: Garnier
 */


#include <CTrectangle.h>

using namespace std;

CTrectangle::CTrectangle(): CTool(),m_toolType(0){}

CTrectangle::~CTrectangle(){}

CTrectangle::CTrectangle(SDL_Color color): CTool(color),m_toolType(TOOL_RECTANGLE){}

void CTrectangle::Draw(SDL_Renderer*pRenderer)const{
	SDL_SetRenderDrawColor(pRenderer, m_color.r,  m_color.g,  m_color.b,  m_color.a);
	SDL_RenderDrawRect(pRenderer, &m_rFrame);
}

int CTrectangle::GetType(){
	 return m_toolType;
}
