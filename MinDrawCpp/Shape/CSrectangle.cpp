/*
 * CSrectangle.cpp
 *
 *  Created on: 30 oct. 2022
 *      Author: andre
 */

#include <CSrectangle.h>

CSrectangle::CSrectangle(): CShape(),m_toolType(TOOL_UNDEFINED) {}

CSrectangle::~CSrectangle() {}

CSrectangle::CSrectangle(SDL_Rect frame,SDL_Color color):
		CShape(frame, color),
		m_toolType(TOOL_RECTANGLE)
{}

void CSrectangle::Draw(SDL_Renderer*pRenderer)const{
	SDL_SetRenderDrawColor(pRenderer, m_color.r, m_color.g, m_color.b, m_color.a);
	SDL_RenderDrawRect(pRenderer, &m_rFrame);
}

void*CSrectangle::WriteInFile(FILE*fd){

	fwrite(&m_rFrame,sizeof(SDL_Rect),1,fd);
	fwrite(&m_color,sizeof(SDL_Color),1,fd);
	fwrite(&m_toolType,sizeof(int),1,fd);
	SDL_Log("WriteInFile");
	return nullptr;
}

int CSrectangle::GetType(){
	 return m_toolType;
}
